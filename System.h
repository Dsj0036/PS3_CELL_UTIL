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

#include <stdarg.h>
#include <xstring>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <ctype.h>
#include <math.h>
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

#define USE_PATCHES_ACCESSOR true
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
#define RAND_BY_TIME(uint_time) _sys_bitwise_mix(uint_time);
#define __UNKNOWN_DATA private:
#define TRUNC_DECIMALS(x) (floorf(x * 100) / 100.0)
#define HIWORD(l) ((unsigned short)(((unsigned long)(l) >> 16) & 0xFFFF))
#define LOWORD(l) ((unsigned short)((unsigned long)(l) & 0xFFFF))
#define MAKELONG(low, high) ((unsigned long)(((unsigned short)(low)) | (((unsigned long)((unsigned short)(high))) << 16)))
#define IMPORT_CALL_TO_INSTANCE(address, name, ret) \
    ret name() { \
        return CallToInstance<ret>(address, this); \
    }

#define IMPORT_CALL(addr, return_type, func_name, args) \
	private:  \
		static int32_t func_name##_opd[2] = { addr, 0x014CDAB0 }; \
		using func_name##_t = return_type(*)args; \
	public: \
	const __ImportedCalls::func_name##_t func_name = reinterpret_cast<__ImportedCalls::func_name##_t>(__ImportedCalls::func_name##_opd);


#define var(n,x)\
 auto n = x;\

#define or ||

#define TRACED_HOOK(opaddr, name, id, whenCalled)\
namespace TracedHook_name{\
CREATE_DUMMY_STUB(any, patched_stub_##name, ...);\
any patched_jump_##name(...){\
	id = (opaddr >> 4);\
	\
	if (whenCalled != nullptr){((void(*)(char*))whenCalled)(#name);}\
	return patched_stub_##name();\
}\
void Write(){hookfunction(opaddr, take(patched_jump_##name), take(patched_stub_##name));}\
\
\
\
}\

#define does(x) { x; }

#define CREATE_DUMMY_STUB(ret_type, func_name, ...) \
    ret_type func_name(__VA_ARGS__) { \
        __nop(); \
        __nop(); \
        __nop(); \
        __nop(); \
        __nop(); \
    }


#define CREATE_DUMMY_STATIC_STUB(ret_type, func_name, ...) \
    static ret_type func_name(__VA_ARGS__) { \
        __nop(); \
        __nop(); \
        __nop(); \
        __nop(); \
        __nop(); \
    }


typedef int ref;
typedef unsigned int uref;
typedef sys_ppu_thread_t thread;
typedef unsigned char byte;
typedef unsigned char uchar;
typedef unsigned int uint;
typedef uint nzvint; // non zero integer.
typedef uint32_t uint32;
typedef uint64_t uint64;
typedef uint32_t* uintaddr;
typedef uint _DWORD;
typedef unsigned long long _QWORD;
typedef short _WORD;
typedef byte _BYTE;
typedef uint address;
typedef uint64_t any;
typedef uint32_t HResult;

// delete for your project, dummy counter
int PATCHES_COUNT = 0;
#pragma endregion



#pragma endregion

#define breakreturn(x) return x; break
namespace sys {
	uint strlen(const char* x) does(_sys_strlen(x));
	typedef int int32_t;
	typedef uint32_t size_t;
	typedef uint uint32_t;
	typedef unsigned long long uint64_t;

	template <typename x>	x abs(x a) does(ABS(a));
	template <typename x>	x min(x a, x b) does(MIN(a, b));
	template <typename x>	x max(x a, x b) does(MAX(a, b));
	int memcmp(void* a, void* b, size_t num) does(return _sys_memcmp(a, b, num));
	void* memcpy(void* srcDest, void* srcSrc, size_t num) does(return _sys_memcpy(srcDest, srcSrc, num));
	void* memset(void* srcDest, int value, size_t len) does(return _sys_memset(srcDest, value, len));
	char* strncpy(char* srcDest, char* srcSrc, size_t srcSize) does(return _sys_strncpy(srcDest, srcSrc, srcSize));
	char* strcpy(char* srcDest, char* srcSrc) does(return _sys_strcpy(srcDest, srcSrc));
	int strncmp(char* srcDest, char* srcSrc, size_t srcSize) does(return _sys_strncmp(srcDest, srcSrc, srcSize));
	int wcsncmp(const wchar_t* a, const wchar_t* b, size_t size) {
		if (size <= 0) {
			return EINVAL;
		}
		size_t iter = 0;
		while (iter < size) {
			if (_sys_memcmp(a, b, 2) != 0) {
				return false;
				break;
				// loop will still there, even if returned, or at least i remember that
				// anyways this is no C# just for ensuring.
			}
			iter++;
		}
		return iter == size;
	}
	size_t wcslen(const wchar_t* widestring) {
		if (!widestring)
			return -1u;
		uint32_t x = 0;
		while (x < 0xFFFFFF && widestring[x] != 0)
			x++;
		return x;

	}
	void* malloc(size_t size) does(_sys_malloc(size));
	void* free(void* alloc) does(_sys_free(alloc));


	template <typename ...args> int printf(const char* format, args...x) does(_sys_printf(format, x...));
	template <typename ...args> int snprintf(const char* format, size_t num, args...x) does(sys::snprintf(format, num, x...));
	int strncat(char* dest, char* src, size_t num)  does(_sys_strncat(dest, src, num));
	int strchr(char* src, int ch)  does(_sys_strrchr(src, ch));
	int tolower(int c) does(return _sys_tolower(c));
	int toupper(int c) does(return _sys_toupper(c));
	template <typename ...args> int sprintf(char* buf, char* format, args...x) does(return _sys_sprintf(buf, format, x..));
}




#ifndef RAND_MAX
#define RAND_MAX	0x3fffffff
#endif

template <typename T>
struct property
{

private:
	T value;
public:
	property() {

	}
	property(T v) {
		this->value = v;
	}
	T& getValue() {
		return value;
	}
	operator T() {
		return value;
	}
};

template <class C, class T>
T reinterpret(C v) {
	return reinterpret_cast<T>(v);
}
template <typename From, typename To>
To cast(From v) {
	return static_cast<To>(v);
}
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

struct point
{
public:
	point() {  }
	point(int x, int y) : X(x), Y(y) {
	}
	point(bool isBoolean) { if (isBoolean) { X = 0; Y = 1; } }
	int X{ 0 };
	int Y{ 0 };
	point Append(int x, int y)
	{
		return point(X + x, Y + y);
	}
	point Append(point increment) {
		return point(X + increment.X, Y + increment.Y);
	}
	uint32_t* Unsigned() {
		uint32_t v[2]
		{ uint32_t(X), uint32_t(Y) };
		return v;
	}
	bool operator == (point alt) {
		return alt.X == X && alt.Y == Y;
	}
};

double sfloor(double x) {
	if (x < 0 && x != static_cast<int>(x)) {
		return static_cast<int>(x) - 1;
	}
	else {
		return static_cast<int>(x);
	}
}

double smod(double a, double b) {
	if (b == 0.0) {
		return 0.0;
	}
	double result = a - b * sfloor(a / b);
	return result;
}

void asm_write_nop_ori(void* a) {
	*(int*)a = 0x60000000;
}
int do_test_thread_inst(void(*fn)(uint64_t), const char* DebugName = "TestThread") {
	thread t;
	int errn = sys_ppu_thread_create(&t, fn, 0, 2000, 10000, 0, DebugName);
	if (errn == 0) {
		return t;
	}
	return errn;
}

char memory(unsigned int offset) {
	return *(unsigned char*)offset;
}

typedef wchar_t wchar;
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
float H2F(uint32_t value) {
	return *(float*)(byte*)&(value);
}

void execute_stub_reference() {
	__nop(); __nop(); __nop(); __nop(); __nop();
}


float get_decimal(float number) {
	int integerPart = static_cast<int>(number);
	float fractional = number - integerPart;
	float decimal = fractional * 10;
	return decimal;
}
int timecode_to_frames(int fps, int h, int m, int s) {
	return (h * fps * 3600) + (m * fps * 60) + (s * fps);
}
int format_float(char* buffer, float v) {
	const int factor = 100000;
	int value = static_cast<int>(v * factor + 0.5f);
	int a = value / 10000;
	int b = (value / 1000) % 10;
	int c = (value / 100) % 10;
	b = b < 0 ? 0 : b;
	c = c < 0 ? 0 : c;
	//int d = (value / 10) % 10;
	//int e = value % 10;
	return _sys_snprintf(buffer, 32, "%i,%i%if", a, b, c);
}
int format_double(char* buffer, double v) {
	const int factor = 100000;
	int value = static_cast<int>(v * factor + 0.5f);
	int a = value / 10000;
	int b = (value / 1000) % 10;
	int c = (value / 100) % 10;
	int d = (value / 10) % 10;
	int e = value % 10;
	return _sys_snprintf(buffer, 32, "%d.%i%i%i%i%i   ", a, b, c, d, e);
}
// Compares if data only atleast haves "data" in it, only compares the len of "comparing" inside "data"
bool safest_compare(const char* data, const char* comparing) {
	return !_sys_strncmp(comparing, data, _sys_strlen(comparing));
}
bool safest_endwith(const char* data, const char* end) {
	size_t data_len = _sys_strlen(data);
	size_t end_len = _sys_strlen(end);

	if (end_len > data_len) {
		return false;
	}

	// Ajustamos el puntero data a la posición correcta
	return !_sys_strcmp(data + data_len - end_len, end);
}
bool safest_wide_compare(const wchar* data, const wchar* comparing) {
	return std::wcsncmp(comparing, data, std::wcslen(comparing)) == 0;
}


int format_d1(char* buffer, double v) {
	const int factor = 100000;
	int value = static_cast<int>(v * factor + 0.5f);
	int a = value / 10000;
	int b = (value / 1000) % 10;
	int c = (value / 100) % 10;
	int d = (value / 10) % 10;
	int e = value % 10;
	return _sys_snprintf(buffer, 32, "%i.%i", a, b, c, d, e);
}

bool is_within_range(int r, int range) {
	return abs((double)r) < range;
}
#pragma once
void formatTime(char* buffer, size_t bufferSize, int hours, int minutes, int seconds) {
	s_snprintf(buffer, bufferSize, "%02d:%02d:%02d", hours, minutes, seconds);
}
// cstring or null
const char* getAMPM(int hour) {
	if (hour >= 0 && hour < 12) { return "AM"; }
	else if (hour >= 12 && hour <= 23) { return "PM"; }
	else { return nullptr; }
}
struct interval
{
	short max;
	short elapsed;
	void (*callback)() = nullptr;
	bool tick() {
		if (elapsed >= max) {
			elapsed = 0;
			return true;
		}
		elapsed++;
		return false;
	}
	interval(short max) { this->max = max; };
};


CellRtcDateTime epochToDatetime(time_t epoch) {
	const int SECONDS_IN_A_MINUTE = 60;
	const int SECONDS_IN_AN_HOUR = 3600;
	const int SECONDS_IN_A_DAY = 86400;

	const int SECONDS_IN_A_LEAP_YEAR = 31622400;
	const int SECONDS_IN_A_NON_LEAP_YEAR = 31536000;
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

	int day = epoch + 1; // day of the month
	CellRtcDateTime date;
	date.day = day;
	date.hour = hours;
	date.minute = hours;
	date.year = year;
	date.month = month;
	date.second = seconds;

	// Convert total days to microseconds
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
	char FW[8]; sprintf(FW, "%02X", info.firmware_version);
	return (float)(FW[0] & 0x0F) + val(FW + 2) * 0.00001f;
}
void print_byte(char* buffer, byte value) {
	char lett[0x3];
	if (value < 0x0A) {
		s_snprintf(lett, 3, "0%x", value);
	}
	else {
		s_snprintf(lett, 3, "%x", value);
	}
	_sys_strncpy(buffer, lett, 3);

}



template <class TYPE_A>
inline bool is(TYPE_A a, TYPE_A b) {
	return a == b;
}

int get_address(void* foo) {
	return reinterpret_cast<int>(&foo);
}
void defaultStub(...) {
	__nop(); __nop(); __nop(); __nop(); __nop();
}
char* createUserIdString(int userId) {
	char cadena[] = "00000000";

	char valor_str[20];
	sprintf(valor_str, "%d", userId);

	size_t longitud_original = sys::strlen(cadena);

	sys::strncpy(cadena + longitud_original - sys::strlen(valor_str), valor_str, sys::strlen(valor_str));
	return cadena;
}
char* createUserIdString(char* buffer, int userId) {

	char valor_str[20];
	sprintf(valor_str, "%d", userId);

	size_t longitud_original = sys::strlen(buffer);

	_sys_strncpy(buffer + longitud_original - sys::strlen(valor_str), valor_str, sys::strlen(valor_str));
	return buffer;
}
char* manual_cat(char* destination, const char* source) {
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
// mallocd
char* format(const char* format, Arguments... s) {
	short len = _sys_strlen(format);
	short buffSz = len < 8 ? 8 : len < 16 ? 16 : len < 32 ? 32 : len < 64 ? 64 : len < 78 ? 78 : len < 86 ? 86 : len < 120 ? 120 : 128;
	char* buff = (char*)malloc(buffSz);
	s_snprintf(buff, buffSz, format, s...);
	return buff;
}
short ctoi(char v) {
	return v - '0';
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
int atoint(const char* str) {
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
void hexstr_to_rgb(const char* hexString, int& r, int& g, int& b) {
	unsigned int hexValue = hexToUInt(hexString);
	r = (hexValue >> 16) & 0xFF;
	g = (hexValue >> 8) & 0xFF;
	b = hexValue & 0xFF;
}
int is_char_integer(char c){
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
double min(double a, double b) {
	return a > b ? b : b < a ? a : b;
}

double max(double a, double b) {
	return a > b ? a : b > a ? b : a;
}
void* zero(void* ptr, size_t sz) {
	return (void*)_sys_memset(ptr, 0, sz);
}

void* zero(const void* ptr, size_t sz) {
	return (void*)_sys_memset((void*)ptr, 0, sz);
}

char* zero(char* ptr) {
	return (char*)_sys_memset(ptr, 0, _sys_strlen(ptr));

}

// Function to remove a word from a string
bool str_remove_word(char* str, const char* wordToRemove) {
	bool f = false;
	// Iterate through the string
	while (*str) {
		// Find the occurrence of the word in the string
		const char* wordStart = str;
		const char* wordEnd = wordToRemove;
		while (*wordEnd && *wordStart == *wordEnd) {
			++wordStart;
			++wordEnd;
		}

		// If the entire word is found, shift the remaining characters
		if (!*wordEnd) {
			while (*wordStart) {
				*str++ = *wordStart++;
			}
			*str = '\0'; // Null-terminate the string
			return true;
		}

		// Move to the next character in the string
		++str;
	}
	return f;
}
// compara dos cadenas y devuelve verdadero si son iguales
bool str_equals(const char* a, const char* b) {
	// itera hasta que A sea nulo o a y b dejen de ser iguales.
	while (*a && (*a == *b)) {
		a++;
		b++;
	}
	// si todos los caracteres son los mismos en ambas cadenas,
	// se retornara verdadero.
	return *a == *b;

}
// Function to check if a specific word is present in a char*
bool str_contain(const char* str, const char* word) {
	while (*str != '\0') {
		// Check if the current substring matches the target word
		const char* tempStr = str;
		const char* tempWord = word;

		while (*tempStr != '\0' && *tempWord != '\0' && *tempStr == *tempWord) {
			tempStr++;
			tempWord++;
		}

		if (*tempWord == '\0') {
			// The entire word was found
			return true;
		}

		// Move to the next character in the main string
		str++;
	}

	// The word was not found
	return false;
}
int is_char_letter(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return true;
	return false;
}

char* strstr_custom(const char* haystack, const char* needle) {
	while (*haystack != '\0') {
		const char* h = haystack;
		const char* n = needle;

		while (*n != '\0' && *h == *n) {
			h++;
			n++;
		}

		if (*n == '\0') {
			return (char*)haystack;  // Found the needle in haystack
		}

		haystack++;
	}

	return NULL;  // Needle not found in haystack
}

size_t str_index_of_ph(const char* haystack, const char* target) {
	char* found = strstr_custom(haystack, target);

	if (found == NULL) {
		return (size_t)-1;  // Target not found in haystack
	}

	return found - haystack;
}

// Function to extract a substring from a string
char* str_extract_sub(const char* str, int start, int length) {
	if (str == nullptr || start < 0 || length < 0) {
		return nullptr;  // Invalid arguments
	}

	// Calculate the length of the original string
	int originalLength = 0;
	const char* temp = str;
	while (*temp != '\0') {
		++originalLength;
		++temp;
	}

	// Check if the start index is within bounds
	if (start >= originalLength) {
		return nullptr;  // Start index out of bounds
	}

	// Calculate the actual length of the substring
	int actualLength = std::min(length, originalLength - start);

	// Allocate memory for the substring
	char* substring = new char[actualLength + 1];  // +1 for null terminator

	// Copy the substring from the original string
	for (int i = 0; i < actualLength; ++i) {
		substring[i] = str[start + i];
	}

	// Null-terminate the substring
	substring[actualLength] = '\0';

	return substring;
}
// Function to find the index of a target character in a string
int str_index_of(const char* str, char target) {
	if (str == nullptr) {
		return -1;  // Invalid string
	}

	const char* tempStr = str;  // Use a separate pointer for iteration
	int index = 0;

	while (*tempStr != '\0') {
		if (*tempStr == target) {
			return index;  // Found the character, return its index
		}

		++tempStr;
		++index;
	}

	return -1;  // Character not found in the string
}
// compare Cstrings, returning differences, -1 if cannot loop.
int str_compare(const char* str1, const char* str2)
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
// shortcut for comparing by start.
bool haves_same_path(const char* filepath, const char* is) {
	return strncmp(is, filepath, _sys_strlen(is)) == 0;
}


template<typename R, typename... Arguments> inline R Call(long long function, Arguments... args)
{
	int toc_t[2] = { function,  0x014CDAB0 };
	R(*temp)(Arguments...) = (R(*)(Arguments...)) & toc_t;
	return temp(args...);
}
template<typename R, typename... Arguments> inline R Call2(uint toc, long long function, Arguments... args)
{
	int toc_t[2] = { function,  toc };
	R(*temp)(Arguments...) = (R(*)(Arguments...)) & toc_t;
	return temp(args...);
}

template <class Instance>
int CallInt(uintptr_t address, Instance* thisInst) {
	return Call<int>(address, (uint)thisInst);
}




// NPUB31419 PRINTFW
template <typename...arg>
size_t printfw(wchar_t* buff, size_t sz, wchar_t* format, arg...s) {
	// fucking linker error 
	//return std::swprintf(buff, sz, format, s...);

	return Call<any>(0x00CB9BD8, buff, sz, format, s...);

}
template <typename R, class Instance, typename ...Args>
R CallToInstance(uintptr_t address, Instance* thisInst, Args...s) {
	return Call<R>(address, (uint)thisInst, s...);
}

char* desreference_stringptr(unsigned int i) {
	char* s = (char*)i;
	if (s) {
		if (*s != '\0') {
			if (_sys_strlen(s) > 2) {

				return (char*)i;
			}
			else return "(null)";
		}
		else return "(null)";
	}
	else return "(null)";
}
bool is_null_str(char* r) {
	return r == 0 || (r[0] == '(' && r[1] == 'n' && r[2] == 'u' && r[3] == 'l' && r[4] == 'l' && r[5] == ')');
}
int str_atoi(char* str)
{
	// Initialize result
	int res = 0;
	for (int i = 0; (*(str + i)) != '\0'; ++i)
		if ((*(str + i)) != ' ') {
			res = res * 10 + (*(str + i)) - '0';
		}

	// return result.
	return res;
}


class allocation {
	const std::size_t storedSize;
	byte* data;
public:

	bool notNull() {
		return data != nullptr;
	}
	uintptr_t getPtr() {
		return reinterpret_cast<uintptr_t>(data);
	}
	template <typename T>
	T* const as() {
		return (T*)data;
	}
	const std::size_t getStorageSize() {
		return storedSize;
	}
	void clear() {
		_sys_memset(data, 0, storedSize);
	}
	allocation(std::size_t size) :storedSize(size) {
		data = (byte*)_sys_malloc(size);
	}
	~allocation() {
		_sys_free(data);
	}
};

void get_temperature(uint32_t a, uint32_t* b)
{
	system_call_2(383, (uint64_t)(uint32_t)a, (uint64_t)(uint32_t)b);
}
int32_t sys_dbg_read_process_memory(uint64_t address, void* data, size_t size)
{
	system_call_4(904, (uint64_t)sys_process_getpid(), address, size, (uint64_t)data);
	return_to_user_prog(int32_t);
}
int32_t sys_dbg_write_process_memory(uint64_t address, const void* data, size_t size)
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

void WriteMemory(int address, char hex)
{
	*(int*)address = hex;
}

//sys_timer_usleep
void sleep(usecond_t time)
{
	sys_timer_usleep(time * 1000);
}


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
	sys_dbg_read_process_memory(functionStub, normalFunctionStub, 0x10);
	sys_dbg_write_process_memory(functionStartAddress, normalFunctionStub, 0x10);

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
		_sys_printf("addr: %i | mem: %s\n", checkAddr, (val == -2147418099 ? "False" : "True"));
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
// This works ppu.
void sys_sleep(uint64_t milliseconds)
{
	sys_timer_usleep(milliseconds * 1000);
}
void sleep_for_real(uint64_t ms) {
	sys_timer_sleep(ms);
}

bool isAlphanumeric(char ch) {
	// Check if the character is an alphanumeric character
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
void restart_ps3() {

	system_call_3(379, 0x8201, NULL, 0);
}
bool containsAlphanumeric(const char* str) {
	while (*str) {
		if (isAlphanumeric(*str) != 0) {
			// The current character is alphanumeric
			return true;
		}
		++str;
	}
	// No alphanumeric characters found
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
const char* getFileExtension(const char* filename) {
	const char* dot = strrchr((char*)filename, '.');
	if (!dot || dot == filename) {
		return "";
	}
	return dot + 1;
}
static void wcharToUtf8(wchar_t wchar, char* utf8Buffer, size_t bufferSize, size_t& written) {
	if (wchar <= 0x7F) {
		if (written + 1 < bufferSize) {
			utf8Buffer[written++] = static_cast<char>(wchar);
		}
	}
	else if (wchar <= 0x7FF) {
		if (written + 2 < bufferSize) {
			utf8Buffer[written++] = static_cast<char>(0xC0 | (wchar >> 6));
			utf8Buffer[written++] = static_cast<char>(0x80 | (wchar & 0x3F));
		}
	}
	else if (wchar <= 0xFFFF) {
		if (written + 3 < bufferSize) {
			utf8Buffer[written++] = static_cast<char>(0xE0 | (wchar >> 12));
			utf8Buffer[written++] = static_cast<char>(0x80 | ((wchar >> 6) & 0x3F));
			utf8Buffer[written++] = static_cast<char>(0x80 | (wchar & 0x3F));
		}
	}
}
static void wcharStringToUtf8(const wchar_t* wcharString, char* utf8Buffer, size_t bufferSize) {
	size_t written = 0;
	for (const wchar_t* wchar = wcharString; *wchar != L'\0'; ++wchar) {
		wcharToUtf8(*wchar, utf8Buffer, bufferSize, written);
	}
	if (written < bufferSize) {
		utf8Buffer[written] = '\0';
	}
}
static wchar_t utf8ToWchar(char* utf8Char, size_t& bytesRead) {
	unsigned char* uchar = reinterpret_cast<unsigned char*>(utf8Char);
	wchar_t wchar = 0;

	int bytesToRead = 1;
	if ((*uchar & 0xF8) == 0xF0) {
		bytesToRead = 4;
		wchar = *uchar & 0x07;
	}
	else if ((*uchar & 0xF0) == 0xE0) {
		bytesToRead = 3;
		wchar = *uchar & 0x0F;
	}
	else if ((*uchar & 0xE0) == 0xC0) {
		bytesToRead = 2;
		wchar = *uchar & 0x1F;
	}
	else {
		wchar = *uchar;
	}

	for (int i = 1; i < bytesToRead; ++i) {
		wchar = (wchar << 6) | (uchar[i] & 0x3F);
	}

	bytesRead = bytesToRead;

	return wchar;
}
static void utf8ToWcharString(char* utf8String, wchar_t* wcharBuffer, size_t wcharBufferSize) {
	size_t bytesRead = 0;
	size_t wcharIndex = 0;

	while (*utf8String != '\0') {
		wchar_t wchar = utf8ToWchar(utf8String, bytesRead);
		if (wcharIndex < wcharBufferSize - 1) {
			wcharBuffer[wcharIndex++] = wchar;
		}
		utf8String += bytesRead;
	}

	wcharBuffer[wcharIndex] = L'\0';
}
namespace http_util
{
	char* removespace(const char* notify) {
		char buffer[0x500];
		_sys_strcat(buffer, notify);
		for (int i = 0; i < 0x500; i++) {
			if (buffer[i] == ' ') {
				buffer[i] = '+';
			}
		}
		return buffer;
	}
	char* SendRequest(char* URL, char* Path) {
		struct sockaddr_in SocketAddress;
		char bufferReturn[500];
		char RequestBuffer[1000];
		_sys_memset(RequestBuffer, 0x00, 1000);
		SocketAddress.sin_addr.s_addr = ((unsigned long)gethostbyname(URL)->h_addr);
		SocketAddress.sin_family = AF_INET;
		SocketAddress.sin_port = htons(80);
		int Socket = socket(AF_INET, SOCK_STREAM, 0);
		if (connect(Socket, (sockaddr*)&SocketAddress, sizeof(SocketAddress)) != 0) {
			return "";
		}
		_sys_strcat(RequestBuffer, "GET /");
		_sys_strcat(RequestBuffer, Path);
		_sys_strcat(RequestBuffer, "\r\nConnection: close\r\n\r\n");

		send(Socket, RequestBuffer, std::strlen(RequestBuffer), 0);
		while (recv(Socket, bufferReturn, 500, 0) > 0) {
			return bufferReturn;
		}
		socketclose(Socket);
	}
	void Notify(const char* notify) {
		char buffer[0x200];
		_sys_snprintf(buffer, 0x200, "notify.ps3mapi?msg=%s", notify);
		_sys_printf("%s\n", buffer);
		SendRequest("127.0.0.1", buffer);
	}
}

char* longToHexString(long number) {
	int numChars = sizeof(long) * 2;
	char hexString[32];
	for (int i = numChars - 1; i >= 0; --i) {
		int digit = number & 0xF;
		hexString[i] = (digit < 10) ? ('0' + digit) : ('A' + digit - 10);
		number >>= 4;
	}
	hexString[numChars] = '\0';

	return hexString;
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
// Trampoline.
void hookfunction(uint32_t address, uint32_t patchedfunc, uint32_t patchstub, ...) {
	//ps3_writelineF("hook %x -> %x, %x, \"%s\"", functionStartAddress, newFunction, functionStub, id);
	uint32_t normalFunctionStub[8], hookFunctionStub[4];
	sys_dbg_read_process_memory_ps3mapi(address, normalFunctionStub, 0x10);
	sys_dbg_read_process_memory(address, normalFunctionStub, 0x10);
	normalFunctionStub[4] = 0x3D600000 + ((address + 0x10 >> 16) & 0xFFFF);
	normalFunctionStub[5] = 0x616B0000 + (address + 0x10 & 0xFFFF);
	normalFunctionStub[6] = 0x7D6903A6;
	normalFunctionStub[7] = 0x4E800420;
	sys_dbg_write_process_memory_ps3mapi(patchstub, normalFunctionStub, 0x20);
	sys_dbg_write_process_memory(patchstub, normalFunctionStub, 0x20);
	hookFunctionStub[0] = 0x3D600000 + ((patchedfunc >> 16) & 0xFFFF);
	hookFunctionStub[1] = 0x616B0000 + (patchedfunc & 0xFFFF);
	hookFunctionStub[2] = 0x7D6903A6;
	hookFunctionStub[3] = 0x4E800420;
	sys_dbg_write_process_memory_ps3mapi(address, hookFunctionStub, 0x10);
	sys_dbg_write_process_memory(address, hookFunctionStub, 0x10);

	PATCHES_COUNT++;
}
void hookfunction(uintptr_t address, void* newfunc, void* newstub)
{
	hookfunction(address, (uint32_t)newfunc, (uint32_t)newstub);
}


namespace vector3_parse {

	int v3atoi(const char* str) {
		int result = 0;
		int sign = 1;
		if (*str == '-') {
			sign = -1;
			++str;
		}
		while (*str >= '0' && *str <= '9') {
			result = result * 10 + (*str - '0');
			++str;
		}

		return sign * result;
	}
	int customIsDigit(char c) {
		return (c >= '0' && c <= '9');
	}
	int customIsSpace(char c) {
		return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
	}
	char* customStrncpy(char* dest, const char* src, size_t n) {
		size_t i;
		for (i = 0; i < n && src[i] != '\0'; ++i) {
			dest[i] = src[i];
		}
		for (; i < n; ++i) {
			dest[i] = '\0';
		}
		return dest;
	}
	int parseVector3(const char* vectorStr, int* x, int* y, int* z) {

		*x = *y = *z = 0;
		while (*vectorStr && !customIsDigit(*vectorStr) && *vectorStr != '-') {
			++vectorStr;
		}
		if (*vectorStr == '\0') {
			return 0;
		}
		*x = v3atoi(vectorStr);
		while (*vectorStr && (customIsDigit(*vectorStr) || *vectorStr == '-')) {
			++vectorStr;
		}
		while (*vectorStr && !customIsDigit(*vectorStr) && *vectorStr != '-') {
			++vectorStr;
		}
		if (*vectorStr == '\0') {
			return 0; 
		}
		*y = v3atoi(vectorStr);
		while (*vectorStr && (customIsDigit(*vectorStr) || *vectorStr == '-')) {
			++vectorStr;
		}
		while (*vectorStr && !customIsDigit(*vectorStr) && *vectorStr != '-') {
			++vectorStr;
		}
		if (*vectorStr == '\0') {
			return 0; 
		}
		*z = v3atoi(vectorStr);

		return 1;
	}
}
#define itrcp hookfunction
uint32_t take(void* f) {
	return *(uintaddr)f;
}

#define NADDR(var) (#var " " + take(&var))
char readStrWide[32];
// 
char* readWide(uint address, int len = 16) {
	_sys_memset(readStrWide, 0, 32);
	int leng = len * 2;
	int index = 0;
	for (int i = 0; i < (leng); i += 2) {
		int c = *(unsigned char*)(address + i);
		if (c == 0) {
			c = *(unsigned char*)(address + i + 1);
			if (c != 0) {
				readStrWide[index] = c;
				index++;
			}
		}
		else
		{
			readStrWide[index] = c;
			index++;
		}
	}
	return readStrWide;
}
template <class T>
int arr_size(T* arr) {

	return sizeof(arr) / sizeof(arr[0]);
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
bool strcont(char* w1, char* w2)
{
	int i = 0;
	int j = 0;
	if (_sys_strlen(w1) == 0 || _sys_strlen(w2) == 0)
	{
		return false;
	}
	while (w1[i] != '\0')
	{
		if (w1[i] == w2[j])
		{
			int init = i;
			while (w1[i] == w2[j] && w2[j] != '\0')
			{
				j++;
				i++;
			}

			if (w2[j] == '\0')
			{
				return true;
			}
			j = 0;
		}

		i++;
	}

	return false;
}


double nsqrtf(double x) {
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
float nsqrtf(float x) {
	return nsqrtf((double)x);
}

char* interaddrToStr(unsigned int ip) {
	char* ipString = new char[16];
	sprintf(ipString, "%u.%u.%u.%u",
		(ip >> 24) & 0xFF,
		(ip >> 16) & 0xFF,
		(ip >> 8) & 0xFF,
		ip & 0xFF);

	return ipString;
}
template <class T>
class node {
public:
	node* next;
	T data;

	bool operator==(const node<T>& otro) const {
		return this->data == otro.data;
	}
	bool operator==(const node<T> otro) const {
		return this->data == otro.data;
	}
	node<T>() {};
};

template <class T>
class wire {
	int count = 0;
public:
	node<T> subs;
	wire<T>() {
		subs = node<T>();
		subs.next = nullptr;

	}
	void add(T data) {
		node<T>* n = &subs;
		while (n->next != nullptr) {
			n = n->next;
		}
		n->next = new node<T>();
		n->next->data = data;
		count++;
	}

	void clear() {
		subs.next = nullptr;
		count = 0;
	}

	int size() const {
		int count = 0;
		node<T>* current = subs.next;
		while (current != nullptr) {
			count++;
			current = current->next;
		}
		return count;
	}
	bool contains(T v) {
		node<T>* sub = subs.next;
		if (sub->data == v) {
			return true;
		}
		else
		{
			while (sub->next != nullptr) {
				if (sub->data == v) {
					break;
					return true;
				}
				sub = sub->next;
			}
		}
	}
	int get_count() const {
		return count;
	}
};
uint64_t _sys_seed;
int random() {
	uint64_t a = 1664525343;
	uint64_t c = 1013904223;
	_sys_seed = a * _sys_seed + c;
	return static_cast<int>(_sys_seed % (RAND_MAX + 1));
}
#define thread_create sys_ppu_thread_create

#pragma region OVERRIDE_NEW
void* operator new(std::size_t size) //_THROW1(_XSTD bad_alloc) // allocate or throw exception
{
	return _sys_malloc(size);
}
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

int threaded(void(*entry), const char* name = "threaded_function") {
	uint64 t;
	int errn = sys_ppu_thread_create(&t, [](uint64 f)->void {void(*s)() = (void(*)())f; s(); }, (uint64)entry, 1500, 5000, 0, name);
	return errn;
}


uint32_t _sys_bitwise_mix(uint32_t input) {
	input = (input ^ 0xdeadbeef) + (input << 4);
	input = input ^ (input >> 10);
	input = input + (input << 7);
	input = input ^ (input >> 13);
	input = input + (input << 11);
	input = input ^ (input >> 17);
	return input;
}


uint getStrUid(char* a)
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
template <std::size_t size, typename Array>
uint explicitArraySize(Array(&array)[size]) {
	return size;
}




template <typename T>
class observable
{
private:
	T data;
public:
	observable(T& data) {
		this->data = data;
	}

	observable(T* data) {
		if (data == nullptr) {
			throw EINVAL;
		}
		this->data = *data;
	}
	const T get() {
		return data;
	}
	int operator =(T* x) {
		throw EINVAL;
	}
};
template <typename T>
class not_null
{
	observable<T> data;
public:
	not_null(T& d) : data(d) {
	}
	not_null(T* d) : data(d) {

	}
	T const get() {
		return (data.get());
	}
	inline void set(const T* x) {
		if (x == nullptr) {
			throw EINVAL;
		}
		data = observable<T>(*x);
	}

};

template <typename Return, typename ...Arguments>
class Trampoline
{
public:
	Return(*function)(Arguments...) = nullptr;
	Return(*replacement)(Arguments...) = nullptr;

	static Return Call(Arguments...) {
		__nop();
		__nop();
		__nop();
		__nop();
		__nop();
	}

	void Write(uint32_t originalFunctionAddress, Return(*replacement)(Arguments...)) {
		Trampoline* x = (Trampoline*)(uint)(this);
		hookfunction(originalFunctionAddress, take(replacement), take(x->Call));
		function = (Return(*)(Arguments...))(originalFunctionAddress);
		this->replacement = replacement;
	}
};

void asm_nop_until(uint32_t sadr, int count) {
	auto ins = (uint*)sadr;
	for (int i = 0; i < count; i++)
		ins[i] = 0x60000000;
}


bool esDigito(char c) {
	return c >= '0' && c <= '9';
}

bool esEspacio(char c) {
	return c == ' ' || c == '\t' || c == '\n';
}

bool esSeparador(char c) {
	return c == ',';
}

bool esPunto(char c) {
	return c == '.';
}

// Función que convierte una subcadena de caracteres en un número flotante
float repToFloat(const char* inicio, const char* fin, char decimalGap = ',') {
	float resultado = 0.0f;
	float factor = 1.0f;
	bool parteDecimal = false;
	float decimalFactor = 0.1f;

	if (*inicio == '-') {
		factor = -1.0f;
		++inicio;
	}

	for (const char* p = inicio; p != fin; ++p) {
		if (esPunto(*p) || (*p) == decimalGap) {
			parteDecimal = true;
		}
		else if (esDigito(*p)) {
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

// Función que interpreta una secuencia de flotantes separada por comas
template <std::size_t N>
bool extract_floats(const char* cadena, std::size_t longitud, float(&valores)[N]) {
	const char* inicio = cadena;
	const char* fin = cadena + longitud;
	std::size_t indice = 0;

	while ((inicio < fin) && (indice < N)) {
		// Saltar espacios en blanco al inicio
		while (inicio < fin && esEspacio(*inicio)) {
			++inicio;
		}

		// Encontrar el final del número flotante
		const char* numFin = inicio;
		while (numFin < fin && !esSeparador(*numFin)) {
			++numFin;
		}

		// Convertir la subcadena en un número flotante
		if (inicio != numFin) {
			valores[indice++] = repToFloat(inicio, numFin);
		}

		// Avanzar al siguiente carácter (después de la coma)
		inicio = numFin + 1;
	}

	return indice == N;
}
namespace ps3 {

	template <typename X, int X2>
	void WriteBytes(uint32_t addr, X(&var)[X2], ...) {
		_sys_memcpy((void*)addr, var, sizeof(X) * X2);
	}
	void WriteByte(uint32_t addr, byte x) {
		*(byte*)addr = x;
	}
}
#endif