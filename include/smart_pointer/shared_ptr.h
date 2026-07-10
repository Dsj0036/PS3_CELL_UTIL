#pragma once
#include "..\heap.h"
#include "..\_ns.h"
_SYS_NS

template<typename T>
struct can_be_shared : bool_constant<!(sys::is_fundamental<sys::remove_extent_t<T>>::value && !sys::is_array<T>::value)>  { };


// typename = sys::enable_if_t<sys::is_fundamental<sys::remove_extent_t<T>>::value && !sys::is_array<T>::value>
template<typename T>
class shared_ptr
{
protected:
	//mutable detail::_control_block* _dta{ nullptr };
	mutable detail::_control_block* _dta{ nullptr };

	// Fails if T is not shareable.
	static_assert(can_be_shared<T>::value, "Invalid shared_ptr instance");

public:
	/// <summary>
	/// Explicit constructor that initializes a shared_ptr from a pointer to an internal control block.Explicitly constructs a shared_ptr by initPointer to an internal control block. The pointer is stored in the shared_ptr's internal _dta member and is used to manage the shared ownership state.ializing its internal control-block pointer.
	/// </summary>
	/// <param name="blk">Pointer to the internal detail::_control_block to associate with the shared_ptr. May be nullptr to indicate no control block.</param>
	explicit shared_ptr(detail::_control_block* blk) : _dta(blk) {}

	template<typename U>
	shared_ptr(const shared_ptr<U>& px, typename sys::sp_enable_if_convertible<U, T>::type = sys::sp_empty())
		: _dta(((const shared_ptr<T>*)& px)->_dta)
	{
		((const shared_ptr<T>*) & px)->_dta->get_reference_count()->operator++();
	}
	shared_ptr(std::nullptr_t) : _dta(nullptr) {}

	/// <summary>
	/// Default constructor that creates an empty shared_ptr by initializing its internal pointer to nullptr.
	/// </summary>
	shared_ptr() : _dta(nullptr) {}

	/// <summary>
	/// Move constructor that transfers ownership from another shared_ptr.
	/// </summary>
	/// <param name="other">An rvalue reference to the source shared_ptr whose internal pointer is moved into the new instance. After construction, other is left in a null state (its internal pointer is set to NULL).</param>
	shared_ptr(shared_ptr&& other) {
		this->_dta = other._dta;
		other._dta = NULL;
	}

	/// <summary>
	/// Copy constructor that creates a new shared_ptr sharing ownership of the resource managed by other. Validates the source and increments the shared reference count; may throw on invalid input.
	/// </summary>
	/// <param name="other">The shared_ptr to copy from. Must be non-null and already in shared state. Passing the same object (self) or a non-shared or null instance will cause an exception to be thrown.</param>
	shared_ptr(const shared_ptr& other) : _dta(other._dta) {
		if (&other == this) {
			THROW(sys::invalid_operation_error("Illegal construction call"));
			return;
		}
		
		unexpect((!this->is_null()) && "constructed on invalid memory.");

		this->_dta = NULL;

		// Update: Disable null validation on copy, since we also need to "copy" those when working with lists.
		// Avoid failing when collections copies this.
		//if (other.is_null()) {
			//THROW(sys::null_reference_error("Expected 'other' to be non-null"));
		//	return;
		//}
		
		if (!other.is_null()) {
			if (!other._dta->is_shared()) {
				THROW(sys::invalid_operation_error("'other' was not shared."));
				return;
			}
			this->_dta = other._dta;
			other._dta->get_reference_count()->operator++();
		}
	}

	/// <summary>
	/// Returns whether the underlying data is unique.
	/// </summary>
	/// <returns>true if _dta is non-null and its unique() method returns true; otherwise false.</returns>
	inline bool unique() const {
		return _dta ? _dta->unique() : false;
	}

	/// <summary>
	/// Checks whether the underlying data is null.
	/// </summary>
	/// <returns>true if the internal _dta pointer is null or if _dta->is_null() returns true; otherwise false.</returns>
	inline bool is_null() const {
		return  _dta ? _dta->is_null() : true;
	}

	/// <summary>
	/// Returns the object's reference count as a 32-bit signed integer. Handles null-object and missing-counter cases with sentinel values.
	/// </summary>
	/// <returns>The reference count converted to int32_t. Returns 0 if the object is null (is_null() is true). Returns -1 if the internal reference-counter pointer is null (get_reference_count() == NULL). Otherwise returns the value of get_reference_count()->operator std::size_t() cast to int32_t (possible truncation if the count exceeds int32_t range).</returns>
	inline int32_t ref_count() const {
		if (is_null()) return 0;
		if (this->_dta->get_reference_count() == NULL) return -1;
		return (int32_t)this->_dta->get_reference_count()->operator std::size_t();
	}

	/// <summary>
	/// Releases control of the object's internal data by calling sys::detail::factory::release_control(this->_dta).
	/// </summary>
	void reset() {
		sys::detail::factory::release_control(this->_dta);
	}
	
	/// <summary>
	/// Move assignment operator for shared_ptr that transfers ownership from another shared_ptr.
	/// </summary>
	/// <param name="other">An rvalue reference to the source shared_ptr. Ownership of the managed object is moved from other to this; other._dta is set to NULL after the operation. If other is the same object as this, no changes are made.</param>
	/// <returns>A reference to this shared_ptr after the move assignment.</returns>
	shared_ptr& operator =(shared_ptr&& other) {
		if (&other == this) return;
		reset();
		this->_dta = other._dta;
		other._dta = NULL;
		return *this;
	}

	/// <summary>
	/// Copy assignment operator that releases current ownership and makes this shared_ptr share ownership of the managed object held by other.
	/// </summary>
	/// <param name="other">The shared_ptr to assign from. If other is the same object as this, the operator returns without modifying state.</param>
	/// <returns>A reference to this shared_ptr after assignment.</returns>
	shared_ptr& operator =(const shared_ptr& other) {
		if (&other == this) return *this;
		reset();
		if (!other.is_null()) {
			this->_dta = other._dta;
			this->_dta->get_reference_count()->operator++();
		}
		return *this;
	}

	/// <summary>
	/// Returns a pointer to the object's underlying data if the object is not null; otherwise returns NULL. The returned pointer is a const pointer and does not transfer ownership.
	/// </summary>
	/// <returns>A const pointer to the underlying T data when the object is not null; otherwise NULL. The pointer remains valid only while the object and its internal storage exist and are not modified.</returns>
	const T* ptr() const { return (!is_null()) ? (T*)this->_dta->data() : NULL; }
	

	/// <summary>
	/// Returns a pointer to the object's underlying data if the object is not null; otherwise returns NULL. The returned pointer is a const pointer and does not transfer ownership.
	/// </summary>
	/// <returns>A const pointer to the underlying T data when the object is not null; otherwise NULL. The pointer remains valid only while the object and its internal storage exist and are not modified.</returns>
	T* ptr() { return (!is_null()) ? (T*)this->_dta->data() : NULL; }




	/// <summary>
	/// Returns a pointer to the object's underlying data if the object is not null; otherwise returns NULL. The returned pointer is a const pointer and does not transfer ownership.
	/// </summary>
	/// <returns>A const pointer to the underlying T data when the object is not null; otherwise NULL. The pointer remains valid only while the object and its internal storage exist and are not modified.</returns>
	T* operator ->() { return ptr(); }


	/// <summary>
	/// Returns a pointer to the object's underlying data if the object is not null; otherwise returns NULL. The returned pointer is a const pointer and does not transfer ownership.
	/// </summary>
	/// <returns>A const pointer to the underlying T data when the object is not null; otherwise NULL. The pointer remains valid only while the object and its internal storage exist and are not modified.</returns>
	const T* operator ->() const{ return ptr(); }


	void _unsafe_assign(detail::_control_block* blk) {
		this->_dta = blk;
	}

	

	~shared_ptr() {
		reset();
	}
	

};
template<typename T>
sys::shared_ptr<T> new_shared(){
	auto handle = newx::allocate<T>(sys::default_allocator, true);
	
	handle.activate();

	return sys::shared_ptr<T>(handle._unsafe_pop());
}

_SYS_ENS