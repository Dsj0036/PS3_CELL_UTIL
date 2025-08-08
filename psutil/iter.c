#pragma once
#include "iter.h"
#pragma once
namespace sys {

	template<typename T>
	struct iter;


	template <typename T> T* iter<T>::begin() { return _ptr; }

	template <typename T> const T* iter<T>::begin() const { return _ptr; }

	template <typename T> T* iter<T>::end() { return _ptr + _size; }
	template <typename T> const T* iter<T>::end() const { return _ptr + _size; }

	template<typename T> size_t iter<T>::size() const { return _size; }
	template<typename T> T& iter<T>:: operator[](size_t i) { return _ptr[i]; }
	template<typename T> const T& iter<T>::operator[](size_t i) const { return _ptr[i]; }

	template<typename T> bool iter<T>::not_null() const { return _ptr != nullptr; }


};