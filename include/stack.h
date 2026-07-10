#pragma once
#include "_ns.h"
#include "array.h"
#include "assert.h"
_SYS_NS
template<typename T, class size_type = size_t>
class stack {
	T* _ptr;
	size_type _size;
	size_type _capacity;

public:
	stack(size_type capacity) : _ptr(nullptr), _size(0), _capacity(0) {
		ensure_capacity(capacity);
	}
	stack() : stack(8) {}

	stack(const stack&) = delete;
	stack& operator=(const stack&) = delete;

	stack(stack&& other) noexcept
		: _ptr(other._ptr), _size(other._size), _capacity(other._capacity) {
		other._ptr = nullptr;
		other._size = 0;
		other._capacity = 0;
	}
	stack& operator=(stack&& other) noexcept {
		if (this != &other) {
			clear();
			operator delete[](_ptr);
			_ptr = other._ptr;
			_size = other._size;
			_capacity = other._capacity;
			other._ptr = nullptr;
			other._size = 0;
			other._capacity = 0;
		}
		return *this;
	}

	T& push(const T& value) {
		ensure_capacity(_size + 1);
		new(&_ptr[_size]) T(value);
		return _ptr[_size++];
	}

	T& push(T&& value) {
		ensure_capacity(_size + 1);
		new(&_ptr[_size]) T(sys::move(value));
		return _ptr[_size++];
	}

	T& back() {
		_sys_assert(_size > 0);
		return _ptr[_size - 1];
	}
	const T& back() const {
		_sys_assert(_size > 0);
		return _ptr[_size - 1];
	}
	T& back(size_type count) {
		_sys_assert(count < _size);
		return _ptr[_size - count - 1];
	}
	const T& back(size_type count) const {
		_sys_assert(count < _size);
		return _ptr[_size - count - 1];
	}

	T& top() { return back(); }
	const T& top() const { return back(); }

	bool empty() const { return _size == 0; }

	T pop() {
		_sys_assert(_size > 0);
		T value = _ptr[--_size];
		_ptr[_size].~T();
		return value;
	}

	size_type size() const { return _size; }
	size_type capacity() const { return _capacity; }

	bool ensure_capacity(size_type capacity) {
		if (_capacity >= capacity) {
			return false;
		}

		size_type new_capacity = _capacity;
		if (new_capacity == 0) new_capacity = 1;
		while (new_capacity < capacity) {
			new_capacity *= 2;
		}

		T* new_ptr = static_cast<T*>(operator new[](new_capacity * sizeof(T)));

		for (size_type i = 0; i < _size; i++) {
			new(&new_ptr[i]) T(_ptr[i]);
		}

		for (size_type i = 0; i < _size; i++) {
			_ptr[i].~T();
		}

		operator delete[](_ptr);
		_ptr = new_ptr;
		_capacity = new_capacity;
		return true;
	}

	bool reserve(size_type count) {
		return ensure_capacity(_size + count);
	}

	void clear() {
		for (size_type i = 0; i < _size; i++) {
			_ptr[i].~T();
		}
		_size = 0;
	}

	T* data() { return _ptr; }
	const T* data() const { return _ptr; }

	~stack() {
		clear();
		operator delete[](_ptr);
	}
};

_SYS_ENS
