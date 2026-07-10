#pragma once
#ifndef __SYS_TRAITS_H__
#define __SYS_TRAITS_H__
#include <sys\types.h>

#define INT8_MIN	(-0x7f - _C2)
#define INT16_MIN	(-0x7fff - _C2)
#define INT32_MIN	(-0x7fffffff - _C2)

#define INT8_MAX	0x7f
#define INT16_MAX	0x7fff
#define INT32_MAX	0x7fffffff
#define UINT8_MAX	0xff
#define UINT16_MAX	0xffff
#define UINT32_MAX	0xffffffff

#define INT_LEAST8_MIN		(-0x7f - _C2)
#define INT_LEAST16_MIN		(-0x7fff - _C2)
#define INT_LEAST32_MIN		(-0x7fffffff - _C2)

#define INT_LEAST8_MAX		0x7f
#define INT_LEAST16_MAX		0x7fff
#define INT_LEAST32_MAX		0x7fffffff
#define UINT_LEAST8_MAX		0xff
#define UINT_LEAST16_MAX	0xffff
#define UINT_LEAST32_MAX	0xffffffff

#define INT_FAST8_MIN		(-0x7fffffff - _C2)
#define INT_FAST16_MIN		(-0x7fffffff - _C2)
#define INT_FAST32_MIN		(-0x7fffffff - _C2)

#define INT_FAST8_MAX		0x7fffffff
#define INT_FAST16_MAX		0x7fffffff
#define INT_FAST32_MAX		0x7fffffff
#define UINT_FAST8_MAX		0xffffffff
#define UINT_FAST16_MAX		0xffffffff
#define UINT_FAST32_MAX		0xffffffff
/// Specifies than an class should not be instanced rather than being referenced.
#define _SYS_UNINITIALIZED_OPT_ 
namespace sys {
	class uninitialized_opt_t final{
		int __zero{0};
	public:
		uninitialized_opt_t(){}
	};
	template <class _Ty, _Ty _Val>
	struct integral_constant {
		static constexpr _Ty value = _Val;

		using value_type = _Ty;
		using type = integral_constant;

		constexpr operator value_type() const noexcept {
			return value;
		}

		constexpr value_type operator()() const noexcept {
			return value;
		}
	};
	template<typename T>
	struct remove_pointer {
		typedef T type;
	};

	template<typename T>
	struct remove_pointer<T*> {
		typedef T type;
	};
	template <bool _Val>
	using bool_constant = integral_constant<bool, _Val>;


	template<typename, typename> struct is_same_v { static const bool value = false; };
	template<typename T1> struct is_same_v<T1, T1> { static const bool value = true; };

	template <class _Ty1, class _Ty2>
	struct is_same : bool_constant<is_same_v<_Ty1, _Ty2>::value> {};



	template <class _Ty>
	struct remove_reference {
		using type = _Ty;
		using _Const_thru_ref_type = const _Ty;
	};

	template <class _Ty>
	struct remove_reference<_Ty&> {
		using type = _Ty;
		using _Const_thru_ref_type = const _Ty&;
	};

	template <class _Ty>
	struct remove_reference<_Ty&&> {
		using type = _Ty;
		using _Const_thru_ref_type = const _Ty&&;
	};

	template <class _Ty>
	using remove_reference_t = typename remove_reference<_Ty>::type;



	using true_type = bool_constant<true>;
	using false_type = bool_constant<false>;

	template <bool _Test, class _Ty = void>
	struct enable_if {}; // no member "type" when !_Test

	template <class _Ty>
	struct enable_if<true, _Ty> { // type is _Ty for _Test
		using type = _Ty;
	};
	template <bool _Test, class _Ty = void>
	using enable_if_t = typename enable_if<_Test, _Ty>::type;


	template <bool _Test, class _Ty1, class _Ty2>
	struct conditional { // Choose _Ty1 if _Test is true, and _Ty2 otherwise
		using type = _Ty1;
	};


	template <class _Ty1, class _Ty2>
	struct conditional<false, _Ty1, _Ty2> {
		using type = _Ty2;
	};

	template <bool _Test, class _Ty1, class _Ty2>
	using conditional_t = typename conditional<_Test, _Ty1, _Ty2>::type;

	template<typename T, typename... Ts>
	struct is_any_of : false_type {};

	template<typename T, typename U, typename... Ts>
	struct is_any_of<T, U, Ts...>
		: sys::conditional<
		sys::is_same<T, U>::value,
		sys::true_type,
		is_any_of<T, Ts...>
		>::type {
	};

	// 
	template <class _Ty, class = void>
	struct _Add_pointer { // add pointer (pointer type cannot be formed)
		using type = _Ty;
	};

	template <class... _Types>
	using void_t = void;

	template <class _Ty>
	struct _Add_pointer<_Ty, void_t<remove_reference_t<_Ty>*>> { // (pointer type can be formed)
		using type = remove_reference_t<_Ty>*;
	};

	template <class _Ty>
	struct add_pointer {
		using type = typename _Add_pointer<_Ty>::type;
	};

	template <class _Ty>
	using add_pointer_t = typename _Add_pointer<_Ty>::type;


	template<class _Ty>
	struct is_array_t {
		static constexpr bool value = false;
	};

	template<class _Ty, size_t _Nx>
	struct is_array_t<_Ty[_Nx]> {
		static constexpr bool value = true;
	};
	template<class _Ty>
	struct is_array_t<_Ty[]> {
		static constexpr bool value = true;
	};

	template<typename _Ty>
	struct is_array : bool_constant< is_array_t<_Ty>::value> {

	};

	template <class _Ty>
	struct remove_const { // remove top-level const qualifier
		using type = _Ty;
	};

	template <class _Ty>
	struct remove_const<const _Ty> {
		using type = _Ty;
	};


	template <class _Ty>
	using remove_const_t = typename remove_const<_Ty>::type;


	template <class _Ty>
	struct remove_volatile { // remove top-level volatile qualifier
		using type = _Ty;
	};

	template <class _Ty>
	struct remove_volatile<volatile _Ty> {
		using type = _Ty;
	};

	template <class _Ty>
	using remove_volatile_t = typename remove_volatile<_Ty>::type;

	template <class _Ty>
	struct remove_cv { // remove top-level const and volatile qualifiers
		using type = _Ty;

		template <template <class> class _Fn>
		using _Apply = _Fn<_Ty>; // apply cv-qualifiers from the class template argument to _Fn<_Ty>
	};

	template <class _Ty>
	struct remove_cv<const _Ty> {
		using type = _Ty;

		template <template <class> class _Fn>
		using _Apply = const _Fn<_Ty>;
	};

	template <class _Ty>
	struct remove_cv<volatile _Ty> {
		using type = _Ty;

		template <template <class> class _Fn>
		using _Apply = volatile _Fn<_Ty>;
	};

	template <class _Ty>
	struct remove_cv<const volatile _Ty> {
		using type = _Ty;

		template <template <class> class _Fn>
		using _Apply = const volatile _Fn<_Ty>;
	};

	template <class _Ty>
	using remove_cv_t = typename remove_cv<_Ty>::type;


	template <class _Ty>
	struct remove_extent { // remove array extent
		using type = _Ty;
	};

	template <class _Ty, size_t _Ix>
	struct remove_extent<_Ty[_Ix]> {
		using type = _Ty;
	};

	template <class _Ty>
	struct remove_extent<_Ty[]> {
		using type = _Ty;
	};

	template <class _Ty>
	using remove_extent_t = typename remove_extent<_Ty>::type;

	template <class _Ty>
	struct remove_all_extents { // remove all array extents
		using type = _Ty;
	};

	template <class _Ty, size_t _Ix>
	struct remove_all_extents<_Ty[_Ix]> {
		using type = typename remove_all_extents<_Ty>::type;
	};

	template <class _Ty>
	struct remove_all_extents<_Ty[]> {
		using type = typename remove_all_extents<_Ty>::type;
	};

	template <class _Ty>
	using remove_all_extents_t = typename remove_all_extents<_Ty>::type;


	template <class _Ty>
	struct is_integral_t {

		static constexpr bool value = is_any_of<remove_cv_t<_Ty>, bool, char, signed char, unsigned char, wchar_t,
			char16_t, char32_t, short, unsigned short, int, unsigned int, long, unsigned long, long long, unsigned long long>::value;

	};


	template <class _Ty>
	struct is_char_t {
		static constexpr bool value = is_any_of<remove_cv_t<_Ty>, char, signed char, unsigned char, wchar_t, char16_t, char32_t>::value;
	};
	template <class _Ty>
	struct is_floating_point_t {
		static constexpr bool value = is_any_of<remove_cv_t<_Ty>, float, double, long double>::value;
	};

	template <class _Ty>
	struct is_integral : bool_constant<is_integral_t<_Ty>::value> {};

	template <class _Ty>
	struct is_floating_point : bool_constant<is_floating_point_t<_Ty>::value> {};

	template <class _Ty>
	struct is_arithmetic : bool_constant<is_integral_t<_Ty>::value || is_floating_point_t<_Ty>::value> {};

	template <class _Ty>
	struct is_nonbool_integral : bool_constant<is_integral<_Ty>::value && !is_same_v<remove_cv_t<_Ty>, bool>::value> {

	};

	template <class _Ty>
	using _Const_thru_ref = typename remove_reference<_Ty>::_Const_thru_ref_type;

	template <class _Ty, bool = is_integral_t<_Ty>::value>
	struct _Sign_base { // determine whether integral type _Ty is signed or unsigned
		using _Uty = remove_cv_t<_Ty>;

		static constexpr bool _Signed = static_cast<_Uty>(-1) < static_cast<_Uty>(0);
		static constexpr bool _Unsigned = !_Signed;
	};

	template <class _Ty>
	struct _Sign_base<_Ty, false> { // floating-point _Ty is signed
		// non-arithmetic _Ty is neither signed nor unsigned
		static constexpr bool _Signed = is_floating_point<_Ty>::value;
		static constexpr bool _Unsigned = false;
	};

	template<class _Ty>
	struct is_const_v {
		static constexpr bool value = false;
	};
	template<class _Ty>
	struct is_const_v<const _Ty> {
		static constexpr bool value = true;
	};

	template<class _Ty>
	struct is_const : bool_constant<is_const_v<_Ty>::value> {};

	template <class _Ty>
	struct is_signed : bool_constant<_Sign_base<_Ty>::_Signed> {}; // determine whether _Ty is a signed type

	template <class _Ty>
	struct is_unsigned : bool_constant<_Sign_base<_Ty>::_Unsigned> {}; // determine whether _Ty is an unsigned type


	template<class>
	struct is_reference_v {
		static constexpr bool value = false; // determine whether type argument is a reference
	};
	template <class _Ty>
	struct is_reference_v<_Ty&> {
		static constexpr bool value = true; // determine whether type argument is a reference
	};
	template <class _Ty>
	struct is_reference_v<_Ty&&> {
		static constexpr bool value = true; // determine whether type argument is a reference
	};
	template <class _Ty>
	struct is_reference : bool_constant<is_reference_v<_Ty>::value> {};

	template <bool Cond, class TTrue, class TFalse>
	struct _Select {
		using type = TTrue;
	};

	template <class TTrue, class TFalse>
	struct _Select<false, TTrue, TFalse> {
		using type = TFalse;
	};




	template<class T, unsigned N = 0>
	struct extent : integral_constant<std::size_t, 0> {};

	template<class T>
	struct extent<T[], 0> : integral_constant<std::size_t, 0> {};

	template<class T, unsigned N>
	struct extent<T[], N> : extent<T, N - 1> {};

	template<class T, std::size_t I>
	struct extent<T[I], 0> : integral_constant<std::size_t, I> {};

	template<class T, std::size_t I, unsigned N>
	struct extent<T[I], N> : extent<T, N - 1> {};


	template <class _Ty>
	struct alignment_of : integral_constant<size_t, alignof(_Ty)> {}; // determine alignment of _Ty

	template<class _Ty>
	struct is_function_v {
		static constexpr const bool value = !is_reference_v<_Ty>::value && !is_const_v<const _Ty>::value;
	};

	template <class _Ty>
	struct is_function : bool_constant<is_function_v<_Ty>::value> {

	};

	template <class T>
	struct decay {
	private:
		using U = remove_reference_t<T>;

		using px = typename _Select<is_function_v<U>::value, typename sys::_Add_pointer<U>, remove_cv_t<U>>::type;

	public:
		using type = typename _Select<is_array_t<U>::value, typename sys::_Add_pointer<remove_extent_t<U>>::type, px>::type;
	};

	// is_bool
	template<typename T> struct is_bool { static const bool value = false; };
	template<> struct is_bool<bool> { static const bool value = true; };

	// is_double
	template<typename T> struct is_double { static const bool value = false; };
	template<> struct is_double<double> { static const bool value = true; };

	// is_void
	template<typename T> struct is_void { static const bool value = false; };
	template<> struct is_void<void> { static const bool value = true; };


	template<typename T> struct is_const_char { static const bool value = false; };
	template<> struct is_const_char<const char*> { static const bool value = true; };


	template<class T> struct is_pointer { static const bool value = false; };
	template<class T> struct is_pointer<T*> { static const bool value = true; };
	template<class T> struct is_pointer<T* const> { static const bool value = true; };
	template<class T> struct is_pointer<T* volatile > { static const bool value = true; };
	template<class T> struct is_pointer<T* const volatile> { static const bool value = true; };


	template<class _Ty>
	struct is_null_pointer : bool_constant<is_same_v<remove_cv_t<_Ty>, std::nullptr_t>::value> {};

	template<class _Ty>
	struct is_fundamental : bool_constant<is_integral_t<_Ty>::value || is_floating_point_t<_Ty>::value ||
		is_same_v<remove_cv_t<_Ty>, void>::value || is_null_pointer<_Ty>::value> {
	};

	template <class _Ty>
	struct is_compound : bool_constant<!is_fundamental<_Ty>::value> {}; // determine whether _Ty is a compound type

	template<class>
	struct is_lvalue_reference_v {
		static constexpr bool value = false; // determine whether type argument is a reference
	};
	template <class _Ty>
	struct is_lvalue_reference_v<_Ty&> {
		static constexpr bool value = true; // determine whether type argument is a reference
	};

	template <class _Ty>
	struct is_lvalue_reference : bool_constant<is_lvalue_reference_v<_Ty>::value> {};

	template<class>
	struct is_rvalue_reference_v {
		static constexpr bool value = false; // determine whether type argument is a reference
	};
	template <class _Ty>
	struct is_rvalue_reference_v<_Ty&&> {
		static constexpr bool value = true; // determine whether type argument is a reference
	};

	template <class _Ty>
	struct is_rvalue_reference : bool_constant<is_lvalue_reference_v<_Ty>::value> {};


	template <class _Bitmask>
	constexpr bool _Bitmask_includes_any(_Bitmask _Left, _Bitmask _Elements) noexcept {
		return (_Left & _Elements) != _Bitmask{};
	}

	template <class _Bitmask>
	constexpr bool _Bitmask_includes_all(_Bitmask _Left, _Bitmask _Elements) noexcept {
		return (_Left & _Elements) == _Elements;
	}



	using destructor_function = void(*)(void*);

	template<typename T>
	static void typed_destructor(void* p) {
		if (sys::is_compound<T>::value)
			((T*)p)->~T();

		// destroy an context-unknown fundamental type, e.g: int.
		return;

	}

	template<typename T>
	static constexpr size_t size_of(T* p) {
		return sizeof(T);
	}
	static constexpr size_t size_of(void* p) {
		return 0;
	}

	template<typename T> static sys::enable_if_t<sys::is_fundamental<T>::value> execute_dtor(T* any) {

	}
	template<class T>
	static sys::enable_if_t<sys::is_compound<T>::value> execute_dtor(T* any) {
		typed_destructor<T>(any);
	}



	template<size_t Bits>
	struct select_uint;

	template<>
	struct select_uint<8>
	{
		using type = uint8_t;
	};

	template<>
	struct select_uint<16>
	{
		using type = uint16_t;
	};

	template<>
	struct select_uint<32>
	{
		using type = uint32_t;
	};

	template<size_t Bits>
	using select_uint_t = typename select_uint<Bits>::type;

	template<size_t Value>
	struct smallest_uint
	{
		using type =
			typename conditional<
			(Value <= UINT8_MAX), uint8_t,
			typename conditional<
			(Value <= UINT16_MAX), uint16_t,
			uint32_t
			>::type
			>::type;
	};

	template<size_t Value>
	using smallest_uint_t = typename smallest_uint<Value>::type;
}

#endif