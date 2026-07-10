#pragma once
#include "traits.h"
namespace sys {

	template<typename T>
	T&& forward(
		typename remove_reference<T>::type& t) noexcept
	{
		return static_cast<T&&>(t);
	}

	template<typename T>
	T&& forward(
		typename sys::remove_reference<T>::type&& t) noexcept
	{
		static_assert(!sys::is_lvalue_reference<T>::value,
			"bad forward of lvalue");
		return static_cast<T&&>(t);
	}

}