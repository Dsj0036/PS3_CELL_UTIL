#pragma once
#include "xtypes.h"
namespace sys {

	template<typename T>
	struct iter {
		T* _ptr;
		size_t _size = 0;


		template<size_t N>
		iter(T(&array)[N]) : _ptr(array), _size(N) {}

		iter(T* ptr, size_t num) : _ptr(ptr), _size(num) {}

		iter(std::nullptr_t) : _ptr(nullptr), _size(0) {}

		T* begin();
		const T* begin() const;
		T* end();
		const T* end() const;

		size_t size() const;
		T& operator[](size_t i);
		const T& operator[](size_t i) const;

		bool not_null() const;

		static const iter<T> null_iter;
	};
	template<typename T>
	const iter<T> iter<T>::null_iter{ nullptr };


}