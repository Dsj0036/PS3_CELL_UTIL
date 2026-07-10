#pragma once
#include <cstddef>
#include "counted_impl.h"   
#include "..\allocator.h"
#include "..\assert.h"
#include "..\unexpect.h"
_SYS_NS

extern void* shared_allocate_bytes(size_t b);
extern void shared_free_bytes(void* sp);
template<typename T>
class shared_ptr {
protected:
	T* ptr_ = nullptr;
	counted_impl* ctrl_ = nullptr;

	void release_control() noexcept {
		if (ctrl_) {
			__expect(ctrl_ != nullptr);

			if (ctrl_->release()) {
				// Last reference - delete the control block
				ctrl_->~counted_impl();
				sys::shared_free_bytes(ctrl_);
			}
			ctrl_ = nullptr;
			ptr_ = nullptr;
		}
	}

public:
	shared_ptr() noexcept = default;



	shared_ptr(std::nullptr_t) noexcept : ptr_(nullptr), ctrl_(nullptr) {}

	explicit shared_ptr(T* p, counted_impl* ctrl)
		: ptr_(p), ctrl_(ctrl)
	{
		__expect(p != nullptr);
		__expect(ctrl != nullptr);
		__expect(ctrl->count() >= 1);
	}

	template<typename U>
	shared_ptr(const shared_ptr<U>& other) noexcept
		: ptr_(static_cast<T*>(other.get())), ctrl_(other.control_ptr()) {
		if (ctrl_) ctrl_->retain();

		__expect(this->ptr_ != nullptr || other.is_null());
		__expect(control_ptr() != nullptr || other.control_ptr() == nullptr);
	}

	template<typename U>
	shared_ptr(shared_ptr<U>& other) noexcept
		: ptr_(static_cast<T*>(other.get())), ctrl_(other.control_ptr()) {
		if (ctrl_) ctrl_->retain();

		__expect(this->ptr_ != nullptr || other.is_null());
		__expect(control_ptr() != nullptr || other.control_ptr() == nullptr);
	}
	shared_ptr(const shared_ptr& other) noexcept
		: ptr_(other.ptr_), ctrl_(other.ctrl_)
	{
		if (ctrl_) ctrl_->retain();
	}

	shared_ptr(shared_ptr&& other) noexcept
		: ptr_(other.ptr_), ctrl_(other.ctrl_)
	{
		other.ptr_ = nullptr;
		other.ctrl_ = nullptr;
	}

	shared_ptr& operator=(const shared_ptr& other) noexcept {
		if (this != &other) {
			if (other.ctrl_) other.ctrl_->retain();
			release_control();
			ptr_ = other.ptr_;
			ctrl_ = other.ctrl_;
		}
		return *this;
	}

	//template<typename U>
	//shared_ptr& operator=(const shared_ptr<U>& other) noexcept {
	//	if (uint32_t(& other) != uint32_t(this)) {
	//		if (other.control_ptr()) other.control_ptr()->retain();
	//		release_control();
	//		ptr_ = static_cast<T*>(other.get());
	//		ctrl_ = other.control_ptr();
	//	}
	//	return *this;
	//}

	shared_ptr& operator=(shared_ptr&& other) noexcept {
		if (this != &other) {
			release_control();
			ptr_ = other.ptr_;
			ctrl_ = other.ctrl_;
			other.ptr_ = nullptr;
			other.ctrl_ = nullptr;
		}
		return *this;
	}

	~shared_ptr() noexcept {
		release_control();
	}

	uintptr_t address() const {
		return (uintptr_t)this->ptr_;
	}

	T* get() const noexcept { return ptr_; }
	T* get() noexcept { return ptr_; }
	counted_impl* control_ptr() const noexcept { return ctrl_; }
	explicit operator bool() const noexcept { return ptr_ != nullptr; }
	bool operator == (const shared_ptr& other) const {
		return this->ptr_ == other.ptr_;
	}
	bool operator == (const std::nullptr_t&) const {
		return this->is_null();
	}
	bool operator != (const std::nullptr_t) const {
		return !this->is_null();
	}
	bool operator != (const shared_ptr& other) const {
		return !operator==(other);
	}
	T* operator->() const noexcept { return ptr_; }
	T& operator*() const noexcept { return *ptr_; }

	void reset() noexcept {
		release_control();
	}
	sys::shared_ptr<T> clone() const {
		T* p = new T(this->ptr_);

		counted_impl* control = (counted_impl*)sys::shared_allocate_bytes(sizeof(counted_impl));
		_sys_memset(control, 0, sizeof(counted_impl));
		new (control)counted_impl(p, new_deleter);
		return sys::shared_ptr<T>(p, control);
	}
	bool unique() const { return this->use_count() == 1; }
	bool is_null() const noexcept { return ptr_ == nullptr; }
	int use_count() const noexcept { return ctrl_ ? ctrl_->count() : 0; }

	template<typename U>
	static shared_ptr<T> covariantFrom(shared_ptr<U>& base) {
		return shared_ptr<T>(static_cast<T*>(base.get()), base.control_ptr());
	}

	// Constructs new shared_ptr from raw pointer with default new_deleter.
	static shared_ptr newp(T* new_in) {
		counted_impl* control = (counted_impl*)sys::shared_allocate_bytes(sizeof(counted_impl));
		_sys_memset(control, 0, sizeof(counted_impl));
		new (control)counted_impl(new_in, new_deleter);
		return sys::shared_ptr<T>(new_in, control);
	}
};

template<class To, class From>
shared_ptr<To> pointer_cast(shared_ptr<From> other) {
	return shared_ptr<To>::covariantFrom(other);
}

template<typename T>
sys::shared_ptr<T> make_shared(T* p) {

	counted_impl* control = (counted_impl*)sys::shared_allocate_bytes(sizeof(counted_impl*));
	_sys_memset(control, 0, sizeof(counted_impl*));
	new (control)counted_impl(p, (counted_impl::deleter_t)+[](T * in) ->void{ delete in; });

	return sys::shared_ptr<T>(p, control);
}

_SYS_ENS
