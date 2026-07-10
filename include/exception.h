#pragma once
#include "_ns.h"

_SYS_NS

template <class CLASS>
inline constexpr const char* typenameOf() {
	static_assert(0);
	return nullptr;
}


class exception {
protected:
	const char* msg; // static msg
	constexpr exception() : msg(nullptr) {

	}
	exception(const char* msg) : msg(msg) {

	}
public:
	const char* what() const {
		return msg;
	}
	

};


template<class CLASS> inline constexpr bool is_exception() {
	return false;
}
template<> inline constexpr bool is_exception <sys::exception>() {
	return true;
}

#define __SYS_ENABLE_TYPENAME__(classType)                   \
template<>                                                   \
inline constexpr const char* ::sys::typenameOf<classType>() {       \
    return #classType;                                       \
}


#define __SYS_ENABLE_IS_EXCEPTION__(classType)\
template<> inline constexpr bool is_exception <classType>() {\
	return true;\
}\


#define __DEF_SYSTEM_EXCEPTION_TYPE__(TYPENAME, DEFAULT_MESSAGE) \
class TYPENAME : public exception                                \
{                                                                \
public:                                                          \
    TYPENAME() : sys::exception(DEFAULT_MESSAGE) {}              \
    TYPENAME(const char* msg) : sys::exception(msg) {}           \
};                                                               \
__SYS_ENABLE_TYPENAME__(TYPENAME)\
__SYS_ENABLE_IS_EXCEPTION__(TYPENAME)


// OVERLOAD FOR ADDITIONAL BODY
#define __DEF_SYSTEM_EXCEPTION_TYPE_2__(TYPENAME, DEFAULT_MESSAGE, BODY)\
class TYPENAME : public exception                                \
{                                                                \
public:                                                          \
    TYPENAME() : sys::exception(DEFAULT_MESSAGE) {}              \
    TYPENAME(const char* msg) : sys::exception(msg) {}           \
BODY\
};                                                               \
__SYS_ENABLE_TYPENAME__(TYPENAME)\
__SYS_ENABLE_IS_EXCEPTION__(TYPENAME)

__DEF_SYSTEM_EXCEPTION_TYPE__(bad_dealloc, "Bad deallocation");
__DEF_SYSTEM_EXCEPTION_TYPE__(bad_alloc, "Bad allocation");
__DEF_SYSTEM_EXCEPTION_TYPE__(logic_error, "Logic error");
__DEF_SYSTEM_EXCEPTION_TYPE__(runtime_error, "Program state is invalid");
__DEF_SYSTEM_EXCEPTION_TYPE__(invalid_operation_error, "Invalid operation");
__DEF_SYSTEM_EXCEPTION_TYPE__(not_implemented_error, "Operation is not implemented.");
__DEF_SYSTEM_EXCEPTION_TYPE__(out_of_memory_error, "Out of memory.");
__DEF_SYSTEM_EXCEPTION_TYPE__(null_reference_error, "Object reference not set to an instance of an object");
__DEF_SYSTEM_EXCEPTION_TYPE__(invalid_format_error, "Invalid input format.");
__DEF_SYSTEM_EXCEPTION_TYPE__(pure_virtual_error, "Invalid function usage is not allowed.");
__DEF_SYSTEM_EXCEPTION_TYPE__(invalid_cast_error, "Underlying type was not the expected");
__DEF_SYSTEM_EXCEPTION_TYPE__(invalid_argument_error, "Argument is invalid");



_SYS_ENS