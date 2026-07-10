#pragma once
#include "traits.h"


namespace sys{

	template<class _Ty> 
	inline sys::enable_if_t<sys::is_reference<_Ty>::value, _Ty>
		max(_Ty left, _Ty right){
		return ((left < right) ? right : left);
	}

	template<class _Ty>
	inline sys::enable_if_t<sys::is_reference<_Ty>::value, _Ty>
		min(_Ty left, _Ty right) {
		return ((right < left) ? right : left);
	}

	template<class _Ty> inline
		_Ty max(_Ty _Left, _Ty _Right)
	{
		return ((_Left < _Right) ? _Right : _Left);
	}
	template<class _Ty> inline
		_Ty min(_Ty _Left, const _Ty _Right)
	{
		return ((_Right < _Left) ? _Right : _Left);
	}
	template<typename _Ty, typename R> inline R left_or(_Ty* left, R right) {
		return left == NULL ? right == NULL ? 0 : right : left;
}

	template<typename _Ty, typename R> inline R select(bool expression, _Ty left, R right) {
		return expression ? left : right;
	}

	template <typename T>
	inline T* fundamental_trim_excess(T* heap_array, size_t heap_size, size_t new_size)
	{
		if (heap_size <= new_size)
			return heap_array;

		T* new_p = new T[new_size];

		sys::memcpy(new_p, heap_array, sizeof(T) * new_size);
		delete[] heap_array;
		return new_p;
	}

	bool ends_with(
		const char* path,
		size_t path_len,
		const char* suffix,
		size_t suffix_len);

	double taylor_square(double x);
	int rand();

	int floor(double x);
	inline bool is_alpha(int c)
	{
		if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
			return true;
		return false;
	}
	inline bool isalphanum(char ch) {
		return  ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9')) && (!(ch != '-' && ch != '_'));
	}
	inline bool isnum(int c) {
		if (c >= '0' && c <= '9')
			return true;
		return false;
	}


	size_t count_occurrences(char target, const char* first, const char* last);

	bool is_range_numeric_fast(const char* start, const char* end);
	bool is_range_precission_fast(const char* str, const char* end);
}