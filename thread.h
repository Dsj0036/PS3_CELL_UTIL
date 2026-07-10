#pragma once
#include <sys\ppu_thread.h>
#include "_pragma_static_getter.h"
#include "_ns.h"
_SYS_NS
/**
 * @class ppu_thread
 * @brief Represents a PlayStation 3 PPU (PowerPC Processing Unit) thread.
 *
 * This class encapsulates PPU thread creation, management, and execution.
 * It provides a wrapper around the PS3 system thread API calls, handling
 * thread lifecycle, state management, and error tracking.
 *
 * @note Thread states are managed internally through STATE_* constants
 * @note All thread operations are synchronized with system-level PPU thread APIs
 *
 * @see sys_ppu_thread_create, sys_ppu_thread_join, sys_ppu_thread_exit
 */
class alignas(16) ppu_thread {
public:
	///< Thread state not yet defined
	static constexpr int32_t STATE_UNDEFINED = 0;

	///< Thread is idle/waiting
	static constexpr int32_t STATE_IDLE = 1;

	///< Thread is currently running
	static constexpr int32_t STATE_RUNNING = 2;


	static constexpr int32_t STATE_DESTROYED = 3;

	///< Thread has completed execution
	static constexpr int32_t STATE_COMPLETED = 4;

	///< Thread finished but not yet joined
	static constexpr int32_t STATE_ZOMBIE = 5;
	/**
	 * @typedef entry
	 * @brief Function pointer type for thread entry point
	 * @param thread Pointer to the ppu_thread instance executing the function
	 * @param arg User-defined argument passed to the thread
	 */
	using entry = void(*)(ppu_thread*, uint64_t);

private:

	///< System thread handle
	sys_ppu_thread_t	_handle;

	///< User argument for entry function
	void* _run_arg;

	///< Thread start time in milliseconds
	uint64_t			_start_time;

	///< Last error code from system calls
	int32_t				_error;

	///< Thread name buffer
	char 				_name[32];

	///< Thread entry point function
	entry				_entry;

	///< Thread stack size in bytes
	int32_t				_stack_size;

	///< Thread priority level
	int32_t				_prio;

	///< Current thread state
	int32_t				_state;

	///< Whether thread is joinable
	bool				_joinable;

public:

	/**
	 * @brief Constructor with explicit name
	 *
	 * Creates a new PPU thread with all parameters specified. The thread
	 * entry point and arguments must be provided at construction time.
	 *
	 * @param name Thread name for debugging purposes (optional). If nullptr,
	 *             the name is derived from the call stack.
	 * @param e Entry point function to execute in the thread
	 * @param arg User-defined argument passed to the entry function
	 * @param stackSize Stack size in bytes for the thread
	 * @param prio Priority level for thread scheduling
	 * @param autostart If true, thread starts immediately; otherwise call start()
	 * @param joinable If true, thread must be joined; if false, detached
	 *
	 * @pre e must not be nullptr
	 * @post Thread is either running (if autostart=true) or ready to start
	 */
	ppu_thread(const char* name, entry e, void* arg = nullptr, int32_t stackSize = 0x40000, int prio = 1000, bool autostart = false, bool joinable = false);

	/**
	 * @brief Constructor without explicit name
	 *
	 * Creates a new PPU thread without an explicit name. The thread name
	 * is automatically derived from the call stack for debugging purposes.
	 * Delegates to the main constructor with name=nullptr.
	 *
	 * @param e Entry point function to execute in the thread
	 * @param arg User-defined argument passed to the entry function
	 * @param stackSize Stack size in bytes for the thread
	 * @param prio Priority level for thread scheduling
	 * @param autostart If true, thread starts immediately; otherwise call start()
	 * @param joinable If true, thread must be joined; if false, detached
	 *
	 * @pre e must not be nullptr
	 * @post Thread is either running (if autostart=true) or ready to start
	 */
	ppu_thread(entry e, void* arg = nullptr, int32_t stackSize = 0x40000, int prio = 1000, bool autostart = false, bool joinable = false);

	/**
	 * @brief Starts the thread execution
	 *
	 * Initiates execution of the thread's entry point function. This method
	 * should only be called if the thread was created with autostart=false.
	 * Calling start() multiple times on the same thread is undefined behavior.
	 *
	 * @return Error code returned by sys_ppu_thread_create:
	 *         - 0 on success
	 *         - Negative value on failure
	 *
	 * @post If successful, thread begins executing its entry function
	 * @note The error code is also stored in the _error member variable
	 */
	int32_t start();

	/**
	 * @brief Joins the thread and waits for completion
	 *
	 * Blocks execution until the specified thread completes. The caller's
	 * thread is suspended until the target thread finishes execution.
	 * This method sets internal state to IDLE during the join operation
	 * and returns to RUNNING upon completion.
	 *
	 * @param target Handle to the thread to join
	 * @param outResult [out] Optional pointer to receive the thread's exit code
	 *
	 * @return Error code returned by sys_ppu_thread_join:
	 *         - 0 on success
	 *         - Negative value on failure
	 *
	 * @post The target thread has completed and its resources are dispose
	 * @note If join fails, the thread state is returned to RUNNING
	 * @warning outResult may be nullptr, in which case the exit code is discarded
	 */
	inline int32_t join(ppu_thread* target, uint64_t* outResult) {
		return join(target->handle(), outResult);
	}
	/**
	 * @brief Joins the thread and waits for completion
	 *
	 * Blocks execution until the specified thread completes. The caller's
	 * thread is suspended until the target thread finishes execution.
	 * This method sets internal state to IDLE during the join operation
	 * and returns to RUNNING upon completion.
	 *
	 * @param target Handle to the thread to join
	 * @param outResult [out] Optional pointer to receive the thread's exit code
	 *
	 * @return Error code returned by sys_ppu_thread_join:
	 *         - 0 on success
	 *         - Negative value on failure
	 *
	 * @post The target thread has completed and its resources are dispose
	 * @note If join fails, the thread state is returned to RUNNING
	 * @warning outResult may be nullptr, in which case the exit code is discarded
	 */
	int32_t join(sys_ppu_thread_t target, uint64_t* outResult);
	/**
	 * @brief Joins the thread and waits for completion
	 *
	 * Blocks execution until the specified thread completes. The caller's
	 * thread is suspended until the target thread finishes execution.
	 * This method sets internal state to IDLE during the join operation
	 * and returns to RUNNING upon completion.
	 *
	 * @param target Handle to the thread to join
	 * @param outResult [out] Optional pointer to receive the thread's exit code
	 *
	 * @return Error code returned by sys_ppu_thread_join:
	 *         - 0 on success
	 *         - Negative value on failure
	 *
	 * @post The target thread has completed and its resources are dispose
	 * @note If join fails, the thread state is returned to RUNNING
	 * @warning outResult may be nullptr, in which case the exit code is discarded
	 */
	inline int32_t join(uint64_t* outResult) {
		return join(this->_handle, outResult);
	}
	inline int32_t join() {
		uint64_t n;
		return join(this->_handle, &n);
	}

	/// Thread name buffer
	inline const char* name()       const { return _name; }

	/// System thread handle
	inline sys_ppu_thread_t handle()const { return _handle; }
	inline uint64_t startTime()     const { return _start_time; }
	inline bool joinable()          const { return _joinable; }
	inline int32_t stackSize()      const { return _stack_size; }
	inline int32_t priority()       const { return _prio; }
	inline int32_t error()          const { return _error; }
	inline int32_t state()          const { return _state; }

	/**
	 * @brief Terminates thread execution with exit code
	 *
	 * Gracefully terminates the currently executing thread. Sets the thread
	 * state to COMPLETED and calls the system thread exit function with
	 * the provided exit code. This should be called from within the thread's
	 * entry point function.
	 *
	 * @param code Exit code to return to any waiting caller (from join())
	 *
	 * @post Thread execution terminates and state becomes COMPLETED
	 * @warning This function does not return; it terminates the thread
	 * @note Should only be called from within the executing thread
	 */
	void finish(uint64_t code);
	inline void finish() { finish(0); }

	/**
	 * @brief Sets the thread name
	 *
	 * Assigns a name to the thread for debugging purposes. If name is nullptr,
	 * derives the name from the current call stack using CellDBG functions.
	 *
	 * @param name Thread name string (optional). If nullptr, name is auto-generated
	 *             from the call stack return address.
	 *
	 * @post _name buffer contains the thread's name
	 * @note Name is limited to sizeof(_name) characters (typically 256)
	 */
	void _setName(const char* name);
private:

	/**
	 * @brief Static thread execution wrapper
	 *
	 * Static function that serves as the actual thread entry point for the
	 * system thread API. It extracts the ppu_thread instance from the provided
	 * pointer, validates it, sets up execution state, and calls the user's
	 * entry function. Handles automatic state transitions.
	 *
	 * @param thread_ptr Opaque pointer to the ppu_thread instance (cast as uint64_t)
	 *
	 * @pre thread_ptr must be a valid pointer to a ppu_thread instance
	 * @post Thread execution begins; state transitions to RUNNING, then to
	 *       ZOMBIE or COMPLETED upon completion
	 *
	 * @note This is called by the system and should not be called directly
	 * @warning Asserts if thread_ptr is invalid or entry point is nullptr
	 */
	static void _exec(uint64_t thread_ptr);
};
_SYS_DEFINE_STATIC_GETTER(current_thread_id, sys_ppu_thread_t);

_SYS_ENS
