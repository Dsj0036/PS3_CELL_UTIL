#pragma once
#include "_ns.h"
#include "lwstring.h"
#include "memchr.h"
_SYS_NS

template<typename T>
struct lexical_cast_traits {
	static T cast(const lwstring& input) {
		// add/update: this is INTERFACE-LIKE; not implemented behaviour.
		// we need to throw here evidently, dont know how i missed this.
		const char* f = __FUNCTION__;
		sys::printf("%s\n\tNot implemented for the specified type.", f);
		sys::throw_pure_virtual_usage();
		//return T();
	}
};

template<typename T>
T lexical_cast(const lwstring& input) {
	return lexical_cast_traits<T>::cast(input);
}

template<typename T>
T lexical_cast(const char* input, size_t length) {
	lwstring fo{};
	fo.assign(input, length);
	return lexical_cast<T>(fo);
}
template<> unsigned long long lexical_cast(const sys::lwstring&);
template<> bool lexical_cast(const sys::lwstring&);
template<> double lexical_cast(const sys::lwstring&);
template<> int lexical_cast(const sys::lwstring&);

_SYS_ENS

#define _SYS_DEFINE_LEXICAL_CAST(T, BODY) \
	template<> \
	struct sys::lexical_cast_traits<T> { \
		static T cast(const sys::lwstring& input){BODY}}