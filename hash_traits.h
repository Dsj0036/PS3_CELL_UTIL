#ifndef SYS_HASH_TRAITS
#define SYS_HASH_TRAITS
#define SYS_HASH_TRAITS_BEGIN _SYS_NS namespace hash_traits {
#define SYS_HASH_TRAITS_END } _SYS_ENS

#include "_ns.h"
#include "exception.h"
#include "throw.h"
#include "lwstring.h"
#include "array_param.h"
#include "allocator.h"

 
SYS_HASH_TRAITS_BEGIN


template<typename T, typename TF = typename sys::_Select<sys::is_fundamental<T>::value, T, const T&>::type>
size_t get_hash(TF x);// { FAIL sys::invalid_operation_error("Invalid function usage is not allowed."); }

template<> size_t get_hash<short>(short);
template<> size_t get_hash<int>(int);
template<> size_t get_hash<unsigned int>(unsigned int);
template<> size_t get_hash<wchar_t>(wchar_t);
template<> size_t get_hash<char>(char);
template<> size_t get_hash<unsigned char>(unsigned char);
template<> size_t get_hash<float>(float);
template<> size_t get_hash<double>(double);
template<> size_t get_hash<long>(long);
template<> size_t get_hash<uint64_t>(uint64_t);
template<> size_t get_hash<const char*>(const char*);
template<> size_t get_hash<const wchar_t*>(const char*);
template<> size_t get_hash<array_param<unsigned char>>(array_param<unsigned char>);

template<> size_t get_hash<lwstring>(const lwstring&);
template<> size_t get_hash<lwwstring>(const lwwstring&);

template<> size_t get_hash<sys::exception>(const sys::exception&);
template<> size_t get_hash<sys::alloc>(const sys::alloc&);

template<> size_t get_hash<string_view>(const string_view&);
template<> size_t get_hash<wstring_view>(const wstring_view&);




SYS_HASH_TRAITS_END
#endif
