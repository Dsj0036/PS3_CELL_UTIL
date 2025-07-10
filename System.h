// PS3 Cell Utilities by Josh
// cool in a way
// Should include for entire project.
#pragma once


#ifndef __PS3_SYSTEM_UTILITIES__
#define __PS3_SYSTEM_UTILITIES__

#pragma region INCLUDES
#include <ppu_intrinsics.h>
#include <sys/timer.h>
#include <sys/prx.h>
#include <sys/prx.h>
#include <sys/types.h>
#include <cellstatus.h>
#include <spu_printf.h>
#include <netdb.h>

// SYS
#include <sys/socket.h>
#include <sys/process.h>
#include <sys/syscall.h>
#include <sys/ppu_thread.h>
#include <sys/sys_time.h>
#include <sys/time_util.h>
#include <sys/process.h>
#include <sys/memory.h>
#include <sys/timer.h>
#include <sys/random_number.h>
// CELL
#include <cellstatus.h>
#include <cell/sysmodule.h>
#include "cell/pad.h"
#include "cell/http/client.h"
#include "cell/http/error.h"
#include "cell/http/net_error.h"
#include "cell/http/util.h"
#include "cell/dbgrsx.h"
#include "Types.h"
#include "cell/cell_fs.h"
#include <cell/http.h>
#include <../PS3_CELL_UTIL/Interop.h>
#include "sys\tty.h"
#include <stdarg.h>
#include <xstring>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <ctype.h>
#include <math.h>
#include <sys\console.h>
#include <fastmath.h>

// http
#include <netex/net.h>
#include <netinet/in.h>
// OVERRIDE ALLOCATION OPERATORS
//#include <new> // for nothrow_t
#include "wchar.h"
#include "C:\usr\local\cell\target\ppu\include\math.h"

#ifndef does
#define does(x) { x; }
#endif
#define THIS ((unsigned int)this)

#pragma region DEFINITIONS
#if false
#ifndef strlen
#define strlen _sys_strlen
#endif

#ifndef memset
#define memset _sys_memset
#endif

#ifndef memcpy
#define memcpy _sys_memcpy
#endif


#ifndef strncpy
#define strncpy _sys_strncpy
#endif
#endif
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

static int32_t HOOK_COUNT = 0;

#define USE_PATCHES_ACCESSOR false
#if USE_PATCHES_ACCESSOR
#define PATCHES_SPACE_NAME Hooks
#define PATCHES_END };
#define PATCHES_BEGIN namespace PATCHES_SPACE_NAME {\

#define PATCHES_ACCESSOR PATCHES_SPACE_NAME::
#define PATCHES_DEPENDANT using namespace PATCHES_SPACE_NAME;
#else
#define PATCHES_SPACE_NAME
#define PATCHES_END
#define PATCHES_BEGIN

#define PATCHES_ACCESSOR
#define PATCHES_DEPENDANT
#endif



#ifndef RAND_MAX
#define RAND_MAX	0x3fffffff
#endif

#define MAX(a, b)			((a) >= (b) ? (a) : (b))

#define MIN(a, b)			((a) <= (b) ? (a) : (b))

#define ABS(a)				(((a) < 0) ? -(a) : (a))

#define Import using namespace


#define thread_create sys_ppu_thread_create

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

#undef assert
#define assert(condition) _internal_assert(condition, __LINE__, __FILE__, #condition)


#define RAND_BY_TIME(uint_time) _sys_bitwise_mix(uint_time);

#define __UNKNOWN_DATA private:

#define TRUNC_DECIMALS(x) (floorf(x * 100) / 100.0)

#define HIWORD(l) ((unsigned short)(((unsigned long)(l) >> 16) & 0xFFFF))

#define LOWORD(l) ((unsigned short)((unsigned long)(l) & 0xFFFF))

#define MAKELONG(low, high) ((unsigned long)(((unsigned short)(low)) | (((unsigned long)((unsigned short)(high))) << 16)))


#define RETNAMEOFINCASE(x) case x: return #x; break
#define breakreturn(x) return x; break
#define __reserved_stub() __nop();__nop();__nop();__nop();__nop()


#define IMPORT_CALL_TO_INSTANCE(address, name, ret) \
    ret name() { \
        return CallToInstance<ret>(address, this); \
    }

#ifndef IMPORT_CALL
#define IMPORT_CALL(addr, return_type, func_name, args) \
	private:  \
		static int32_t func_name##_opd[2] = { addr, 0x014CDAB0 }; \
		using func_name##_t = return_type(*)args; \
	public: \
	const __ImportedCalls::func_name##_t func_name = reinterpret_cast<__ImportedCalls::func_name##_t>(__ImportedCalls::func_name##_opd);
#endif


#define or ||


#define does(x) { x; }

/// @brief Defines a dummy function stub with a given return type and name.
/// @details This stub contains 5 NOP instructions, acting as placeholder code
///          which can later be patched or replaced at runtime.
/// 
/// @param ret_type The return type of the function.
/// @param func_name The name of the function to generate.
/// @param ... The parameter list for the function (use like a regular prototype).
///
/// @example
///     CREATE_DUMMY_STUB(void, DummyFunc, int a, float b);
///     // Generates:
///     // void DummyFunc(int a, float b) { __nop(); __nop(); ... }
#define CREATE_DUMMY_STUB(ret_type, func_name, ...) \
    ret_type func_name(__VA_ARGS__) { \
        __nop(); \
        __nop(); \
        __nop(); \
        __nop(); \
        __nop(); \
    }



/// @brief Defines a static dummy function stub.
/// @details Identical to CREATE_DUMMY_STUB, but the function is declared as static,
///          meaning its scope is limited to the current translation unit (file).
///
/// @param ret_type The return type of the function.
/// @param func_name The static function name to define.
/// @param ... The parameter list for the function.
///
/// @example
///     CREATE_DUMMY_STATIC_STUB(int, StaticStub, const char* msg);
///     // Generates:
///     // static int StaticStub(const char* msg) { __nop(); __nop(); ... }
#define CREATE_DUMMY_STATIC_STUB(ret_type, func_name, ...) \
    static ret_type func_name(__VA_ARGS__) { \
        __nop(); \
        __nop(); \
        __nop(); \
        __nop(); \
        __nop(); \
    }


/// @brief Shorthand macro for creating a static dummy stub with a fixed return type.
/// @details This macro simplifies the creation of a static stub intended to act as a
///          restoration trampoline, typically used in runtime patching or code restoration.
///          The stub uses int as return type and accepts variadic arguments.
/// 
/// @param NAME The function name of the trampoline.
///
/// @example
///     RESTORATION_TRAMPOLINE(MyPatchRestore);
///     // Expands to:
///     // static int MyPatchRestore(...) { __nop(); __nop(); ... }
#define RESTORATION_TRAMPOLINE(NAME) CREATE_DUMMY_STATIC_STUB(int, NAME, ...)


#define CASE_RETURN(x, v) case x: return v; break

#define sub(addr, ...) Call<uint64_t>(addr, __VA_ARGS__)

typedef int ref;
typedef unsigned int uref;
typedef sys_ppu_thread_t thread;
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

struct OPDEntry {
	void* func;
	void* toc;
};

struct uint128 {
public:
	uint64_t low;
	uint64_t high;

	uint128() : low(0), high(0) {}
	uint128(const uint128& x) {
		low = x.low;
		high = x.high;
	}
	uint128(uint64_t l) : low(l), high(0) {}
	uint128(uint64_t h, uint64_t l) : low(l), high(h) {}
	uint128& operator++() {
		if (++low == 0) {
			++high;
		}
		return *this;
	}
	uint128 operator++(int) {
		uint128 temp = *this;
		++(*this);
		return temp;
	}
	uint128& operator--() {
		if (low-- == 0) {
			--high;
		}
		return *this;
	}
	uint128 operator--(int) {
		uint128 temp = *this;
		--(*this);
		return temp;
	}
	uint128 operator<<(uint32_t shift) const {
		if (shift >= 128) return uint128(0, 0);
		if (shift >= 64) return uint128(low << (shift - 64), 0);
		return uint128((high << shift) | (low >> (64 - shift)), low << shift);
	}
	uint128 operator>>(uint32_t shift) const {
		if (shift >= 128) return uint128(0, 0);
		if (shift >= 64) return uint128(0, high >> (shift - 64));
		return uint128(high >> shift, (low >> shift) | (high << (64 - shift)));
	}
	uint128 operator+(const uint128& other) const {
		uint64_t new_low = low + other.low;
		uint64_t carry = new_low < low ? 1 : 0;
		return uint128(high + other.high + carry, new_low);
	}
	uint128 operator-(const uint128& other) const {
		uint64_t borrow = low < other.low ? 1 : 0;
		return uint128(high - other.high - borrow, low - other.low);
	}
	uint128 operator*(const uint128& other) const {
		uint64_t a = low, b = high, c = other.low, d = other.high;
		uint64_t ac = a * c;
		uint64_t ad = a * d;
		uint64_t bc = b * c;
		uint64_t bd = b * d;
		return uint128(bd + (ad >> 32) + (bc >> 32), ac);
	}
	uint128 operator/(uint64_t divisor) const {
		uint128 result;
		uint128 remainder;
		for (int i = 127; i >= 0; --i) {
			remainder = (remainder << 1) + ((high >> i) & 1);
			if (remainder.low >= divisor) {
				remainder.low -= divisor;
				result.low |= (1ULL << i);
			}
		}
		return result;
	}
	uint128& operator+=(const uint128& other) {
		*this = *this + other;
		return *this;
	}

	uint128& operator-=(const uint128& other) {
		*this = *this - other;
		return *this;
	}
	uint128 operator%(uint64_t divisor) const {
		uint128 remainder;
		for (int i = 127; i >= 0; --i) {
			remainder = (remainder << 1) + ((high >> i) & 1);
			if (remainder.low >= divisor) {
				remainder.low -= divisor;
			}
		}
		return remainder;
	}
};

enum THREAD_PRIORITY
{
	LOWEST = 3000,
	BELOW_NORMAL = 2400,
	LOW = 2000,
	NORMAL = 1500,
	ABOVE_NORMAL = 1000,
	REAL_TIME = 500,
	ALL = 0, // WARNING VSH

};




struct local_time_t {
	short year; byte month, day, hour, minute, second;
	bool isPM;
};
void addMilliseconds(local_time_t& time, int ms) {
	static const int MS_IN_A_SECOND = 1000;
	static const int SECONDS_IN_A_MINUTE = 60;
	static const int MINUTES_IN_AN_HOUR = 60;
	static const int HOURS_IN_HALF_DAY = 12;

	int extraSeconds = ms / MS_IN_A_SECOND;
	time.second += extraSeconds;

	// Normalización del tiempo
	while (time.second >= SECONDS_IN_A_MINUTE) {
		time.second -= SECONDS_IN_A_MINUTE;
		time.minute++;
	}

	while (time.minute >= MINUTES_IN_AN_HOUR) {
		time.minute -= MINUTES_IN_AN_HOUR;
		time.hour++;
	}

	while (time.hour > HOURS_IN_HALF_DAY) {
		time.hour -= HOURS_IN_HALF_DAY;
		time.isPM = !time.isPM;
		if (!time.isPM) {
			time.day++;
		}
	}
}

struct utc_t {
	uint16_t year;
	byte month, day, hour, minute, second;
	uint16_t millisecond;
	utc_t() : year(0), month(0), day(0), hour(0), minute(0), second(0), millisecond(0) {}
	utc_t(int y, int mo, int d, int h, int mi, int s, int ms)
		: year(y), month(mo), day(d), hour(h), minute(mi), second(s), millisecond(ms) {
	}
	bool operator==(const utc_t& other) const {
		return year == other.year && month == other.month && day == other.day &&
			hour == other.hour && minute == other.minute && second == other.second &&
			millisecond == other.millisecond;
	}
	bool operator!=(const utc_t& other) const { return !(*this == other); }
	bool operator<(const utc_t& other) const {
		if (year != other.year) return year < other.year;
		if (month != other.month) return month < other.month;
		if (day != other.day) return day < other.day;
		if (hour != other.hour) return hour < other.hour;
		if (minute != other.minute) return minute < other.minute;
		if (second != other.second) return second < other.second;
		return millisecond < other.millisecond;
	}
	bool operator>(const utc_t& other) const { return other < *this; }
	bool operator<=(const utc_t& other) const { return !(*this > other); }
	bool operator>=(const utc_t& other) const { return !(*this < other); }
	utc_t operator+(int ms) const {
		utc_t result = *this;
		result.millisecond += ms;
		while (result.millisecond >= 1000) { result.millisecond -= 1000; result.second++; }
		while (result.second >= 60) { result.second -= 60; result.minute++; }
		while (result.minute >= 60) { result.minute -= 60; result.hour++; }
		while (result.hour >= 24) { result.hour -= 24; result.day++; }

		return result;
	}
	utc_t operator-(int ms) const {
		utc_t result = *this;
		result.millisecond -= ms;

		while (result.millisecond < 0) { result.millisecond += 1000; result.second--; }
		while (result.second < 0) { result.second += 60; result.minute--; }
		while (result.minute < 0) { result.minute += 60; result.hour--; }
		while (result.hour < 0) { result.hour += 24; result.day--; }

		return result;
	}
	utc_t& operator=(const utc_t& t) {
		this->day = t.day;
		this->month = t.month;
		this->year = t.year;
		this->hour = t.hour;
		this->minute = t.minute;
		this->second = t.second;
		this->millisecond = t.millisecond;
		return *this;
	}

	void addMilliseconds(long ms) {
		this->millisecond += ms;
		while (this->millisecond >= 1000) {
			this->millisecond -= 1000;
			this->second++;
		}

		while (this->second >= 60) {
			this->second -= 60;
			this->minute++;
		}

		while (this->minute >= 60) {
			this->minute -= 60;
			this->hour++;
		}

		while (this->hour >= 24) {
			this->hour -= 24;
			this->day++;
		}
	}
};

inline int ctoi(char c) {
	return c - '0';
}

bool parse_local_time(const char* timeStr, local_time_t& outTime) {
	if (!timeStr) return false;
	if (timeStr[2] != '/' || timeStr[5] != '/' || timeStr[10] != ',' ||
		timeStr[13] != ':' || timeStr[16] != ':' || (timeStr[19] != 'A' && timeStr[19] != 'P') || timeStr[20] != 'M') {
		return false;
	}
	outTime.month = ctoi(timeStr[0]) * 10 + ctoi(timeStr[1]);
	outTime.day = ctoi(timeStr[3]) * 10 + ctoi(timeStr[4]);
	outTime.year = ctoi(timeStr[6]) * 1000 + ctoi(timeStr[7]) * 100 +
		ctoi(timeStr[8]) * 10 + ctoi(timeStr[9]);
	outTime.hour = ctoi(timeStr[12]) * 10 + ctoi(timeStr[13]);
	outTime.minute = ctoi(timeStr[15]) * 10 + ctoi(timeStr[16]);
	outTime.second = ctoi(timeStr[18]) * 10 + ctoi(timeStr[19]);
	outTime.isPM = (timeStr[19] == 'P');
	return true;
}
bool parse_utc_time(const char* utcStr, utc_t& outTime) {
	if (!utcStr) return false;

	if (utcStr[4] != '-' || utcStr[7] != '-' || utcStr[10] != 'T' ||
		utcStr[13] != ':' || utcStr[16] != ':' || utcStr[19] != '.' || utcStr[23] != 'Z') {
		return false;
	}
	outTime.year = ctoi(utcStr[0]) * 1000 + ctoi(utcStr[1]) * 100 +
		ctoi(utcStr[2]) * 10 + ctoi(utcStr[3]);

	outTime.month = ctoi(utcStr[5]) * 10 + ctoi(utcStr[6]);
	outTime.day = ctoi(utcStr[8]) * 10 + ctoi(utcStr[9]);

	outTime.hour = ctoi(utcStr[11]) * 10 + ctoi(utcStr[12]);
	outTime.minute = ctoi(utcStr[14]) * 10 + ctoi(utcStr[15]);
	outTime.second = ctoi(utcStr[17]) * 10 + ctoi(utcStr[18]);

	outTime.millisecond = ctoi(utcStr[20]) * 100 + ctoi(utcStr[21]) * 10 + ctoi(utcStr[22]);

	return true;
}
namespace sys {
	template<typename T>
	struct iter {
		T* _ptr;
		size_t _size = 0;

		template<size_t N>
		iter(T(&array)[N]) : _ptr(array), _size(N) {}

		iter(T* ptr, size_t num) : _ptr(ptr), _size(num) {}

		T* begin() { return _ptr; }
		const T* begin() const { return _ptr; }
		T* end() { return _ptr + _size; }
		const T* end() const { return _ptr + _size; }

		size_t size() const { return _size; }
		T& operator[](size_t i) { return _ptr[i]; }
		const T& operator[](size_t i) const { return _ptr[i]; }
	};
	void* memalign(size_t boundary, size_t size) {
		return _sys_memalign(boundary, size);
	}
	void* memmove(void* dest, const void* src, size_t n) {
		unsigned char* d = static_cast<unsigned char*>(dest);
		const unsigned char* s = static_cast<const unsigned char*>(src);

		if (d == s || n == 0) {
			return dest;
		}

		if (d < s || d >= s + n) {
			while (n--) {
				*d++ = *s++;
			}
		}
		else {
			d += n;
			s += n;
			while (n--) {
				*(--d) = *(--s);
			}
		}

		return dest;
	}

	uint strlen(const char* x) does(return _sys_strlen(x));
	uint strlen(void* x) does(return _sys_strlen((char*)x));
	typedef int int32_t;
	typedef uint32_t size_t;
	typedef uint uint32_t;
	typedef unsigned long long uint64_t;

	template <typename x>	x abs(x a) does(ABS(a));
	template <typename x>	x min(x a, x b) does(MIN(a, b));
	template <typename x>	x max(x a, x b) does(MAX(a, b));
	int memcmp(const void* a, const void* b, size_t num) does(return _sys_memcmp(a, b, num));
	void* memcpy(const void* srcDest, const void* srcSrc, size_t num) does(return _sys_memcpy((void*)srcDest, (void*)srcSrc, num));
	void* memset(void* srcDest, int value, size_t len) does(return _sys_memset(srcDest, value, len));
	char* strncpy(char* srcDest, const char* srcSrc, size_t srcSize) does(return _sys_strncpy(srcDest, srcSrc, srcSize));
	char* strcpy(char* srcDest, const char* srcSrc) does(return _sys_strcpy(srcDest, srcSrc));


	int strncmp(const char* srcDest, const char* srcSrc, size_t srcSize) does(return _sys_strncmp(srcDest, srcSrc, srcSize));

	int _strcmp(const char* s1, const char* s2) {
		while (*s1 && (*s1 == *s2)) {
			++s1;
			++s2;
		}
		return *(unsigned char*)s1 - *(unsigned char*)s2;
	}

	const char* strstr_array(const char* const strings[], const char* target, int count, bool matchCase) {
		if (!strings || !target || count <= 0)
			return nullptr;
		int targetLen = sys::strlen(target);
		for (int i = 0; i < count; ++i) {
			if (!strings[i]) continue;
			bool matched = matchCase
				? sys::strncmp(strings[i], target, targetLen) == 0
				: std::strncasecmp(strings[i], target, targetLen) == 0;
			if (matched)
				return strings[i];
		}
		return nullptr;
	}

	int wcsncmp(const wchar_t* a, const wchar_t* b, size_t size) {
		if (size <= 0) {
			return EINVAL;
		}
		size_t iter = 0;
		while (iter < size) {
			if (_sys_memcmp(a, b, 2) != 0) {
				return false;
			}
			iter++;
		}
		return iter == size;
	}
	size_t wcslen(const wchar_t* widestring) {
		if (!widestring) {
			return 0;
		}
		size_t x = 0;
		while (widestring[x] != L'\0') {
			x++;
		}
		return x;
	}

	void* malloc(size_t size) does(return _sys_malloc(size));
	void free(void* alloc) does(_sys_free(alloc));


	template <typename ...args> int printf(const char* format, args...x) does(_sys_printf(format, x...));
	template <typename ...args> int printf(const std::string& format, args...x) does(_sys_printf(format.c_str(), x...));

	template <typename ...args> int snprintf(char* buff, size_t num, const char* frm, args...x) does(_sys_snprintf(buff, num, frm, x...));
	void strncat(char* dest, char* src, size_t num) {
		_sys_strncat(dest, src, num);
	}
	void* strchr(char* src, int ch)  does(return _sys_strrchr(src, ch));
	int tolower(int c) does(return _sys_tolower(c));
	int toupper(int c) does(return _sys_toupper(c));
	template <typename ...args> int sprintf(char* buf, char* format, args...x) does(_sys_sprintf(buf, format, x...));
	double stod(const char* str) {
		double result = 0.0f;
		// double factor = 1.0f;
		bool negative = false;
		bool decimalPointEncountered = false;
		float decimalFactor = 0.1f;

		// !! Ensure skipping leading spaces otherwises it will always return 0.0
		while (*str == ' ') {
			str++;
		}
		if (*str == '-') {
			negative = true;
			str++;
		}
		while (*str != '\0') {
			if (*str == '.') {
				decimalPointEncountered = true;
			}
			else if (*str >= '0' && *str <= '9') {
				if (decimalPointEncountered) {
					result += (*str - '0') * decimalFactor;
					decimalFactor *= 0.1f;
				}
				else {
					result = result * 10.0f + (*str - '0');
				}
			}
			else {
				break;
			}
			str++;
		}
		if (negative) {
			result = -result;
		}

		return result;
	}
	/// <summary>
	/// Parse Dot Floating Value String
	/// </summary>
	/// <param name="str"></param>
	/// <returns></returns>
	float stof(const char* str) {
		float result = 0.0f;
		//float factor = 1.0f;
		bool negative = false;
		bool decimalPointEncountered = false;
		float decimalFactor = 0.1f;
		// !! Ensure skipping leading spaces otherwises it will always return 0.0
		while (*str == ' ') {
			str++;
		}
		if (*str == '-') {
			negative = true;
			str++;
		}
		while (*str != '\0') {
			if (*str == '.') {
				decimalPointEncountered = true;
			}
			else if (*str >= '0' && *str <= '9') {
				if (decimalPointEncountered) {
					result += (*str - '0') * decimalFactor;
					decimalFactor *= 0.1f;
				}
				else {
					result = result * 10.0f + (*str - '0');
				}
			}
			else {
				break;
			}
			str++;
		}
		if (negative) {
			result = -result;
		}

		return result;
	}

	template <typename... Arguments>
	size_t strnprintfcat(char* buffer, const char* format, size_t len, Arguments... s) {
		char temp[0x256]{ 0 };

		sys::snprintf(temp, sizeof(temp) - 1, format, s...);

		size_t currentLen = sys::strlen(buffer);
		sys::_sys_strncat(buffer, temp, len - currentLen - 1);

		return sys::strlen(buffer);
	}
	template <typename T>
	T&& move(T& arg) {
		return static_cast<T&&>(arg);
	}
	static std::string trim(const std::string& s) {
		const char* ws = " \t\r\n";
		size_t start = s.find_first_not_of(ws);
		size_t end = s.find_last_not_of(ws);
		return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
	}


}

// Format the UTC structure into an SQL TIMESTAMP WITH TIME ZONE format
void utcToSqlTimestamptz(const utc_t& utc, char* output) {
	// Example format: "2025-02-13 14:30:45.123+00"
	sys::snprintf(output, 50, "%04d-%02d-%02d %02d:%02d:%02d.%03d+00",
		utc.year, utc.month, utc.day,
		utc.hour, utc.minute, utc.second, utc.millisecond);
}

signed int s_addr_dist_from(void* class_, void* object) {
	return static_cast<signed int>(((uint32_t)object) - ((uint32_t)class_));
}


uintptr_t s_funcopdoff(uint32_t classed_ptr, uint32_t offset) {
	uint32_t table_value = *(uint32_t*)(classed_ptr);
	return *(uint32_t*)(table_value + offset);
}


template <typename T>
class property {
private:
	T value;
	bool isInitialized = false;

public:
	explicit property(const T& initialValue) : value(initialValue), isInitialized(true) {}
	property(T value) {
		this->value = value;
		isInitialized = true;
	}
	property() = default;
	void set(const T& newValue) {
		if (isInitialized) {
			return;
		}
		value = newValue;
		isInitialized = true;
	}

	T get() const {
		if (!isInitialized) {
			return;
		}
		return value;
	}
	operator T() const {
		return get();
	}
	property<T>& operator= (T x) {
		value = x;
	}
};

template <typename T, typename C>
T reinterpret(C v) {
	return reinterpret_cast<T>(v);
}
template <typename From, typename To>
To cast(From v) {
	return static_cast<To>(v);
}

double _dfloor(double x) {
	if (x < 0 && x != static_cast<int>(x)) {
		return static_cast<int>(x) - 1;
	}
	else {
		return static_cast<int>(x);
	}
}

double _dmod(double a, double b) {
	if (b == 0.0) {
		return 0.0;
	}
	double result = a - b * _dfloor(a / b);
	return result;
}

void asm_write_nop_ori(void* a) {
	*(uint32_t*)a = 0x60000000;
}
void asm_write_nop_ori(uint32_t a) {
	*(uint32_t*)a = 0x60000000;
}

template <class T>
uintptr_t this_stor(T* s) {
	return (unsigned int)s;
}
int toInt(float input) {
	bool negative = input < 0.0f;
	if (negative) input *= -1.0f;

	uint32_t output = static_cast<uint32_t>(input);
	if (negative) {
		output -= 0x80000000;
		output = 0x80000000 - output;
		output -= 1;
	}

	return output;
}

float toFloat(int input) {
	bool negative = 0 > input;
	unsigned int output_tmp = negative ? -input : input;
	float output = static_cast<float>(output_tmp);
	return negative ? -output : output;
}
// Convert a 32-bit unsigned integer to a float
float _ufloat(uint32_t value) {
	return *(float*)(byte*)&(value);
}


float _gdecimal(float number) {
	int integerPart = static_cast<int>(number);
	float fractional = number - integerPart;
	float decimal = fractional * 10;
	return decimal;
}
int _timecode_to_frames(int fps, int h, int m, int s) {
	return (h * fps * 3600) + (m * fps * 60) + (s * fps);
}
// Compares if data only atleast haves "data" in it, only compares the len of "comparing" inside "data"
bool _sstartswith(const char* data, const char* comparing) {
	while (*comparing) {
		if (*data++ != *comparing++)
			return false;
	}
	return true;
}

bool _endsWith(const char* data, const char* end) {
	size_t data_len = _sys_strlen(data);
	size_t end_len = _sys_strlen(end);

	if (end_len > data_len) {
		return false;
	}
	return !_sys_strcmp(data + data_len - end_len, end);
}
bool _wsequals(const wchar* data, const wchar* comparing) {
	return std::wcsncmp(comparing, data, std::wcslen(comparing)) == 0;
}
bool _absSmallerThan(int r, int range) {
	return abs((double)r) < range;
}

CellRtcDateTime _epochToDatetime(time_t epoch) {
	const int SECONDS_IN_A_MINUTE = 60;
	//const int SECONDS_IN_AN_HOUR = 3600;
	//const int SECONDS_IN_A_DAY = 86400;

	//const int SECONDS_IN_A_LEAP_YEAR = 31622400;
	//const int SECONDS_IN_A_NON_LEAP_YEAR = 31536000;
	const int DAYS_IN_MONTHS[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	int seconds = epoch % SECONDS_IN_A_MINUTE;
	epoch /= SECONDS_IN_A_MINUTE;
	int minutes = epoch % SECONDS_IN_A_MINUTE;
	epoch /= SECONDS_IN_A_MINUTE;
	int hours = epoch % 24;
	epoch /= 24;
	int year = 1970;
	int daysInYear;
	while (true) {
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
			daysInYear = 366;
		}
		else {
			daysInYear = 365;
		}

		if (epoch >= daysInYear) {
			epoch -= daysInYear;
			++year;
		}
		else {
			break;
		}
	}
	int month = 0;
	bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
	while (true) {
		int daysInMonth = DAYS_IN_MONTHS[month];
		if (isLeapYear && month == 1) {
			++daysInMonth;
		}

		if (epoch >= daysInMonth) {
			epoch -= daysInMonth;
			++month;
		}
		else {
			break;
		}
	}
	int day = epoch + 1;
	CellRtcDateTime date;
	date.day = day;
	date.hour = hours;
	date.minute = minutes;
	date.year = year;
	date.month = month;
	date.second = seconds;
	date.microsecond = day * 24 * 60 * 60 * 1000000;
	return date;
}
static struct platform_info {
	uint firmware_version;
} info;
static inline int lv2_get_platform_info(struct platform_info* info)
{
	system_call_1(387, (uint)info);
	return (uint)p1;
}

static char h2a(const char hex) // hex byte to ascii char
{
	char c = (unsigned char)hex;
	if (BETWEEN(0, c, 9))
		c += '0'; //'0'-'9'
	else if (BETWEEN(0xA, c, 0xF))
		c += 55;  //'A'-'F'
	return c;
}
static uint8_t h2b(const char hex) // hex char to byte
{
	uint8_t c = LCASE(hex);
	if (BETWEEN('0', c, '9'))
		c -= '0'; // 0-9
	else if (BETWEEN('a', c, 'f'))
		c -= 'W'; // 10-15
	return c;
}
static bool islike(const char* param, const char* text)
{
	if (!param || !text) return false;
	while (*text && (*text == *param)) text++, param++;
	return !*text;
}

static uint64 convertH(const char* val) // convert hex string to unsigned integer 64bit
{
	if (!val || (*val == 0)) return 0;

	uint64 ret = 0; uint8_t n = 0, c;

	if (islike(val, "0x")) n = 2;

	for (uint8_t i = n; i < 16 + n; i++)
	{
		if (val[i] == ' ') { n++; continue; }

		c = h2b(val[i]);
		if (c > 0xF)
			return ret;

		ret = (ret << 4) | c;
	}

	return ret;
}

static uint64 val(const char* c)
{
	if (!c) return 0;

	if (islike(c, "0x"))
	{
		return convertH((char*)c);
	}

	uint64 result = 0;
	uint64 sign = 1;

	if (c && *c == '-')
	{
		sign = -1;
		c++;
	}

	while (*c)
	{
		if (!ISDIGIT(*c)) break;

		result *= 10;
		result += (*c & 0x0F);

		c++;
	}
	return(result * sign);
}

static float get_firmware_version(void)
{
	lv2_get_platform_info(&info);
	char FW[8]; sys::sprintf(FW, "%02X", info.firmware_version);
	return (float)(FW[0] & 0x0F) + val(FW + 2) * 0.00001f;
}

int _saddressof(void* foo) {
	return reinterpret_cast<int>(&foo);
}
std::string _uid2str(int userId) {
	char base_[9];
	std::fill(base_, &base_[8], '0');
	base_[9] = 0;
	char prt[32]{ 0 };
	sys::snprintf(prt, 32, "%i", userId);
	int num = sys::strlen(prt);
	sys::memcpy((base_ + 8) - num, prt, num);
	base_[9] = 0;

	return base_;
}
char* _strcat2(char* destination, const char* source) {
	char* result = destination;

	while (*destination != '\0') {
		++destination;
	}

	while (*source != '\0') {
		*destination = *source;
		++destination;
		++source;
	}
	*destination = '\0';

	return result;
}

template <typename ... Arguments>
char* format(const char* format, Arguments... s) {
	short len = _sys_strlen(format);
	short buffSz = len < 8 ? 8 : len < 16 ? 16 : len < 32 ? 32 : len < 64 ? 64 : len < 78 ? 78 : len < 86 ? 86 : len < 120 ? 120 : 128;
	char* buff = (char*)malloc(buffSz);
	s_snprintf(buff, buffSz, format, s...);
	return buff;
}
unsigned char hexCharToNibble(char c) {
	if (c >= '0' && c <= '9') {
		return c - '0';
	}
	else if (c >= 'A' && c <= 'F') {
		return c - 'A' + 10;
	}
	else if (c >= 'a' && c <= 'f') {
		return c - 'a' + 10;
	}
	else {
		return 0; // Invalid hex character
	}
}
unsigned int hexToUInt(const char* hexString) {
	unsigned int result = 0;
	while (*hexString) {
		result = (result << 4) | hexCharToNibble(*hexString);
		hexString++;
	}
	return result;
}
int _satoi(const char* str) {
	int result = 0;
	int sign = 1;
	int i = 0;
	while (str[i] == ' ')
		i++;

	if (str[i] == '-') {
		sign = -1;
		i++;
	}
	else if (str[i] == '+') {
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9') {
		result = result * 10 + (str[i] - '0');
		i++;
	}

	return sign * result;
}
void hexs2rgb(const char* hexString, int& r, int& g, int& b) {
	unsigned int hexValue = hexToUInt(hexString);
	r = (hexValue >> 16) & 0xFF;
	g = (hexValue >> 8) & 0xFF;
	b = hexValue & 0xFF;
}
// Check if a character is a digit (0-9)
int _isnumc(int c) {
	if (c >= '0' && c <= '9')
		return true;
	return false;
}

int length(char* s) {
	int len = 0;
	while (*s != 0) {
		len++;
		++s;
	}
	return len;
}
double _min(double a, double b) { return a > b ? b : b < a ? a : b; }

double _max(double a, double b) { return a > b ? a : b > a ? b : a; }
void* _memclr(void* ptr, size_t sz) {
	return (void*)_sys_memset(ptr, 0, sz);
}

void* zero(const void* ptr, size_t sz) { return (void*)_sys_memset((void*)ptr, 0, sz); }

char* zero(char* ptr) {
	return (char*)_sys_memset(ptr, 0, _sys_strlen(ptr));

}
// Remove the first occurrence of a word from a string
bool _strwrem(char* str, const char* wordToRemove) {
	bool f = false;
	while (*str) {
		const char* wordStart = str;
		const char* wordEnd = wordToRemove;
		while (*wordEnd && *wordStart == *wordEnd) {
			++wordStart;
			++wordEnd;
		}
		if (!*wordEnd) {
			while (*wordStart) {
				*str++ = *wordStart++;
			}
			*str = '\0';
			return true;
		}
		++str;
	}
	return f;
}

bool _sequals2(const char* a, const char* b) {
	while (*a && (*a == *b)) {
		a++;
		b++;
	}
	return *a == *b;

}
bool _scontains(const char* str, const char* word) {
	while (*str != '\0') {
		const char* tempStr = str;
		const char* tempWord = word;

		while (*tempStr != '\0' && *tempWord != '\0' && *tempStr == *tempWord) {
			tempStr++;
			tempWord++;
		}

		if (*tempWord == '\0') {
			return true;
		}
		str++;
	}
	return false;
}
bool _iscalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return true;
	return false;
}
char* _strstr(const char* haystack, const char* needle) {
	while (*haystack != '\0') {
		const char* h = haystack;
		const char* n = needle;

		while (*n != '\0' && *h == *n) {
			h++;
			n++;
		}

		if (*n == '\0') {
			return (char*)haystack;
		}

		haystack++;
	}

	return NULL;
}
// Find the index of the first occurrence of a substring in a string
size_t _sfinds(const char* haystack, const char* target) {
	char* found = _strstr(haystack, target);

	if (found == NULL) {
		return (size_t)-1;
	}

	return found - haystack;
}

// Extract a substring from a string starting at a given index and with a specified length
char* _substrnw(const char* str, int start, int length) {
	if (str == nullptr || start < 0 || length < 0) {
		return nullptr;
	}
	int originalLength = 0;
	const char* temp = str;
	while (*temp != '\0') {
		++originalLength;
		++temp;
	}
	if (start >= originalLength) {
		return nullptr;
	}
	int actualLength = std::min(length, originalLength - start);
	char* substring = new char[actualLength + 1];
	for (int i = 0; i < actualLength; ++i) {
		substring[i] = str[start + i];
	}
	substring[actualLength] = '\0';

	return substring;
}
// Find the index of the first occurrence of a character in a string
int _sfindc(const char* str, char target) {
	if (str == nullptr) {
		return -1;
	}
	const char* tempStr = str;
	int index = 0;
	while (*tempStr != '\0') {
		if (*tempStr == target) {
			return index;
		}

		++tempStr;
		++index;
	}

	return -1;
}
int _strcmp(const char* str1, const char* str2)
{
	int diff = -1;

	if (*(str1) == 0x00 || *(str2) == 0x00) { return -1; }

	for (int i = 0; i < 0x600; i++)
	{
		if (*(str1 + i) == 0x00 || *(str2 + i) == 0x00) { break; }
		if (*(str1 + i) != *(str2 + i)) { diff++; }
	}

	return diff;
}

template<typename R, typename... Arguments>
inline R _cast_call(long long function, Arguments... args)
{
	R(*func)(Arguments...) = reinterpret_cast<R(*)(Arguments...)>(function);
	return func(args...);
}
template<typename R, typename... Arguments> inline R Call(long long function, Arguments... args)
{
	int toc_t[2] = { function,  0x014CDAB0 };
	R(*temp)(Arguments...) = (R(*)(Arguments...)) & toc_t;
	return temp(args...);
}
template<typename R, typename... Arguments> inline R _cast_call(uint toc, long long function, Arguments... args)
{
	int toc_t[2] = { function,  toc };
	R(*temp)(Arguments...) = (R(*)(Arguments...)) & toc_t;
	return temp(args...);
}

template <class Instance>
int CallInt(uintptr_t address, Instance* thisInst) {
	return Call<int>(address, (uint)thisInst);
}
template <typename...arg>
size_t printfw(wchar_t* buff, size_t sz, const wchar_t* format, arg...s) {
	return Call<any>(0x00CB9BD8, buff, sz, format, s...);
}
template <typename R, class Instance, typename ...Args>
R CallToInstance(uintptr_t address, Instance* thisInst, Args...s) {
	return Call<R>(address, (uint)thisInst, s...);
}
int _satoi2(char* str) {
	int res = 0;
	for (int i = 0; (*(str + i)) != '\0'; ++i)
		if ((*(str + i)) != ' ') {
			res = res * 10 + (*(str + i)) - '0';
		}
	return res;
}


void _gtemp(uint32_t id, uint32_t* value) {
	// i dont get why is being casted here. Is not needed in any way.

	system_call_2(383, (uint64_t)(uint32_t)id, (uint64_t)(uint32_t)value);
}
// Low level memory read.
int32_t _kernmread(uint64_t address, void* data, size_t size)
{
	system_call_4(904, (uint64_t)sys_process_getpid(), address, size, (uint64_t)data);
	return_to_user_prog(int32_t);
}
// Low level memory write.
int32_t _kernmwrite(uint64_t address, const void* data, size_t size)
{
	system_call_4(905, (uint64_t)sys_process_getpid(), address, size, (uint64_t)data);
	return_to_user_prog(int32_t);
}
int32_t sys_dbg_write_process_memory_ps3mapi(uint64_t ea, const void* data, size_t size)
{
	system_call_6(8, 0x7777, 0x32, (uint64_t)sys_process_getpid(), (uint64_t)ea, (uint64_t)data, (uint64_t)size);
	return_to_user_prog(int32_t);
}
int32_t sys_dbg_read_process_memory_ps3mapi(uint64_t ea, void* data, size_t size)
{
	system_call_6(8, 0x7777, 0x31, (uint64_t)sys_process_getpid(), (uint64_t)ea, (uint64_t)data, (uint64_t)size);
	return_to_user_prog(int32_t);
}

void _set8(int address, char hex) { *(int*)address = hex; }

// Sleep for a specified number of milliseconds
void sleep(usecond_t time) { sys_timer_usleep(time * usecond_t(1000)); }

int write_process(uint64_t ea, const void* data, size_t size)
{
	system_call_6(8, 0x7777, 0x32, (uint64_t)sys_process_getpid(), (uint64_t)ea, (uint64_t)data, (uint64_t)size);
	return_to_user_prog(int);
}
int read_process(uint64_t ea, const void* data, size_t size)
{
	system_call_6(8, 0x7777, 0x31, (uint64_t)sys_process_getpid(), (uint64_t)ea, (uint64_t)data, (uint64_t)size);
	return_to_user_prog(int);
}
int sys_dbg_memcpy(void* destination, const void* source, size_t size)
{
	system_call_4(905, (uint64_t)sys_process_getpid(), (uint64_t)destination, size, (uint64_t)source);
	__dcbst(destination);
	__sync();
	__isync();
	return_to_user_prog(int);
}
void PatchInJump(int Address, int Destination) {
	int FuncBytes[4];
	Destination = *(int*)Destination;
	FuncBytes[0] = 0x3D600000 + ((Destination >> 16) & 0xFFFF);
	if (Destination & 0x8000) FuncBytes[0] += 1;
	FuncBytes[1] = 0x396B0000 + (Destination & 0xFFFF);
	FuncBytes[2] = 0x7D6903A6;
	FuncBytes[3] = 0x4E800420;
	for (int i = 0; i < 4; i++) {
		*(int*)(Address + (i * 4)) = FuncBytes[i];

	}
}
void UnHookFunctionStart(uint32_t functionStartAddress, uint32_t functionStub) {
	uint32_t normalFunctionStub[4];
	_kernmread(functionStub, normalFunctionStub, 0x10);
	_kernmwrite(functionStartAddress, normalFunctionStub, 0x10);

	sys_dbg_read_process_memory_ps3mapi(functionStub, normalFunctionStub, 0x10);
	sys_dbg_write_process_memory_ps3mapi(functionStartAddress, normalFunctionStub, 0x10);
}
int saveValue[2] = { 0x01DA0000, 0x33A00000 };
int highestVal[2] = { 0x01DF0000, 0x36000000 };
int getHighestValue(int index, int checkAddr)
{
	if (checkAddr > saveValue[index] && checkAddr < highestVal[index])
	{
		char getVal[1];
		int val = sys_dbg_read_process_memory_ps3mapi(checkAddr, getVal, 1);
		if (val != -2147418099)
		{
			saveValue[index] = checkAddr + 1;
			return checkAddr;
		}
		else
			return 0x000101C0;
	}
	else
	{
		//_sys_printf("saved %i at %i\n", saveValue[index], index);
		return saveValue[index];
	}
}
void reverse(char s[])
{
	int i, j;
	char c;

	for (i = 0, j = sys::strlen(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}
bool isAlphanumeric(char ch) {
	bool flag = ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9'));
	bool flag2 = ch != '-' && ch != '_';
	return flag && (!flag2);
}
bool endsWith(const char* str, const char* suffix) {
	int suffixLength = 0;
	while (suffix[suffixLength] != '\0') {
		++suffixLength;
	}
	const char* tempStr = str;
	while (*tempStr != '\0') {
		++tempStr;
	}
	int strLength = tempStr - str;
	if (suffixLength > strLength) {
		return false;
	}
	int suffixIndex = 0;
	for (int i = strLength - suffixLength; i < strLength; ++i) {
		if (str[i] != suffix[suffixIndex]) {
			return false;
		}
		++suffixIndex;
	}
	return true;
}
void restartMachine() {
	system_call_3(379, 0x8201, NULL, 0);
}
bool containsAlphanumeric(const char* str) {
	while (*str) {
		if (isAlphanumeric(*str) != 0) {
			return true;
		}
		++str;
	}
	return false;
}
long yearToMilliseconds(int year) {
	return (year - 1970) * 365 * 24 * 60 * 60 * 1000;
}
long monthToMilliseconds(int month) {
	return (month - 1) * 30 * 24 * 60 * 60 * 1000;
}
long datetimeToTimestamp(int year, int month, int day, int hour, int minute, int second) {
	long milliseconds = 0;
	milliseconds += yearToMilliseconds(year);
	milliseconds += monthToMilliseconds(month);
	milliseconds += (day - 1) * 24 * 60 * 60 * 1000;
	milliseconds += hour * 60 * 60 * 1000;
	milliseconds += minute * 60 * 1000;
	milliseconds += second * 1000;

	return milliseconds;
}
// Convert a wide character to UTF-8 encoding
static void _swc2utf8(wchar_t wchar, char* utf8Buffer, size_t bufferSize, size_t& written) {
	if (wchar <= 0x7F) { // 1 byte
		if (written + 1 <= bufferSize) {
			utf8Buffer[written++] = static_cast<char>(wchar);
		}
	}
	else if (wchar <= 0x7FF) { // 2 bytes
		if (written + 2 <= bufferSize) {
			utf8Buffer[written++] = static_cast<char>(0xC0 | (wchar >> 6));
			utf8Buffer[written++] = static_cast<char>(0x80 | (wchar & 0x3F));
		}
	}
	else if (wchar <= 0xFFFF) { // 3 bytes (evitando 0xD800-0xDFFF)
		if ((wchar < 0xD800 || wchar > 0xDFFF) && written + 3 <= bufferSize) {
			utf8Buffer[written++] = static_cast<char>(0xE0 | (wchar >> 12));
			utf8Buffer[written++] = static_cast<char>(0x80 | ((wchar >> 6) & 0x3F));
			utf8Buffer[written++] = static_cast<char>(0x80 | (wchar & 0x3F));
		}
	}
	else if (wchar <= 0x10FFFF) { // 4 bytes
		if (written + 4 <= bufferSize) {
			utf8Buffer[written++] = static_cast<char>(0xF0 | (wchar >> 18));
			utf8Buffer[written++] = static_cast<char>(0x80 | ((wchar >> 12) & 0x3F));
			utf8Buffer[written++] = static_cast<char>(0x80 | ((wchar >> 6) & 0x3F));
			utf8Buffer[written++] = static_cast<char>(0x80 | (wchar & 0x3F));
		}
	}
}

// Convert a wide character string to UTF-8 encoding
static void _sws2utf8s(const wchar_t* wcharString, char* utf8Buffer, size_t bufferSize) {
	size_t written = 0;
	for (; *wcharString != L'\0'; ++wcharString) {
		_swc2utf8(*wcharString, utf8Buffer, bufferSize, written);
	}
	if (written < bufferSize) {
		utf8Buffer[written] = '\0';
	}
}

// Inversed convertion UTF-8 → wchar_t
static wchar_t _sutf82wc(const char* utf8Char, size_t& bytesRead) {
	uint8_t firstByte = static_cast<uint8_t>(utf8Char[0]);
	wchar_t wchar = 0;
	bytesRead = 1;

	if (firstByte <= 0x7F) {
		return firstByte;
	}
	else if ((firstByte & 0xE0) == 0xC0) {
		if ((utf8Char[1] & 0xC0) != 0x80) return L'?';
		wchar = (firstByte & 0x1F) << 6 | (utf8Char[1] & 0x3F);
		bytesRead = 2;
	}
	else if ((firstByte & 0xF0) == 0xE0) {
		if ((utf8Char[1] & 0xC0) != 0x80 || (utf8Char[2] & 0xC0) != 0x80) return L'?';
		wchar = (firstByte & 0x0F) << 12 | (utf8Char[1] & 0x3F) << 6 | (utf8Char[2] & 0x3F);
		bytesRead = 3;
	}
	else if ((firstByte & 0xF8) == 0xF0) {
		if ((utf8Char[1] & 0xC0) != 0x80 || (utf8Char[2] & 0xC0) != 0x80 || (utf8Char[3] & 0xC0) != 0x80) return L'?';
		wchar = (firstByte & 0x07) << 18 | (utf8Char[1] & 0x3F) << 12 | (utf8Char[2] & 0x3F) << 6 | (utf8Char[3] & 0x3F);
		bytesRead = 4;
	}
	else {
		return L'?';
	}

	return wchar;
}
// Convert a UTF-8 string to a wide character string
static void _sutf8s2wcs(const char* utf8String, wchar_t* wcharBuffer, size_t wcharBufferSize) {
	size_t bytesRead = 0;
	size_t wcharIndex = 0;

	while (*utf8String != '\0' && wcharIndex < wcharBufferSize - 1) {
		wcharBuffer[wcharIndex++] = _sutf82wc(utf8String, bytesRead);
		utf8String += bytesRead;
	}

	wcharBuffer[wcharIndex] = L'\0'; // Agregar terminador
}
// Patch a branch instruction to jump to a function
void _sbranch(uint addr, void* functionBase, bool link = false) {

	// functionBase is name.
	// expresion equivalent to his OPD entry in module.

	uint32_t* target = (uint32_t*)addr; // <--
	uint32_t jmp = *(uint*)functionBase;
	uint32_t offset = jmp - (uint32_t)target;
	if (offset & 0x3) offset &= ~0x3;
	*target = (0x48000000 | (offset & 0x03FFFFFC)) | (link ? 1 : 0);
	__dcbst(target);
	__sync();
	__isync();

}

void patcher(int Address, int Destination, bool Linked)
{
	int FuncBytes[4];
	Destination = *(int*)Destination;
	FuncBytes[0] = 0x3D600000 + ((Destination >> 16) & 0xFFFF);
	if (Destination & 0x8000)
		FuncBytes[0] += 1;
	FuncBytes[1] = 0x396B0000 + (Destination & 0xFFFF); // addi    %r11, %r11, dest&0xFFFF
	FuncBytes[2] = 0x7D6903A6; // mtctr    %r11
	FuncBytes[3] = 0x4E800420; // bctr
	if (Linked)
		FuncBytes[3] += 1; // bctrl
	sys_dbg_memcpy((void*)Address, FuncBytes, 4 * 4);
}
void hookfunction(uint32_t address, uint32_t patchedfunc, uint32_t patchstub, ...) {

	uint32_t normalFunctionStub[8], hookFunctionStub[4];
	sys_dbg_read_process_memory_ps3mapi(address, normalFunctionStub, 0x10);
	_kernmread(address, normalFunctionStub, 0x10);
	normalFunctionStub[4] = 0x3D600000 + ((address + 0x10 >> 16) & 0xFFFF);
	normalFunctionStub[5] = 0x616B0000 + (address + 0x10 & 0xFFFF);
	normalFunctionStub[6] = 0x7D6903A6;
	normalFunctionStub[7] = 0x4E800420;
	sys_dbg_write_process_memory_ps3mapi(patchstub, normalFunctionStub, 0x20);
	_kernmwrite(patchstub, normalFunctionStub, 0x20);
	hookFunctionStub[0] = 0x3D600000 + ((patchedfunc >> 16) & 0xFFFF);
	hookFunctionStub[1] = 0x616B0000 + (patchedfunc & 0xFFFF);
	hookFunctionStub[2] = 0x7D6903A6;
	hookFunctionStub[3] = 0x4E800420;
	sys_dbg_write_process_memory_ps3mapi(address, hookFunctionStub, 0x10);
	_kernmwrite(address, hookFunctionStub, 0x10);

	HOOK_COUNT++;
}

void hookfunction2(uint32_t address, uint32_t patchedfunc, uint32_t patchstub, ...) {
	//ps3_writelineF("hook %x -> %x, %x, \"%s\"", functionStartAddress, newFunction, functionStub, id);
	uint32_t normalFunctionStub[8], hookFunctionStub[4];
	sys::memcpy((void*)address, normalFunctionStub, 0x10);
	normalFunctionStub[4] = 0x3D600000 + ((address + 0x10 >> 16) & 0xFFFF);
	normalFunctionStub[5] = 0x616B0000 + (address + 0x10 & 0xFFFF);
	normalFunctionStub[6] = 0x7D6903A6;
	normalFunctionStub[7] = 0x4E800420;
	sys::memcpy((void*)patchstub, normalFunctionStub, 0x20);
	hookFunctionStub[0] = 0x3D600000 + ((patchedfunc >> 16) & 0xFFFF);
	hookFunctionStub[1] = 0x616B0000 + (patchedfunc & 0xFFFF);
	hookFunctionStub[2] = 0x7D6903A6;
	hookFunctionStub[3] = 0x4E800420;
	sys::memcpy((void*)address, hookFunctionStub, 0x10);

	HOOK_COUNT++;
}
template<typename T, typename T2>
void hookfunction(uint32_t address, T jumpFunc, T2 retFunc) {
	uint space = (uint) * (int**)(retFunc); // opd reinterpret.
	uint jump_ = (uint) * (int**)(jumpFunc);

	uint32_t normalFunctionStub[8], hookFunctionStub[4];
	sys_dbg_read_process_memory_ps3mapi(address, normalFunctionStub, 0x10);
	_kernmread(address, normalFunctionStub, 0x10);

	normalFunctionStub[4] = 0x3D600000 + ((address + 0x10 >> 16) & 0xFFFF);
	normalFunctionStub[5] = 0x616B0000 + (address + 0x10 & 0xFFFF);
	normalFunctionStub[6] = 0x7D6903A6;
	normalFunctionStub[7] = 0x4E800420;
	sys_dbg_write_process_memory_ps3mapi(space, normalFunctionStub, 0x20);
	_kernmwrite(space, normalFunctionStub, 0x20);

	hookFunctionStub[0] = 0x3D600000 + ((jump_ >> 16) & 0xFFFF);
	hookFunctionStub[1] = 0x616B0000 + (jump_ & 0xFFFF);
	hookFunctionStub[2] = 0x7D6903A6;
	hookFunctionStub[3] = 0x4E800420;
	sys_dbg_write_process_memory_ps3mapi(address, hookFunctionStub, 0x10);
	_kernmwrite(address, hookFunctionStub, 0x10);

}

// dummy function.
uint32_t _addr(void* f) {
	return *(uint_ptr)f;
}
int guessfix_storage_for_mc(int addr)
{
	//char getVal[1];
	//int val = sys_dbg_read_process_memory_ps3mapi(addr, getVal, 1);
	//_sys_printf("addr: %i | mem: %s\n", addr, (val == -2147418099 ? "False" : "True"));
	//if (val != -2147418099)
	//	return addr;
	//else
	//	return 0x000101C0;
	if (0x00010000 < addr && getHighestValue(0, addr) > addr ||
		0x10000000 < addr && 0x10EF0000 > addr ||
		0x10F30000 < addr && 0x11060000 > addr ||
		0x11220000 < addr && 0x136A0000 > addr ||
		0x20000000 < addr && 0x20060000 > addr ||
		0x30000000 < addr && getHighestValue(1, addr) > addr ||
		0x40000000 < addr && 0x40010000 > addr ||
		0x40100000 < addr && 0x40110000 > addr ||
		0x40200000 < addr && 0x40210000 > addr ||
		0x40300000 < addr && 0x40310000 > addr ||
		0x50000000 < addr && 0x52000000 > addr ||
		0x60000000 < addr && 0x64000000 > addr ||
		0xC0000000 < addr && 0xCF900000 > addr ||
		0xD0010000 < addr && 0xD0020000 > addr ||
		0xD0030000 < addr && 0xD0050000 > addr ||
		0xD0060000 < addr && 0xD00A0000 > addr ||
		0xD00B0000 < addr && 0xD0130000 > addr ||
		0xD0160000 < addr && 0xD02A0000 > addr ||
		0xD02B0000 < addr && 0xD02F0000 > addr)
		return addr;
	else
	{
		char getVal[1];
		int val = sys_dbg_read_process_memory_ps3mapi(addr, getVal, 1);
		//_sys_printf("addr: %i | mem: %s\n", addr, (val == -2147418099 ? "False" : "True"));
		if (val != -2147418099)
			return addr;
		else
			return 0x000101C0;
	}
}
static const char* ToString(bool boolean) {
	return boolean ? "true" : "false";
}

double _sisqrt(double x) {
	if (x <= 0.0f)
		return 0.0f;
	double result = x;

	result = 0.5f * (result + x / result);
	result = 0.5f * (result + x / result);
	result = 0.5f * (result + x / result);
	result = 0.5f * (result + x / result);
	result = 0.5f * (result + x / result);
	result = 0.5f * (result + x / result);
	result = 0.5f * (result + x / result);
	result = 0.5f * (result + x / result);
	result = 0.5f * (result + x / result);
	return result;
}
float _sisqrt(float x) {
	return _sisqrt((double)x);
}

// Convert an unsigned integer IP address to a string representation
char* _sip2strnw(unsigned int ip) {
	char* ipString = new char[16];
	sys::sprintf(ipString, "%u.%u.%u.%u",
		(ip >> 24) & 0xFF,
		(ip >> 16) & 0xFF,
		(ip >> 8) & 0xFF,
		ip & 0xFF);

	return ipString;
}
uint64_t u_randseed;

// Generate a random number using a linear congruential generator (LCG)
int _slcg() {
	uint64_t a = 1664525343;
	uint64_t c = 1013904223;
	u_randseed = a * u_randseed + c;
	return static_cast<int>(u_randseed % (RAND_MAX + 1));
}

#pragma region OVERRIDE_NEW
void* operator new(std::size_t size) { return _sys_malloc(size); }
void* operator new(std::size_t size, const _STD nothrow_t&) //_THROW0() // allocate or return null pointer
{
	return _sys_malloc(size);
}
void* operator new(size_t size, size_t align)
{
	return _sys_memalign(align, size);
}
void* operator new(size_t size, size_t align, const _STD nothrow_t&) //_THROW0()
{
	return _sys_memalign(align, size);
}
void* operator new[](std::size_t size) 	// allocate array or throw exception
{
	return _sys_malloc(size);
}
void* operator new[](std::size_t size, const _STD nothrow_t&)  // allocate array or return null pointer
{
	return _sys_malloc(size);
}
void* operator new[](size_t size, size_t align)
{
	return operator new(size, align);
}
void* operator new[](size_t size, size_t align, const _STD nothrow_t&)
{
	return operator new(size, align);
}
void operator delete(void* mem) //_THROW0()  // delete allocated storage
{
	if (!mem) {
		console_print_line("WARNING. Tried to delete instance from an null pointer.");
		return;
	}
	_sys_free(mem);
}
// The rest of these deletes will be called if the correspond call to
	// new throws an exception.
void operator delete(void* mem, const _STD nothrow_t&)
{
	_sys_free(mem);
}
void operator delete(void* ptr, void* prt2)
{
	return operator delete(ptr);
}
void operator delete(void* ptr, size_t align)
{
	return operator delete(ptr);
}
void operator delete(void* ptr, size_t align, const _STD nothrow_t&) //_THROW0()
{
	return operator delete(ptr);
}
void operator delete(void* ptr, size_t align, void* prt2)
{
	return operator delete(ptr);
}
void operator delete[](void* mem)  // delete allocated array
{
	_sys_free(mem);
}
void operator delete[](void* mem, const _STD nothrow_t&) _THROW0() // delete if nothrow array new fails -- REPLACEABLE
{
	_sys_free(mem);
}
void operator delete[](void* ptr, void* prt2)
{
	return operator delete(ptr, prt2);
}
void operator delete[](void* ptr, size_t align)
{
	return operator delete(ptr, align);
}
void operator delete[](void* ptr, size_t align, const _STD nothrow_t&) _THROW0()
{
	return operator delete(ptr, align);
}
void operator delete[](void* ptr, size_t align, void* prt2)
{
	return operator delete(ptr, align);
}

#pragma endregion



uint32_t _sys_bitwise_mix(uint32_t input) {
	input = (input ^ 0xdeadbeef) + (input << 4);
	input = input ^ (input >> 10);
	input = input + (input << 7);
	input = input ^ (input >> 13);
	input = input + (input << 11);
	input = input ^ (input >> 17);
	return input;
}

// Generate a unique identifier based on a string input
uint _suid(const char* a)
{
	uint r = 1;
	byte b = 1;
	int z = sys::strlen(a);
	for (int i = 0; i < z; i++)
	{

		byte m = (byte)(a[b] ^ (0x7 * b));
		m = (byte)((m - (13 * b)) ^ (b + 3));
		r += (uint)((m << 2) | (m >> 6));
		b++;
	}

	return r;
}

// Get the size of an explicitly known array
template <std::size_t size, typename Array>
uint _mgic_sizeof(Array(&array)[size]) {
	return size;
}
// Fill a memory region with NOP instructions
void _snop_itions(uint32_t sadr, int count) {
	auto ins = (uint*)sadr;
	for (int i = 0; i < count; i++)
		ins[i] = 0x60000000;
}
// Fill a memory region with NOP instructions until a specified address
void _snop_itions2adr(uint32_t sadr, uint adr) {
	auto ins = (uint*)sadr;
	for (; ins < (uint*)adr; ins++) {
		*ins = 0x60000000;
	}
	*ins = 0x60000000;
}


bool _sisnumc(char c) {
	return c >= '0' && c <= '9';
}

bool _sisblank(char c) {
	return c == ' ' || c == '\t' || c == '\n';
}

bool _siscomma(char c) {
	return c == ',';
}

bool _sisdot(char c) {
	return c == '.';
}
float _satof(const char* inicio, const char* fin, char decimalGap = ',') {
	float resultado = 0.0f;
	float factor = 1.0f;
	bool parteDecimal = false;
	float decimalFactor = 0.1f;

	if (*inicio == '-') {
		factor = -1.0f;
		++inicio;
	}

	for (const char* p = inicio; p != fin; ++p) {
		if (_sisdot(*p) || (*p) == decimalGap) {
			parteDecimal = true;
		}
		else if (_sisnumc(*p)) {
			if (!parteDecimal) {
				resultado = resultado * 10.0f + (*p - '0');
			}
			else {
				resultado += decimalFactor * (*p - '0');
				decimalFactor *= 0.1f;
			}
		}
	}

	return resultado * factor;
}

static std::string ToString(const std::wstring& r) {
	char buffer[1024]{ 0 };
	_sws2utf8s(r.c_str(), buffer, 1024);
	sys::memset(buffer, 0, 1024);
	return buffer;
}
template <typename...arg>
size_t s_printfcat(char* buffer, wchar_t* format, arg...s) {
	wchar bufferw[256]{ 0 };
	char bufferc[256]{ 0 };
	printfw(bufferw, 256, format, s...);
	_sws2utf8s(bufferw, bufferc, 256);
	std::strcat(buffer, bufferc);
	return sys::strlen(buffer);
}
void _trapped_assert(bool c, int16_t line, const char* fn, const char* conditionStr) {
	if (!c) {
		console_indent('=', 32);
		console_line("Assertion failed.");
		console_print_line("%s was false", conditionStr);
		console_print_line("Line: %i, in %s", line, fn);
		console_indent('=', 32);
		__builtin_trap();
	}
}
namespace ps3 {

	template <typename X, int X2>
	void _swrite_block(uint32_t addr, X(&varr)[X2], ...) {
		_sys_memcpy((void*)addr, varr, sizeof(X) * X2);
	}
	void _write8(uint32_t addr, byte x) {
		*(byte*)addr = x;
	}
}

#define TRAP(type, address, name, patcher_func)\
	type s##name(...){\
		__nop();\
		__nop();\
		__nop();\
		__nop();\
		__nop();\
	}\
void Patch_##name(){\
		hookfunction(address, _addr(patcher_func), _addr(s##name));	\
}


#define TRAP_SYS(type, address, name, patcher_func)\
	type s##name(...){\
		__nop();\
		__nop();\
		__nop();\
		__nop();\
		__nop();\
	}\
void Patch_##name(){\
		hookfunction2(address, _addr(patcher_func), _addr(s##name));	\
}

#define TRAP2(type, address, patcher_func) TRAP(type, address, patcher_func, patcher_func)
#define TRAP2_SYS(type, address, patcher_func) TRAP_SYS(type, address, patcher_func, patcher_func)


#endif

