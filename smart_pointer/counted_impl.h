#pragma once
#include "..\_ns.h"
#include "..\unexpect.h"
#include "..\throw.h"
#include "..\exception.h"
#include "..\allocator.h"
#include "..\atomic_count.h"

_SYS_NS
template<typename T>
class shared_ptr;
class counted_impl {

	
	void* _ptr{nullptr};
	void(*deleter)(void*) {nullptr};
	sys::atomic_count _weak_count{0};
	sys::atomic_count _refcount{0};
	counted_impl(const counted_impl& other) {
		FAIL sys::invalid_operation_error("counted_impl is not copy constructible.");
		//__expect(false);
	}
	counted_impl& operator=(const counted_impl&) = delete;
public:
	using deleter_t = void(*)(void*);
	virtual ~counted_impl() = default;

	counted_impl() : _weak_count(0), _refcount{0} {
		_ptr = nullptr;
		deleter = nullptr;
	}
	explicit counted_impl(void* p, void(*deleter)(void*) = nullptr) : 
		_weak_count(1), _refcount{ 1}, _ptr(p), deleter(deleter) {
	}

	bool isnull() const noexcept { return _ptr == nullptr; }
	void* get() noexcept { return _ptr; }
	const void* get() const noexcept { return _ptr; }
	void* operator->() noexcept { return _ptr; }
	const void* operator->() const noexcept { return _ptr; }


	void weak_retain() noexcept {

		++_weak_count;
	}

	void weak_release() noexcept {
		--_weak_count;

		check_delete();
	}

	bool retain_if_nonzero() noexcept {
		if (_refcount == 0) return false;
		++_refcount;
		return true;
	}

	int32_t count() const { return _refcount; }


	int retain() { return ++_refcount; }

	int release() {
		if (_refcount > 0)
		{
			--_refcount;
			if (!_refcount)
				on_zero();

		}
		return _refcount;
	}



private:
	void on_zero() {
		if (_ptr) {
			if (deleter)
				deleter(_ptr);
			_ptr = nullptr;
		}
		--_weak_count;
		check_delete();
	}

	void check_delete() noexcept {
		if (_refcount == 0 && _weak_count == 0) {
			this->~counted_impl();
			sys::shared_free_bytes(this);
		}
	}
};


_SYS_ENS
