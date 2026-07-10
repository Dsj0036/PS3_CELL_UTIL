#pragma once
#include "_ns.h"
#include <types.h>
#include "memory.h"
#include "abort.h"
#include "unexpect.h"
#include "iter.h"
#include "throw.h"
#include "traits.h"
_SYS_NS
#define _SYS_ARRAY_DEBUG false

template<typename T>
class array 
	// not equatable yet, also implement shallow copy and deep clone.
{
public:
	struct unsafe_copy_tag {
		friend array<T>;
		T* dta;
		int sz;

	};
private:
	T* _px;			// ptr to collected storage.
	int _length;	// fixed length of the collection.

	array(unsafe_copy_tag t) : _px(t.dta), _length(t.sz) {
	}

public:
	array(std::nullptr_t) {
		this->_px = nullptr;
		this->_length = 0;
	}
	// Construct called by declr implicitly.
	array() {

#if _SYS_ARRAY_DEBUG
		_sys_printf("array()\n");
#endif
		_px = nullptr;
		_length = -1;
	}
	array(const T* other, int count) : array() {

#if _SYS_ARRAY_DEBUG
		_sys_printf("array(T* other: %x, int count: %i)\n", other, count);
#endif
		if (!other) {
			throw "Invalid argument specified: 'T* other' was null";

		}
		_tidy(count + 1, other, count);
	}
	array(size_t capacity) : array() {
		__expect(capacity > 0 && capacity < 0xffffff);
		_tidy(capacity);
		this->_length = capacity;
	}
	array(array&& other) {
		this->_px = other._px;
		this->_length = other._length;
		other._px = 0;
		other._length = 0;
	}
	array(const array& other) : array() {
		if (!other._disposed())
			_tidy(other._length, other._px, other._length);
	}
	//array(const std::initializer_list<T>& initializer) : array() {
	//	_tidy(initializer.size(), initializer.begin(), static_cast<int>(initializer.size()));
	//
	T* _assign(size_t idx, const T& srcCloneable) {
		if (_disposed()) {
			FAIL "array where disposed already.";
		}

#if _SYS_ARRAY_DEBUG
		_sys_printf("array::_assign(%i, %x)\n", idx, &srcCloneable);
#endif
		if (idx >= static_cast<size_t>(_length)) {

			FAIL "Index out of bounds in array::_assign";
		}

		T* p = &_px[idx];
		
		unexpect(p == nullptr);

		//if (sys::is_trivial())
			//*p = srcCloneable;
		//else
			new (p) T(srcCloneable);

		return p;
	}

	static T* _newStrg(size_t cap, size_t align_boundary = 4) {
		if (cap == 0) {
			FAIL "Cannot allocate 0 elements.";

		}
		void* object = sys::memalign(align_boundary, cap * sizeof(T));
		if (!object) {
			
			//throw "Cannot allocate more memory, object is 0x%x", object);
		}
		return (T*)object;
	}

	T& operator[](size_t idx) { return at(idx); }
	const T& operator[](size_t indx)const { return at(indx); }


	//array<T>& operator = (const std::initializer_list<T>& other) {
	//	_release();
	//	_tidy(other.size() + 1, other.begin(), other.size());
	//	return *this;
	//}
	array<T>& set(const T* other, int32_t size) {
		_release();
		_tidy(size + 32, other, size);
		return *this;
	}

	const T& at(size_t idx) const {
		if (_disposed()) {
			FAIL "array where disposed already.";

		}
		if (idx >= static_cast<size_t>(_length)) {
#ifdef DEBUG
			sys::dbg::writeLine("Index: %d - Length: %d", idx, _length);
#endif
			//sys::abort_expresive(EINVAL, "Index out of range");
			FAIL "Index out of range";
		}
		return _px[idx];
	}
	T& at(size_t idx) {
		if (_disposed()) {
			FAIL "array where disposed already.";
		}
		if (idx >= static_cast<size_t>(_length)) {
			FAIL "Index out of range";

		}
		return _px[idx];
	}
	void destroy(size_t idx) {
		if (_disposed())
		{
			FAIL "array where disposed already.";
		}
		if (idx >= static_cast<size_t>(_length)) {
			FAIL "Index out of range";
		}
		unexpect(_px == nullptr);
		_destroy(_px[idx]);
	}
	T* begin() {
		if (_disposed()) {
			FAIL "array where disposed already.";

		}

		return _px;
	}
	const T* begin() const {
		if (_disposed())
		{
			FAIL "array where disposed already.";
		}
		return _px;
	}
	array<T> clone() const {
		if (_disposed()) return array<T>();
		return array<T>(_px, _length);
	}

	T* end() {
		return _px + _length;
	}
	const T* end() const { return _px + _length; }


	int size()const { return _length == -1 ? 0 : _length; }

	bool _disposed() const {

		return this->_px == nullptr || this->_length == -1;
	}
	void _dispose() {
		if (_disposed()) {
			throw "array where disposed already.";
		}

		_release();
	}

	static sys::array<T> unsafe(T* p, int size) {
		return unsafe_copy_tag(p, size);
	}
	void unsafe_init(int capacity) {
		_sys_assert(capacity > 0);
		_tidy(capacity, nullptr, capacity);

	}
protected:

	void _release() {

#if _SYS_ARRAY_DEBUG
		_sys_printf("array::_release. [px=%x]\n", _px);
#endif
		if (_px) {
			for (int i = 0; i < _length; ++i)
				_destroy(_px[i]);

			sys::free(_px);
			_px = nullptr;
			_length = -1;
		}

	}
	void _destroy(T& elem) {
			elem.~T();

#if _SYS_ARRAY_DEBUG
		_sys_printf("array::_destroy(T& elem: %x)\n", &elem);
#endif
		sys::memset(&elem, 0u, sizeof(T));
	}

	void _tidy(int elemCapct, const T* otherCollection = nullptr, size_t otherCollectionLen = 0) {

#if _SYS_ARRAY_DEBUG
		_sys_printf("array::_tidy(%i, %x, %x)\n", elemCapct, otherCollection, otherCollectionLen);
#endif
		if (this->_px == nullptr && (this->_length == -1 || this->_length == 0)) {

			if (otherCollectionLen && elemCapct < otherCollectionLen)
				elemCapct = otherCollectionLen;

			this->_px = _newStrg(elemCapct);
			this->_length = otherCollectionLen;

			sys::memset(this->_px, 0, sizeof(T) * elemCapct);

			if (otherCollection && otherCollectionLen) {
				for (size_t idx = 0; idx < otherCollectionLen; idx++)
					_assign(idx, otherCollection[idx]);
			}

		}
		else {
			FAIL "Attempted to tidy already initialized array";
		}
	}
public:
	virtual ~array() {
#if _SYS_ARRAY_DEBUG
		_sys_printf("array::~array. [px=%x, length=%i]\n", _px, _length);
#endif
		_release();
	}
};

extern std::nullptr_t empty_array;


_SYS_ENS