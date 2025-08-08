#pragma once
#include <types.h>
typedef int ref;
typedef unsigned int uref;
typedef char sbyte;
typedef unsigned short ushort;
typedef unsigned char byte;
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef float single;
typedef double decimal;
typedef uint32_t uint32;
typedef uint64_t uint64;
typedef byte* byte_ptr;
typedef uint32_t* uint_ptr;
typedef uint _DWORD;
typedef bool BOOL;
typedef unsigned long long _QWORD;
typedef short _WORD;
typedef byte _BYTE;
typedef uint address;
typedef uint64_t any;
typedef int i32;
typedef int64_t i64;
typedef uint u32;
typedef uint64_t u64;
typedef int32_t Int32;
typedef int64_t Int64;
typedef uint64_t Uint64;
typedef uint32_t Uint32;
typedef wchar_t wchar;

#ifndef PSUTIL_EMPTY_STRING
#define PSUTIL_EMPTY_STRING
static const char* EMPTY_STRING = "";
static const wchar_t* EMPTY_WSTRING = L"";
#endif

extern const char* EMPTY_STRING;
extern const wchar_t* EMPTY_WSTRING;
#define MAX(a, b)			((a) >= (b) ? (a) : (b))
#define MIN(a, b)			((a) <= (b) ? (a) : (b))
#define ABS(a)				(((a) < 0) ? -(a) : (a))
// aldo had the same idea 
#define RANGE(a, b, c)		((a) <= (b) ? (b) : (a) >= (c) ? (c) : (a))
#define BETWEEN(a, b, c)	( ((a) <= (b)) && ((b) <= (c)) )
#define ISDIGIT(a)			( ('0' <= (a)) && ((a) <= '9') )
#define ISSPACE(a)			( ( 0  <= (a)) && ((a) <= ' ') )
#define ISHEX(a)			(ISDIGIT(a) || BETWEEN('a', LCASE(a), 'f'))
#define	INT32(a)			(*((u32*)(a)))
#define LCASE(a)	(a | 0x20)
#define NORMALIZED(x, min, max)(x - min) / (max - min)
#define NORMALIZED2(x) (((x)<0.0) ? 0.0:1.0 )
#define NORMALIZE32(x) (((x)<-1.0) ? -1.0: (((x) > 1.0)?1.0:x) )
#define ast(type,x)\ ((type)(x))
#define NAMEOF(var) #var
#define AS(addr, type) (type)addr;
#define OVERRIDE_INMEDIATE(liAddr, newValue) (((short*)liAddr)[1] = newValue);