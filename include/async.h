#pragma once
#include "_ns.h"
#include "event.h"
#include "rand.h"
#include "..\memory\hash_set.h"
#include "mutex.h"
/**
 * @file task_queue_dispatcher.h
 * @brief Implements an asynchronous lightweight task queue system using PS3 low-level synchronization primitives.
 *
 * This module provides a minimalistic framework for queuing, dispatching, and executing asynchronous
 * tasks in a dedicated thread or locally. It uses `sys_lwcond`, `sys_lwmutex`, and `sys_event_queue`
 * as synchronization and communication primitives, similar to a thread pool or deferred call system.
 *
 * The implementation uses custom structures (`task_reserve`, `task_reservation`, etc.) for task tracking,
 * handle management, and event queue integration.
 */

 // #TODO
 // Add debug print macro
 // Solve trap "handle error", not found on hash_set
 // Add some different types of event args for enqueue_execute

_SYS_NS

#define _SYS_TASK_DEBUG true

#if _SYS_TASK_DEBUG
#define _SYS_TASK_ASSERT(condition) do {\
		if(!(condition)){\
			sys::printf("[sys_task] Assertion failed: %s\n", #condition);\
			__builtin_trap();\
		}\
	}while(0);\


#define _SYS_TASK_ASSERTD(condition, message, ...) do {\
		if(!(condition)){\
			sys::printf("[sys_task] Assertion failed: %s\n", #condition);\
			sys::printf(message, __VA_ARGS__);\
			__builtin_trap();\
		}\
	}while(0);


#define _SYS_TASK_LOG(message,...) sys::printf(message "\n", __VA_ARGS__);

#else
#define _SYS_TASK_ASSERT(condition) 
#define _SYS_TASK_ASSERTD(condition, message)
#define _SYS_TASK_LOG(message,...) sys::printf(message "\n", __VA_ARGS__);

#endif

typedef uint32_t task_handle_t;
static constexpr task_handle_t TASK_HANDLE_INVALID = -8u;


static const uint32_t finalize_task = -0xFFFFFFu;


class task_polymorphic_persistency_wrapper {
public:

	virtual void dispose_data() {
		sys::dbg::writeLine("[system tasks] WARNING. Calling dispose_data on an unimplemented instance of persistency_wrapper");
	}
};

struct task_ppw_numeric_tag : public task_polymorphic_persistency_wrapper {
	uint32_t tag1;

	void dispose_data()override {
		tag1 = 0;
	}
};

struct task_ppw_numeric_tags : public task_polymorphic_persistency_wrapper {
	uint32_t tag1;
	uint32_t tag2;
	uint32_t tag3;
	uint32_t tag4;

	void dispose_data()override {
		tag1 = 0;
		tag2 = 0;
		tag3 = 0;
		tag4 = 0;
	}
};

/**
 * @struct task_event_args_t
 * @brief Generic structure passed to task functions during execution.
 *
 * Can store an arbitrary pointer tag that can be interpreted as any user-defined type.
 */

struct task_event_args_t {
	task_polymorphic_persistency_wrapper* persistency;



};
/**
 * @struct task
 * @brief Represents a single executable task within the dispatcher.
 */
struct task {
public:
	using entry = uint64_t(*)(const task_event_args_t*);

	task_handle_t handle;
	entry funcEntry;
};
using task_entry = task::entry;
/**
 * @struct task_reserve
 * @brief Represents a reserved task within the task reservation system.
 */
struct task_reserve {
	task task_origin;
	uint32_t result{ 0 };
	task_polymorphic_persistency_wrapper* persistency;
	bool operator ==(const task_reserve& other) const {
		if (task_origin.handle == other.task_origin.handle)
			if (task_origin.funcEntry == other.task_origin.funcEntry)
				if (result == other.result)
					if (persistency == other.persistency)
						return true;
		return false;
	}
};

_HASH_PROVIDER_SPEC(task_reserve) {
	return sys::hash_int(v.task_origin.handle);
}
_HASH_PROVIDER_END_SPEC
class task_queue_dispatcher;


using task_ppw = task_polymorphic_persistency_wrapper;




/**
 * @class task_reservation
 * @brief Internal manager for active and reserved tasks within a dispatcher.
 *
 * This class maintains a thread-safe hash set of `task_reserve` objects and provides
 * lookup, insertion, and removal methods for task lifecycle tracking.
 */
class task_reservation {
	friend task_queue_dispatcher;
	sys::hash_set<task_reserve> mRes;
	sys::mutex mMutex;
private:
	task_reservation() : mRes() {

	}
	int reserve(const task_reserve& in, task_reserve** result) {
		if (!mMutex.try_lock()) return 1;
		task_reserve* stored = nullptr;
		if (!mRes.put(in, &stored)) {
			mMutex.unlock();
			_SYS_TASK_ASSERT(false);
			return 2;
		}
		_SYS_TASK_ASSERT(stored != nullptr);
		stored->task_origin.handle = in.task_origin.handle;
		*result = stored;
		mMutex.unlock();
		return 0;
	}
	sys::optional<task_reserve> fetch(task_handle_t handle) {
		mMutex.lock();
		size_t h = sys::hash_int(handle);
		task_reserve* task_result = mRes.find_hash(h);
		task_reserve cloned{};
		if (task_result) {
			cloned = *task_result;
			mRes.remove_hash(h);

		}
		mMutex.unlock();
		return task_result != nullptr ? cloned : sys::optional<task_reserve>(nullopt);
	}
	task_reserve* find(task_handle_t handle) {
		mMutex.lock();
		size_t h = sys::hash_int(static_cast<uint64_t>(handle));
		task_reserve* task_result = mRes.find_hash(h);
		mMutex.unlock();
		return task_result;
	}
	sys::hash_set<task_reserve>& _set() {
		return this->mRes;
	}
};
/**
 * @struct task_event_in
 * @brief Low-level structure describing event data received by the dispatcher.
 */
struct task_event_in {
	uint64_t pTask;  // d1
	uint64_t pSender; // d2
	uint64_t pResult; // d3
};
class task;
using asynchronic_function_signature = uint64_t(*)(const task_event_args_t*);

/**
 * @class task_queue_dispatcher
 * @brief Core dispatcher responsible for queuing, executing, and managing asynchronous tasks.
 *
 * Provides mechanisms for both background (threaded) and local (synchronous) execution.
 * Integrates with the PS3 event queue and mutex/condition primitives for thread-safe task scheduling.
 */
class alignas(16) task_queue_dispatcher {
	friend task_reservation;

	event_port mPort;
	event_queue mQueue;
	sys_ppu_thread_t mThread{ SYS_PPU_THREAD_ID_INVALID };
	random mUidGen;
	task_reservation mReservation{};
	int mPriority;
	int mStackSize;
	int mBackgroundError;
	sys_lwcond mWorkLock;
	sys_lwmutex_t mWorkMutex;
	bool mInitialized = false;
	bool mMustDestroy{ false };
	bool mThreaded{ false };
public:
	task_queue_dispatcher() :
		task_queue_dispatcher(SYS_SYNC_PRIORITY, 99999, 8u, 1000, 0x5000)
	{

	}
	/*
	* @brief Constructs a new task queue dispatcher instance.
	* @param protocol System protocol type.
	* @param uid Unique identifier for the dispatcher.
	* @param capacity Queue capacity.
	* @param knPriority Thread priority.
	* @param knStackSize Thread stack size.
	*/
	task_queue_dispatcher(sys_protocol_t protocol, uint64_t uid, uint8_t capacity, int knPriority, int knStackSize)
		: mPort(uid), mQueue(mPort, protocol, SYS_PPU_QUEUE, uid, capacity), mUidGen(), mPriority(knPriority), mStackSize(knStackSize) {

		if (this->mPriority < 600)
			this->mPriority = 600;
	}
	/**
	 * @brief Initializes the dispatcher and spawns a background worker thread.
	 * @return Zero on success, error code otherwise.
	 */
	int initialize() {
		if (mInitialized) return EABORT;

		sys_lwmutex_attribute_t mattr{};
		sys_lwmutex_attribute_initialize(mattr);
		int R = sys_lwmutex_create(&mWorkMutex, &mattr);
		if (R) return R;
		sys_lwcond_attribute attr{};
		sys_lwcond_attribute_initialize(attr);
		R = sys_lwcond_create(&mWorkLock, &mWorkMutex, &attr);
		if (R) return R;
		R = _background_initialize();
		if (R) return R;
		mInitialized = true;
		mThreaded = true;
		return 0;
	}
	/**
	 * @brief Checks if the dispatcher is running in a background thread.
	 */

	bool is_threaded() const {
		return mThreaded;
	}

	/**
	 * @brief Initializes the dispatcher to run locally (no separate thread).
	 */
	int dispatch_locally() {
		if (mInitialized) return EABORT;

		sys_lwmutex_attribute_t mattr{};
		sys_lwmutex_attribute_initialize(mattr);
		int R = sys_lwmutex_create(&mWorkMutex, &mattr);
		if (R) return R;
		sys_lwcond_attribute attr{};
		sys_lwcond_attribute_initialize(attr);
		R = sys_lwcond_create(&mWorkLock, &mWorkMutex, &attr);
		if (R) return R;

		// locally.
		R = sys_ppu_thread_get_id(&mThread);
		_SYS_TASK_ASSERTD(!CELL_ERROR_IS_FAILURE(R), "Unexpected result of sys_ppu_thread_get_id: 0x%X", R);


		R = sys_ppu_thread_set_priority(mThread, this->mPriority);
		_SYS_TASK_ASSERTD(!CELL_ERROR_IS_FAILURE(R), "Unexpected result of sys_ppu_thread_set_priority: 0x%X", R);


		mInitialized = true;
		mThreaded = false;
		mMustDestroy = false;
		return _listen_for_events(true);
	}
	/**
	 * @brief Returns whether the dispatcher has been initialized.
	 */
	bool initialized() const {
		return mInitialized;
	}
	/**
	 * @brief Disposes and cleans up all associated resources and queues.
	 */
	void dispose() {
		mMustDestroy = true;
		if (mInitialized) {
			sys_lwcond_signal_to(&mWorkLock, mThread);
			sys_lwcond_destroy(&mWorkLock);
			sys_lwmutex_destroy(&mWorkMutex);
			mPort.disconnectFromQueue();
			mPort.dispose();
			mQueue.dispose();
		}
	}
	/**
	 * @brief Enqueues and executes a task asynchronously.
	 * @param entry Task function entry pointer.
	 * @return Zero on success, error code otherwise.
	 */
	int enqueue_execute(task_entry entry) {
		task task_model{};
		task_model.funcEntry = entry;
		task_model.handle = mUidGen.next();


		_SYS_TASK_ASSERT(task_model.handle != 0);

		// nullptr by now.
		int R = this->sendImpl(task_model, nullptr);
		if (R)	return R;
		R = sys_lwcond_signal_to(&mWorkLock, mThread);

		return R;
	}
	/**
	 * @brief Enqueues and executes a task asynchronously.
	 * @param entry Task function entry pointer.
	 * @return Zero on success, error code otherwise.
	 */
	int enqueue_execute(task_entry entry, task_ppw* abstract_persistent) {
		task task_model{};
		task_model.funcEntry = entry;
		task_model.handle = mUidGen.next();


		_SYS_TASK_ASSERT(task_model.handle != 0);

		// nullptr by now.
		int R = this->sendImpl(task_model, abstract_persistent);
		if (R)	return R;
		R = sys_lwcond_signal_to(&mWorkLock, mThread);

		return R;
	}
	// @return The dispatcher thread priority.
	int priority() const { return this->mPriority; }

	// @return The dispatcher thread stack size.
	int stack_size() const { return this->mStackSize; }
	// @return Unique queue identifier.
	const uint64_t& queue_uid() const {
		return this->mQueue.uid();
	}
	// @return Queue capacity.
	const uint8_t& capacity() const {
		return this->mQueue.capacity();
	}
	static task_queue_dispatcher* system_default() {
		static task_queue_dispatcher* result = new task_queue_dispatcher(SYS_SYNC_PRIORITY, 0x810CE11, 12u, 800, 0x10000);
		return result;
	}


private:
	int  _background_initialize() {
		return sys_ppu_thread_create(&mThread, _background_wrapped_work, (uint64_t)this, mPriority, mStackSize, 0, "Event Queue");
	}

	static inline void _background_wrapped_work(uint64_t raw) {
		// For 'this' usage.
		reinterpret_cast<task_queue_dispatcher*>(raw)->_listen_for_events(false);
	}

	int poll() {
		int R = sys_lwcond_wait(&this->mWorkLock, 0);
		if (R) {
			sys::printf("sys_lwcond_wait(%x) ", R);
			__builtin_trap();
		}
	}

	void _doInvoke(sys_event& in) {
		if (in.source == this->mPort.uid()) {
			task_handle_t handle = (task_handle_t)in.data1;
			if (handle == 0) {
				sys::printf("handle cannot be zero");
				__builtin_trap();
			}
			sys::task_reserve* slot = mReservation.find(handle);

			// fail
			if (!slot) {
				if (this->mReservation.mRes.size() == 0) {
					sys::printf("mRes.size() == 0");
				}
				else {
					int32_t indx = 0;
					for (auto& elem : this->mReservation.mRes) {
						sys::printf("[task[%i]] handle{0x%X}\n", indx, elem.task_origin.handle);
						++indx;
					}
				}

			}
			_SYS_TASK_ASSERT(slot != nullptr);
			sys::task_event_args_t args{
				slot->persistency
			};


			slot->result = slot->task_origin.funcEntry(&args);

			// DESTROY PERSISTENT OBJECT BETWEEN THREADS.
			if (slot->persistency) {
				slot->persistency->dispose_data();
#if TEST
				sys::dbg::writeLine("destroy: slot->persistency 0x%X", slot->persistency);
#endif
				delete slot->persistency;
				//*(uint32_t*)slot->persistency = 0x0000DEAD; // [Debug] Set invalid destroyed.
				slot->persistency = NULL;

			}
			_sys_assert(mReservation.mRes.remove(*slot));
		}
	}

	CellError _listen_for_events(bool locally) {
		this->mBackgroundError = mPort.initialize();
		if (this->mBackgroundError) return this->mBackgroundError;

		this->mBackgroundError = mQueue.initialize();
		if (this->mBackgroundError) return this->mBackgroundError;

		this->mBackgroundError = mPort.connectToQueueLocal(this->mQueue);
		if (this->mBackgroundError) return this->mBackgroundError;

		this->mBackgroundError = sys_lwmutex_lock(&this->mWorkMutex, 0);

		if (this->mBackgroundError) return this->mBackgroundError;

		uint8_t queue_capacity = this->capacity();


		sys::array<sys_event> resultingArray{};


		while (!mMustDestroy) {
			int R = poll();
			R = mQueue.tryReceive(queue_capacity, resultingArray, 0);
			if (resultingArray.size())
				for (sys_event& event : resultingArray)
					_doInvoke(event);
		}
		sys_lwmutex_unlock(&this->mWorkMutex);
		if (!locally)
			sys_ppu_thread_exit(this->mBackgroundError >= 0 ? 0 : this->mBackgroundError);

		return 0;
	}

	CellError sendImpl(const task& in, void* sender);

public:
	~task_queue_dispatcher() {
		dispose();
		mReservation.~task_reservation();
		mQueue.~event_queue();
		mPort.~event_port();;
	}
};

static inline uint64_t task_result(CellError e) {
	return e == 0 ? finalize_task : e;
}


CellError task_queue_dispatcher::sendImpl(const task& in, void* sender) {

	task_reserve* stored_reserve = nullptr;

	task_reserve tin;
	tin.result = 0;
	tin.task_origin = in;
	tin.persistency = (sys::task_ppw*)sender;
	// assert stored_reserve
	int R = mReservation.reserve(tin, &stored_reserve);
	if (!stored_reserve) __builtin_trap();

	_SYS_TASK_LOG("[system_task] reserve handle 0x%X", stored_reserve->task_origin.handle);

	return sys_event_port_send(mPort.handle(), static_cast<uint64_t>(in.handle), 0, 0);
}

class task_inline_launcher {
	void* mRefToFunc;
	task_queue_dispatcher* mTargetDispatcher;
	task_ppw* mPersistentDataTag;
	int mRunVal;
	bool mRunned;
	bool mAutoDispatch;
public:
	task_inline_launcher(void(*function)())
		: mTargetDispatcher(sys::task_queue_dispatcher::system_default()), mRefToFunc(function), mRunned(false), mPersistentDataTag(NULL), mAutoDispatch(true)
	{

	}
	task_inline_launcher(void(*function)(), task_queue_dispatcher* dispatcher) :
		mTargetDispatcher(dispatcher),
		mRefToFunc(function), mRunned(false), mPersistentDataTag(NULL), mAutoDispatch(true)
	{

	}
	task_inline_launcher(asynchronic_function_signature function, task_queue_dispatcher* dispatcher) :
		mTargetDispatcher(dispatcher),
		mRefToFunc(function), mRunned(false), mPersistentDataTag(NULL), mAutoDispatch(true)
	{

	}
	task_inline_launcher& with_persistent(sys::task_ppw* abstract_persistent) {
		mPersistentDataTag = abstract_persistent;
		return *this;
	}
	task_inline_launcher& with_autodispatch(bool autodispatch = true) {
		mAutoDispatch = autodispatch;
		return *this;
	}
	void dispatch() {
		_validate_usage();
		if (!mRunned) {
			mRunned = true;
			//  Usar mPersistentDataTag en lugar de NULL
			mRunVal = mTargetDispatcher->enqueue_execute(
				(sys::task_entry)mRefToFunc,
				mPersistentDataTag  // FIX: Enviar datos persistentes
			);
			mPersistentDataTag = nullptr;  // Transferencia de propiedad
		}
	}

	int dispatch_error() const {
		return mRunVal;
	}

	bool is_executed() const {
		return mRunned;
	}

	~task_inline_launcher() {
		if (mAutoDispatch) {
			dispatch();
			if (CELL_ERROR_IS_FAILURE(mRunVal))
				sys::dbg::writeLine("## mRunVal => %x", mRunVal);
			_sys_assertd(!CELL_ERROR_IS_FAILURE(mRunVal), "[system_task] Failed to enqueue.");

		}
		mTargetDispatcher = nullptr;
		mRefToFunc = nullptr;
	}

	void _validate_usage() {
		_sys_assert(mTargetDispatcher != NULL);
		_sys_assert(mRefToFunc != NULL);
		_sys_assert(!mRunned);
	}

};
/**
 * @brief Enqueues a function to be executed asynchronously on the system default dispatcher.
 * @param func Function pointer of type task_entry.
 * @return Zero on success, nonzero otherwise.
 */
static task_inline_launcher async(task_entry func) {
	//task_inline_launcher pl(func, sys::task_queue_dispatcher::system_default());

	//return sys::task_queue_dispatcher::system_default()->enqueue_execute(func);
	return { func, sys::task_queue_dispatcher::system_default() };
}

/**
 * @brief Enqueues a function to be executed asynchronously on the system default dispatcher.
 * @param func Function pointer of type task_entry.
 * @return Zero on success, nonzero otherwise.
 */
static task_inline_launcher async(void(*func)()) {
	//task_inline_launcher pl(func, sys::task_queue_dispatcher::system_default());

	//return sys::task_queue_dispatcher::system_default()->enqueue_execute(func);
	return { func, sys::task_queue_dispatcher::system_default() };
}
_SYS_ENS
