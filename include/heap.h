#pragma once
#include "_ns.h"
#include "enumdef.h"
#include "callback.h"
#include "flagset.h"
#include "unexpect.h"
#include "atomic_count.h"
#include "allocator.h"

#include "smart_pointer/_sp_convertible.h"
_SYS_NS

SMART_ENUM(heap_handle_flags,
	IsFundamental = 1 << 2,
	IsArray = 1 << 3,
	IsOwner = 1 << 4,
	ReleaseOnRemove = 1 << 5,
	IsInvalidated = 1 << 6,
	HasTypedDestructor = 1 << 7,
	IsCRT = 1 << 8,
	);

class handle;

struct _heap_dbg_callbacks
{
	callback<handle*, size_t> mallocd{};
	callback<handle*, void*> freed{};
};
static constexpr int CONTROL_BLOCK_MODE_NONTYPED = 1;
static constexpr int CONTROL_BLOCK_MODE_OBJECT = 2;
static constexpr int CONTROL_BLOCK_MODE_OBJECT_ARRAY = 2;

static constexpr int CONTROL_BLOCK_MAX_TYPE_SIZE = (unsigned short)-1;
static constexpr uint32_t CONTROL_BLOCK_DISPOSED = 0xffffffff;

SMART_ENUM(control_block_type,
	T_INVALID,
	T_OBJECT,
	T_ARRAY,
	T_OBJECT_ARRAY,
	);

class alloc;

// We do not want an single CBLK structure occupying the same size remaining unused fields.

class  _cb_reference_count {
	mutable sys::atomic_count _refcount;
public:
	_cb_reference_count() : _refcount(0) {}
	// Reference count
	inline long value() const { return _refcount.operator uint32_t(); }

	// Increase refcount
	inline size_t retain() {
		return _refcount.operator++();
	}
	// Decrease refcount
	inline size_t release() {
		return _refcount.operator--();
	}
	// Value
	sys::atomic_count& counter()const { return _refcount; }
};

class handle;
namespace detail {

	using _size = uint16_t;
	using _type_size = uint16_t;
	using _align = uint16_t;

	/// <summary>
	/// Internal control block that manages a referenced memory region, its allocator, size, alignment, and reference-tracking semantics.
	/// </summary>
	class _control_block {
		friend handle;

	protected:
		void* _px;
		_size _sizev;
		_align _alignv;
		alloc* _allocator;

	public:
		_control_block(
			alloc* allocator,
			void* px,
			_size size,
			_align alignment
		);

		// Determines if this reference is invalidated.
		bool removed() const;

		// The virtual type of this control block.
		virtual control_block_type block_type() const;

		// Count in bytes of memory assigned in the referenced address.
		int size() const;

		// Derived type or one if byte field.
		virtual _type_size type_size() const;

		// Determinates that this referenced address is a byte array. 
		// False if typed object or byte field.
		virtual bool is_array() const;

		alloc* allocator();

		// Assignation alignment.
		_align alignment() const;

		// Determines is this instance is unique, true by default if not tracked.
		virtual bool unique() const;

		// Obtains the referenced data address by this instance as readonly.
		const void* data() const;
		// Obtains the referenced data address by this instance.
		void* data();

		// Unsafe pop: for factory utilities. 
		// Invalidates this instance afterwards.
		inline void* unsafe_pop() {
			void* dta = _px;
			_sizev = 0;
			_alignv = 0;
			_allocator = 0;
			_px = 0;
			return dta;
		}

		bool is_null() const;

	protected:
		// Clears fields, does not dispose.
		virtual void unsafe_clear_fields();

		virtual bool check_proper_release();

	public:
		// Abstraction dispose by higher owner (e.g: typed_handle)
		virtual void dispose();

		// Obtains the reference count, null if not tracked.
		virtual sys::atomic_count* get_reference_count() const;

		// Determines if the data referenced by this instance is reference tracked.
		virtual bool is_shared() const;

		virtual ~_control_block() = default;
	};

	class _shared_control_block : public _control_block, public _cb_reference_count {

	public:
		_shared_control_block(alloc* allocator, void* px, _size size, _align alignment);

		virtual bool is_shared() const override;

		sys::atomic_count* get_reference_count() const override;

		bool unique() const override;
		virtual ~_shared_control_block() = default;
	};

	/// <summary>
	/// OBJECT
	/// </summary>
	class _typed_control_block : public _control_block {
	protected:
		// REMOVE SINCE SIZE = TYPE_SIZE, this only makes sense to have it you hold and array.
		//unsigned short type_size;
		destructor_function _destructor;
	public:
		_typed_control_block(alloc* alloc,
			void* px,
			_size size,
			_align alignment,
			destructor_function dtor);

		bool is_array() const override;
		control_block_type block_type() const override;

		// Destructor function for the type or NULL.
		destructor_function dtor() const;
		virtual bool check_proper_release()override;
		void unsafe_clear_fields() override;
		void dispose() override;

		virtual ~_typed_control_block() = default;
	};

	/// <summary>
	/// SHARED OBJECT
	/// </summary>
	class _shared_typed_control_block : public _typed_control_block, public _cb_reference_count {
	public:
		_shared_typed_control_block(alloc* alloc, void* px, _size size, uint16_t alignment, destructor_function dtor);
		virtual bool is_shared() const override;
		sys::atomic_count* get_reference_count() const override;
		bool unique() const override;
		virtual ~_shared_typed_control_block() = default;
	};

	/// <summary>
	/// TYPED ARRAY
	/// </summary>
	// Do not confuse this with the main control block.
	// Is not an untyped byte array.
	// It represents a control block in which a series of typed objects with destruction information have been assigned.
	class _typed_array_control_block : public _typed_control_block
	{
	protected:
		_type_size _type_sizev;
		_size _count;
	public:
		_typed_array_control_block(alloc* alloc, void* px, _size count, _type_size type_size, _align alignment, sys::destructor_function dtor_function);

		// Update 6/27/26: Add missing to array metadata informative override.
		bool is_array() const override;

		control_block_type block_type() const override;
		// The size of the assigned type _Ty of the reference.
		_type_size type_size() const override;
		virtual ~_typed_array_control_block() = default;
	};

	/// <summary>
	/// SHARED TYPED ARRAY
	/// </summary>
	class _shared_typed_array_control_block : public _typed_array_control_block, public _cb_reference_count {
	public:
		_shared_typed_array_control_block(alloc* alloc, void* px, _size count, _type_size type_size, _align alignment, sys::destructor_function dtor_function);

		bool is_shared() const override;

		bool is_array() const override;
		sys::atomic_count* get_reference_count() const override;
		bool unique() const override;
		virtual ~_shared_typed_array_control_block() = default;
	};

	namespace factory {
		static inline sys::alloc* cb_allocator() {
			return &sys::crt_alloc::instance();
		}

		// Create an specific control block.
		template<typename T>
		static T* new_control_block() {
			__expect(cb_allocator() != NULL);
			T* ctrl = (T*)(cb_allocator()->unsafe_malloc(sizeof(T), alignof(T)));

			if (!ctrl) {
				THROW(sys::bad_alloc("Could not create a new control_block"));
				return;
			}
			return ctrl;

		}

		static void free_control_block(detail::_control_block* block) {
			__expect(cb_allocator() != NULL);
			block->~_control_block();

			cb_allocator()->unsafe_free(block);

		}

		//extern - Remove extern since we need to debug this
		void release_control(detail::_control_block*&);

		// Allocate field. Like basic malloc.
		detail::_control_block* allocate(detail::_size count, detail::_align alignment, sys::alloc* allocator, bool shared);

		// Allocate type with destructor, type not initialized.
		detail::_control_block* allocate_type(detail::_size type_size,
			detail::_align alignment, sys::alloc* allocator, destructor_function destructor, bool shared);

		// Allocate type array with destructor, elements not initialized.
		detail::_control_block* allocate_type_array(detail::_size elementsCount, detail::_type_size typeSize,
			detail::_align alignment, sys::alloc* allocator, destructor_function destructor, bool shared);
	}
}

template<typename T>
class shared_ptr;

template<typename _Ty>
class typed_handle;

class handle {
protected:
	mutable detail::_control_block* _dta{ nullptr };

public:
	handle(std::nullptr_t);
	handle();
	// non-copyable by default.
	handle(const handle& other) = delete;
	inline handle(handle&& other) {
		steal(sys::move(other));
	}
	explicit handle(detail::_control_block* ctrl);

	void steal(handle&& other);

	size_t size()const;

	const void* ptr() const;
	void* ptr();

	const void* data() const;
	void* data();

	bool is_typed() const;

	bool is_null() const;

	inline sys::alloc* allocator() const {
		return _dta->allocator();
	}

	bool is_shared() const {

		if (this->_dta == nullptr) return false;

		return this->_dta->is_shared();
	}

	bool unique() const {
		if (this->_dta == nullptr) return false;

		return this->_dta->unique();
	}
	// The size of the allocated type, 1 if byte field.
	size_t type_size() const {
		return this->_dta->type_size();
	}



	inline void _unsafe_assign(const handle& other) {
		if (this->_dta == other._dta || this == &other) {
			THROW(sys::invalid_operation_error("this->_dta == other _dta"));
			return;
		}

		reset();
		this->_dta = other._dta;
	}
	inline void _unsafe_assign(sys::detail::_control_block* other) {
		if (this->_dta == other) {
			THROW(sys::invalid_operation_error("this->_dta == other _dta"));
			return;
		}
		reset();
		this->_dta = other;
	}
	template<typename _KnownTy>
	void _unsafe_assign(const sys::typed_handle<_KnownTy>& other_typed);

	template<typename _Ty>
	sys::typed_handle<_Ty> _unsafe_cast();

	template<typename _Ty>
	sys::typed_handle<const _Ty> _unsafe_cast() const;


	bool is_array() const {
		return this->_dta->is_array();
	}

	handle& reset();

	inline sys::detail::_control_block* _unsafe_pop() {
		auto* dta = this->_dta;
		this->_dta = NULL;
		return dta;
	}

	void dispose() {
		reset();
	}
protected:
	inline void _set_ref(detail::_control_block* block) {
		this->_dta = block;
	}

	void _shared_init(const handle& other);
public:

	~handle();
};
template<typename T>
class typed_handle : public handle {
	friend shared_ptr<T>;

public:
	using _Tr = typename sys::decay<T>::type;

	typed_handle(std::nullptr_t) : handle(nullptr) {}

	typed_handle(const typed_handle&) = delete;
	
	typed_handle(typed_handle&& other) {
		unexpect((!this->is_null()) && "unexpected condition");
		this->_unsafe_assign(other._unsafe_pop());
	}


	explicit typed_handle(detail::_control_block* blk) : handle(blk) {}

	template<typename K,
		typename = sys::enable_if_t<
		sys::convertible<T*, K*>::value>>
		typed_handle(typed_handle<K>&& other)
	{
		this->_dta = other._dta;
		other._dta = nullptr;
	}
	typed_handle& operator=(const typed_handle&) = delete;

	const _Tr* ptr()const { return static_cast<const _Tr*>(data()); }
	_Tr* ptr() {
		return static_cast<_Tr*>(data());
	}
	template<class K>
	K* cast()
	{
		static_assert(sys::convertible<K, _Tr>::value,
			"Invalid cast.");

		return static_cast<K*>(data());
	}
	template<class K>
	const K* cast() const
	{
		static_assert(sys::convertible<K, _Tr>::value,
			"Invalid cast.");

		return static_cast<const K*>(data());
	}


	inline const _Tr* operator->()const {
		return  static_cast<const _Tr*>(data());
	}
	inline _Tr* operator->() { return static_cast<_Tr*>(data()); }

	void steal(typed_handle<T>& other) {
		this->_unsafe_assign(other._unsafe_pop());
	}
	inline _Tr* activate() {
		new (ptr()) _Tr();
		return ptr();
	}
	virtual ~typed_handle() = default;
};

template<typename _KnownTy>
void sys::handle::_unsafe_assign(const sys::typed_handle<_KnownTy>& other_typed) {
	if (this->_dta == other_typed._dta) {
		THROW(sys::invalid_operation_error("this->_dta == other_typed._dta"));
		return;
	}
	reset();
	this->_dta = other_typed._dta;
}


template<typename _Ty>
sys::typed_handle<_Ty>  sys::handle::_unsafe_cast() {
	if (!this->is_typed()) {
		THROW(sys::invalid_cast_error());
		return nullptr;
	}
	sys::typed_handle<_Ty> r;
	r._set_ref(this->_dta);
	return r;
}

template<typename _Ty>
sys::typed_handle<const _Ty>  sys::handle::_unsafe_cast() const {
	if (!this->is_typed()) {
		THROW(sys::invalid_cast_error());
		return nullptr;
	}
	sys::typed_handle<_Ty> r;
	r._set_ref(this->_dta);
	return r;
}

template<typename _Ty>
class unique_handle : public typed_handle<_Ty>{
	using Mybase = typed_handle<_Ty>;

public:
	unique_handle() = delete;
	unique_handle(unique_handle&& other ) : typed_handle<_Ty>(nullptr) {
		_unsafe_assign(other._unsafe_pop());
	}
	unique_handle(sys::typed_handle<_Ty>&& other) : typed_handle(nullptr) {
		_unsafe_assign(other._unsafe_pop());
	}
	unique_handle(std::nullptr_t) : Mybase(nullptr) {}
	


	virtual ~unique_handle(){
		this->dispose();
	}

	void _unsafe_assign(sys::detail::_control_block * block) {
		handle::_unsafe_assign(block);
	}

	unique_handle& operator =(unique_handle&& other) {
		this->_unsafe_assign(other._unsafe_pop());
		return *this;
	}
};



_SYS_ENS
