#pragma once
#include <sys\types.h>
namespace sys {
	template< class Y, class T > struct convertible
	{
		typedef char(&yes)[1];
		typedef char(&no)[2];

		static yes f(T*);
		static no  f(...);

		enum _vt { value = sizeof((f)(static_cast<Y*>(0))) == sizeof(yes) };
	};

	template< class Y, class T > struct convertible< Y, T[] >
	{
		enum _vt { value = false };
	};

	template< class Y, class T > struct convertible< Y[], T[] >
	{
		enum _vt { value = convertible< Y[1], T[1] >::value };
	};

	template< class Y, std::size_t N, class T > struct convertible< Y[N], T[] >
	{
		enum _vt { value = convertible< Y[1], T[1] >::value };
	};

	struct sp_empty
	{
	};

	template< bool > struct sp_enable_if_convertible_impl;

	template<> struct sp_enable_if_convertible_impl<true>
	{
		typedef sp_empty type;
	};

	template<> struct sp_enable_if_convertible_impl<false>
	{
	};

	template< class Y, class T > struct sp_enable_if_convertible : public sp_enable_if_convertible_impl< convertible< Y, T >::value >
	{
	};
}