﻿// PS3 Cell Utilities by Josh
// cool in a way
// Should include for entire project.

#include <sys/timer.h>
#include <xstring>
#include <cellstatus.h>
#include <sys/prx.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <string.h>
#include <sys/prx.h>
#include <sys/syscall.h>
#include <sys/ppu_thread.h>
#include <sys/sys_time.h>
#include <sys/time_util.h>
#include <sys/process.h>
#include <sys/memory.h>
#include <sys/timer.h>
#include <sys/types.h>
#include <math.h>
#include <fastmath.h>
#include <cellstatus.h>
#include <sys/timer.h>
#include <cell/sysmodule.h>
#include <sys/random_number.h>
#include <ppu_intrinsics.h>
#include <spu_printf.h>
#include <ctype.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/process.h>
#include <netdb.h>
#include "cell/http/client.h"
#include "cell/http/error.h"
#include "cell/http/net_error.h"
#include "cell/http/util.h"
#include "cell/dbgrsx.h"
// http
#include "Types.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cell/http.h>
#include <netex/net.h>
#include "cell/cell_fs.h"
#include <../PS3_CELL_UTIL/Interop.h>
#include "cell/pad.h"



// OVERRIDE ALLOCATION OPERATORS
#include <yvals.h> // for _CSTD
#include <xstddef> // for _THROW1
#include <new> // for nothrow_t



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
typedef uint address;
typedef uint64_t any;


// delete for your project, dummy counter
int PATCHES_COUNT = 0;



template <typename T>
struct property
{

private:
	T value;
public:
	property(T v) {
		this->value = v;
	}
	T getValue() {
		return value;
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
#define NAMEOF(var) #var
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
template <typename T>
short count(T* pointer, uint len) {
	char i = 0;
	short c = 0;
	while (i < len) {
		if (*(pointer + i) != 0) {
			c++;
		}
		i++;
	}
	return c;
}
bool is_within_range(int r, int range) {
	return abs(r) < range;
}
#pragma once
void formatTime(char* buffer, size_t bufferSize, int hours, int minutes, int seconds) {
	snprintf(buffer, bufferSize, "%02d:%02d:%02d", hours, minutes, seconds);
}
// cstring or null
const char* getAMPM(int hour) {
	if (hour >= 0 && hour < 12) {return "AM";}
	else if (hour >= 12 && hour <= 23) {return "PM";}
	else {return nullptr;}
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

static char* buffer(int a) {
	char buff[1]{ a };
	return buff;
}
static char* buffer2(int a, int b) {
	char buff[2]{ a,b };
	return buff;
}
static char* buffer3(int a, int b, int c) {
	char buff[3]{ a,b, c };
	return buff;
}
static char* buffer4(int a, int b, int c, int d) {
	char buff[4]{ a,b,c, d };
	return buff;
}
static char* buffer5(int a, int b, int c, int d, int e) {
	char buff[5]{ a,b, c,d, e };
	return buff;
}
static char* buffer6(int a, int b, int c, int d, int e, int f) {
	char buff[6]{ a,b, c,d,e,f };
	return buff;
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
		snprintf(lett, 3, "0%x", value);
	}
	else {
		snprintf(lett, 3, "%x", value);
	}
	_sys_strncpy(buffer, lett, 3);

}



template <class TYPE_A>
inline bool is(TYPE_A a, TYPE_A b) {
	return a == b;
}
class repeating {
	uint variants[10];
	short filler_index = 0;
	bool checkIfHaves(uint value, short index = 0) {
		if (variants[index] == value) {
			return true;
		}
		else if ((index + 1) < 10)
		{
			if (checkIfHaves(value, index + 1)) {
				return true;
			}
		}
	}
	void add_flag(uint value) {
		if (filler_index < 10) {
			variants[filler_index] = value;
			filler_index++;
		}
	}
	void update(uint newOrExistent) {
		if (!checkIfHaves(newOrExistent)) {
			add_flag(newOrExistent);
		}

	}
	// This is better than a FOR
	void clear(short index) {
		variants[index] = 0;
		if (index < 10 && index > -1) {
			clear(index + 1);
		}
	}
};

inline char* raw(std::string s) {
	return  &s[0];
}
void removeWord(char* str, const char* wordToRemove) {
	int wordToRemoveLen = strlen(wordToRemove);
	int len = strlen(str);

	for (int i = 0; i <= len - wordToRemoveLen; ++i) {
		if (strncmp(str + i, wordToRemove, wordToRemoveLen) == 0) {
			// Word found, remove it by shifting characters
			for (int j = i; j <= len - wordToRemoveLen; ++j) {
				str[j] = str[j + wordToRemoveLen];
			}
			len -= wordToRemoveLen;
			// Adjust the index to recheck the current position
			--i;
		}
	}
}
// Target address of function, return type, function name, arguments.
#define MAKE_FN(address, return_type, func_name, args) \
    uint32_t func_name##opd[2] = { address, 0x014CDAB0 }; \
    using func_name##_t = return_type(*)args; \
    func_name##_t func_name = (func_name##_t)func_name##opd;
int get_address(void* foo) {
	return reinterpret_cast<int>(&foo);
}
void defaultStub(...) {
	__nop(); __nop(); __nop(); __nop(); __nop();
}
size_t len(const char* str) {
	size_t length = 0;
	while (*str != '\0') {
		++length;
		++str;
	}
	return length;
}

void increase(short& i, short limit) {
	short soon = i + 1;
	if (soon >= limit) {
		i = 0;
		return;
	}
	else if (soon < -1)
	{
		i = 0;
	}
	else
	{
		i += i;
	}
}
void increase(short& i, short value, short limit) {
	short soon = i + value;
	if (soon >= limit) {
		i = 0;
		return;
	}
	else if (soon < -1)
	{
		i = 0;
	}
	else
	{
		i += i;
	}
}
char* createUserIdString(int userId) {
	char cadena[] = "00000000";

	char valor_str[20];
	sprintf(valor_str, "%d", userId);

	size_t longitud_original = strlen(cadena);

	strncpy(cadena + longitud_original - strlen(valor_str), valor_str, strlen(valor_str));
	return cadena;
}
char* createUserIdString(char* buffer, int userId) {

	char valor_str[20];
	sprintf(valor_str, "%d", userId);

	size_t longitud_original = strlen(buffer);

	_sys_strncpy(buffer + longitud_original - strlen(valor_str), valor_str, strlen(valor_str));
	return buffer;
}
char* cat(char* destination, const char* source) {
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
	snprintf(buff, buffSz, format, s...);
	return buff;
}
short ctoi(char v) {
	return v - '0';
}
int ca(int a) {
	return a;
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
void add_json_property(std::string& json, char* propertyName, char* propertyValue) {
	json += "\"";
	json += propertyName;
	json += "\":\"";
	json += propertyValue;
	json += "\"\n";
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

	// Skip leading whitespace
	while (str[i] == ' ')
		i++;

	// Check for sign
	if (str[i] == '-') {
		sign = -1;
		i++;
	}
	else if (str[i] == '+') {
		i++;
	}

	// Convert digits to integer
	while (str[i] >= '0' && str[i] <= '9') {
		result = result * 10 + (str[i] - '0');
		i++;
	}

	return sign * result;
}

void hexstr_to_rgb(const char* hexString, int& r, int& g, int& b) {


	// Convert hexadecimal string to integer value
	unsigned int hexValue = hexToUInt(hexString);

	// Extract RGB values
	r = (hexValue >> 16) & 0xFF;
	g = (hexValue >> 8) & 0xFF;
	b = hexValue & 0xFF;
}

void* read(int address) {
	return (void*)(address);
}
int is_char_integer(char c)
{
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
		return false;
	return true;
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
bool haves_same_path(const char* filepath, const char* is) {
	return strncmp(is, filepath, _sys_strlen(is)) == 0;
}
// Equals
bool str_equals_advanced(const char* str1, const char* str2) {
	int a = len(str1);
	int b = len(str2);

	if (a != b) {
		return false;
	}
	else {
		int i = 0;

		// Use additional pointers for comparison without modifying original pointers
		const char* ptr1 = str1;
		const char* ptr2 = str2;

		while (i < a) {
			char ac = *ptr1++;
			char bc = *ptr2++;

			if (ac != bc) {
				return false;
			}

			i++;
		}

		return true;
	}
}
// Function to find the first occurrence of any character from the 'charset' in 'str'
char* _strpbrk(const char* str, const char* charset) {
	if (str == nullptr || charset == nullptr) {
		return nullptr;  // Invalid arguments
	}

	while (*str != '\0') {
		const char* charInCharset = charset;
		while (*charInCharset != '\0') {
			if (*str == *charInCharset) {
				return const_cast<char*>(str);  // Found a match
			}
			++charInCharset;
		}
		++str;
	}

	return nullptr;  // No match found
}

char* _strtok(char* str, const char* delimiter) {
	static char* lastToken = nullptr;  // Holds the state between calls

	// If a new string is given, update the lastToken
	if (str != nullptr) {
		lastToken = str;
	}

	// If there's no more string to tokenize, return nullptr
	if (lastToken == nullptr || *lastToken == '\0') {
		return nullptr;
	}

	// Find the next occurrence of the delimiter
	char* tokenStart = lastToken;
	char* tokenEnd = _strpbrk(lastToken, delimiter);

	// If the delimiter is found, replace it with null terminator
	if (tokenEnd != nullptr) {
		*tokenEnd = '\0';
		lastToken = tokenEnd + 1;  // Move to the next character after the delimiter
	}
	else {
		lastToken = nullptr;  // No more tokens
	}

	return tokenStart;
}
void splitAndRetrieve(const char* input, char* result) {
	int i = 0;

	// Find the position of '=' in the input string
	while (input[i] != '=' && input[i] != '\0') {
		i++;
	}

	// If '=' is found, copy the right part to the result
	if (input[i] == '=') {
		int j = 0;
		while (input[i + 1 + j] != '\0') {
			result[j] = input[i + 1 + j];
			j++;
		}

		// Set the null terminator at the end of the result
		result[j] = '\0';
	}
	else {
		// If '=' is not found, set an empty string in the result
		result[0] = '\0';
	}
}
// find the index of the next occurrence of a specific symbol (i) in a character sequence (sequence). It starts searching from the position indicated by the parameter i and returns the index of the found symbol.
int find_next_symbol(const char* sequence, int i) {
	const char* find_1 = sequence;
	int index = 0;
	while (*find_1 != '\0' && *find_1 != '\n' && *find_1 != i) {
		index++;
		find_1++;
	}
	return index;
}
//  this function compares characters in the given sequence and substring until the end of either one is reached or a difference is found. It returns true if the sequence starts with the provided substring and false otherwise.
bool startsWith(const char* sequence, char* compare) {
	if (sequence == 0) { return false; }
	if (compare == 0) { return false; }
	const char* seq = sequence;
	const char* comp = compare;
	int diffs = 0;
	int ch = 0;
	while ((ch = *seq) != '\0' && (*compare != '\0')) {
		if (ch != *compare) {
			diffs++;
		}
		compare++;
		seq++;
	}
	return diffs == 0;
}
// Function to extract the filename from a path
char* extractFilename(const char* path) {
	if (path == NULL) {
		return NULL; // Handle invalid input
	}

	// Find the last occurrence of '/'
	const char* lastSlash = path;
	const char* current = path;

	while (*current != '\0') {
		if (*current == '/') {
			lastSlash = current + 1; // Move one position after the last '/'
		}
		++current;
	}

	// If '/' is not found, the entire path is the filename
	if (*lastSlash == '\0') {
		return NULL; // Empty filename
	}

	// Calculate the length of the filename
	size_t filenameLength = _sys_strlen(lastSlash);

	// Allocate memory for the filename
	char* filename = (char*)_sys_malloc((filenameLength + 1) * sizeof(char)); // +1 for the null terminator

	if (filename == NULL) {
		return NULL; // Memory allocation failed
	}

	// Copy the filename to the new buffer
	_sys_strcpy(filename, lastSlash);

	return filename;
}
short generateUniqueId(const char*& text) {
	short value{ 0 };
	auto len = _sys_strlen(text);
	for (byte i = 0; i < len; i++) {
		byte asc = text[i];
		value += (asc + (i));
	}
	value -= len;
	return value;
}


bool isNotWeird(char c) {
	return c >= 33 && c < 127;
}
// cstring is fully alpha numeric.
bool isNotWeird(char* str) {
	if (!str) {
		return false;
	}
	else
	{
		char* cc = str;
		while (*cc != '\0') {
			if (!isNotWeird(*cc)) {
				return false;
				break;
			}
			cc++;
		}
		return true;
	}
}

// Convert a hex character to its decimal equivalent
int hexCharToDecimal(char hexChar) {
	if (hexChar >= '0' && hexChar <= '9') {
		return hexChar - '0';
	}
	else if (hexChar >= 'A' && hexChar <= 'F') {
		return hexChar - 'A' + 10;
	}
	else if (hexChar >= 'a' && hexChar <= 'f') {
		return hexChar - 'a' + 10;
	}
	return -1;  // Invalid hex character
}

void aptf(char* file, char buf[] = 0, int size = 0) {
	int err;
	int fd;
	uint64_t nrw;
	int ret;
	err = cellFsOpen(file, CELL_FS_O_RDWR | CELL_FS_O_APPEND | CELL_FS_O_CREAT, &fd, NULL, 0);
	if (size != 0)
		err = cellFsWrite(fd, (const void*)buf, (uint64_t)size, &nrw);
	err = cellFsClose(fd);
}
void aptff(char* file, char buf[] = 0)
{
	aptf(file, buf, strlen(buf));
}
// Convert a hexadecimal string to an RGB color
bool hexStringToColor(const char* hexString, int* red, int* green, int* blue) {
	if (hexString == NULL || red == NULL || green == NULL || blue == NULL) {
		return false;
	}

	*red = 0;
	*green = 0;
	*blue = 0;

	// Skip the '0x' or '0X' prefix if present
	if (hexString[0] == '0' && (hexString[1] == 'x' || hexString[1] == 'X')) {
		hexString += 2;
	}

	// Iterate through the hex string
	int index = 0;
	while (*hexString != '\0') {
		if (index >= 200) {
			char* f = "/dev_hdd0/tmp/dclient/session_log.log";
			aptff(f, "Parsing hex failed when received: ");
			aptff(f, (char*)hexString);
			aptff(f, "as param\n");
			red = 0;
			green = 0;
			blue = 0;
			return false;
			break;

		}
		*red = (*red << 4) + hexCharToDecimal(*hexString++);
		*green = (*green << 4) + hexCharToDecimal(*hexString++);
		*blue = (*blue << 4) + hexCharToDecimal(*hexString++);
		index++;
	}

	return true;
}

namespace HTTP
{
#define __WEB_H

	//int _HTTP_POOL_BUFFER = 0x10030000;
#define HTTP_POOL_SIZE      (64 * 1024)
#define HTTP_POOL_BUFFER 0x10030000 //change this to an address with a free size of 0x10000 bytes
	static char r_buffer[0x6000];  //MAX is 0x6000

	void memCpy(void* destination, const void* source, size_t num)
	{
		for (int i = 0; i < num; i++)
		{
			*((char*)destination + i) = *((char*)source + i);
		}
	}


	void memFree(char* ptr, int len)
	{
		for (int i = 0; i < len; i++)
		{
			*(char*)(ptr + i) = 0x00;
		}
	}


	int strCmp(const char* str1, const char* str2)
	{
		int diff = 0;

		if (*(str1) == 0x00 || *(str2) == 0x00) { return -1; }

		for (int i = 0; i < 0x600; i++)
		{
			if (*(str1 + i) == 0x00 || *(str2 + i) == 0x00) { break; }
			if (*(str1 + i) != *(str2 + i)) { diff++; }
		}

		return diff;
	}
	// MEMORY WARNING, SHOULD UPDATE FOR USING 'SOCKET' INSTEAD
	void SendRequest(char* url, char* retBuffer, int bufMaxLen) //url = url to request ("http://www.google.com/")    | retBuffer = ptr where the answer will be written to  | bufMaxLen = Max length of the buffer
	{
		if (bufMaxLen > 0x4000) { return; } //ERROR, bufMaxLen is TOO BIG

		CellHttpClientId client = 0;
		CellHttpTransId trans = 0;
		CellHttpUri uri;
		int ret;
		bool has_cl = true;
		uint64_t length = 0;
		uint64_t recvd;
		size_t poolSize = 0;
		void* uriPool = NULL;
		void* httpPool = NULL;
		const char* serverName;
		size_t localRecv = 0;

		serverName = url;  //set url
		memFree(r_buffer, bufMaxLen);

		sys_net_initialize_network(); //init network
		httpPool = (void*)HTTP_POOL_BUFFER; //address to: 0x10000 free bytes
		cellHttpInit(httpPool, HTTP_POOL_SIZE);
		cellHttpCreateClient(&client);
		cellHttpUtilParseUri(NULL, serverName, NULL, 0, &poolSize);
		char uriPoolAlloc[0x1024]; //allocate some space for the uri (a bit too much but eh)
		uriPool = uriPoolAlloc;
		cellHttpUtilParseUri(&uri, serverName, uriPool, poolSize, NULL);
		cellHttpCreateTransaction(&trans, client, CELL_HTTP_METHOD_GET, &uri);

		ret = cellHttpSendRequest(trans, NULL, 0, NULL); //send it :D
		{//make a new scope for the status
			int code = 0;
			ret = cellHttpResponseGetStatusCode(trans, &code);
		}//end of status scope

		cellHttpResponseGetContentLength(trans, &length);

		if (ret < 0)
		{
			if (ret == CELL_HTTP_ERROR_NO_CONTENT_LENGTH)
			{
				has_cl = false;
			}
		}

		recvd = 0;

		while ((!has_cl) || (recvd < length))
		{
			ret = cellHttpRecvResponse(trans, r_buffer, bufMaxLen - 1, &localRecv);
			recvd += localRecv;
			r_buffer[localRecv] = '\0'; //null terminate it
		}
		ret = 0;
		{
			for (int i = 0; i < bufMaxLen; i++)
			{
				retBuffer = r_buffer;
			}
		}  //OUTPUT

		cellHttpDestroyTransaction(trans);
		trans = 0;


		cellHttpDestroyClient(client); client = 0;


		cellHttpEnd();

		if (httpPool)
		{
			memFree((char*)httpPool, sizeof(httpPool));
			httpPool = NULL;
		}

		sys_net_finalize_network();
	}
}

char mem(int address, int index) {
	return *(char*)(ca(address + (index)));
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

//Hook Functions
int Memcpy(void* destination, const void* source, size_t size)
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

void WriteBytes(int address, char* input, int length)
{
	for (int i = 0; i < length; i++) {
		*(char*)(ca(address + (i))) = input[i];
	}
	*(char*)(ca(address + (length))) = 0x00;
}

char byteArrayz[1000][100];
char _byteArrayz[100];

char* ReadBytes(int index, int address, int length)
{
	for (int i = 0; i < length; i++)
	{
		byteArrayz[index][i] = *(char*)(ca(address + (i)));
	}
	return byteArrayz[index];
}

char* ReadBytes(int address, int length)
{
	for (int i = 0; i < length; i++)
	{
		_byteArrayz[i] = *(char*)(ca(address + (i)));
	}
	return _byteArrayz;
}

char returnRead[100][100];
char _returnRead[100];

char* readStr(int ofs)
{
	char* str = (char*)ca(ofs);
	if (strlen(str) < 50)
		return str;
	else
		return "error";
}
char* ReadString(int address)
{
	memset(&_returnRead[0], 0, sizeof(_returnRead));
	int strlength = 100;
	char* StrBytes = ReadBytes(address, strlength);
	for (int i = 0; i < strlength; i++)
	{
		if (StrBytes[i] != 0x00)
			_returnRead[i] = StrBytes[i];
		else
			break;
	}
	return _returnRead;
}

char* ReadString(int index, int address)
{
	memset(&returnRead[index][0], 0, sizeof(returnRead[index]));
	int strlength = 100;
	char* StrBytes = ReadBytes(index, address, strlength);
	for (int i = 0; i < strlength; i++)
	{
		if (StrBytes[i] != 0x00)
			returnRead[index][i] = StrBytes[i];
		else
			break;
	}
	return returnRead[index];
}

int WriteString(int address, char* string) {
	int FreeMem = 0x01D62000;
	int strlength = strlen(string);
	char* strpointer = *(char**)FreeMem = string;
	char* StrBytes = ReadBytes(50, *(int*)FreeMem, strlength);
	WriteBytes(address, StrBytes, strlength);
	*(char*)(ca(address + strlength + 1)) = 0x00;
	return strlength;
}

void reverse(char s[])
{
	int i, j;
	char c;

	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}
char itoaBuff[12][4];
char* itoa(int index, int n) {
	_sys_memset(itoaBuff[index], 0, sizeof(itoaBuff[index]));
	int i, sign;

	if ((sign = n) < 0)  /* record sign */
		n = -n;          /* make n positive */
	i = 0;
	do {		/* generate digits in reverse order */
		itoaBuff[index][i++] = n % 10 + '0';	/* get next digit */
	} while ((n /= 10) > 0);	/* delete it */
	if (sign < 0)
		itoaBuff[index][i++] = '-';
	itoaBuff[index][i] = '\0';
	reverse(itoaBuff[index]);
	return itoaBuff[index];
}

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
// Function to check if a string ends with a specified suffix
bool endsWith(const char* str, const char* suffix) {
	// Find the lengths of the suffix
	int suffixLength = 0;
	while (suffix[suffixLength] != '\0') {
		++suffixLength;
	}

	// Find the length of the string
	const char* tempStr = str;
	while (*tempStr != '\0') {
		++tempStr;
	}
	int strLength = tempStr - str;

	// If the suffix is longer than the string, it can't be a match
	if (suffixLength > strLength) {
		return false;
	}

	// Compare the suffix with the end of the string
	int suffixIndex = 0;
	for (int i = strLength - suffixLength; i < strLength; ++i) {
		if (str[i] != suffix[suffixIndex]) {
			return false; // Mismatch found
		}
		++suffixIndex;
	}

	// If we reached this point, the suffix matches the end of the string
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

// Function to get the extension of a file from a given path
const char* getFileExtension(const char* filename) {
	const char* dot = strrchr((char*)filename, '.');
	if (!dot || dot == filename) {
		return ""; // No extension found
	}
	return dot + 1; // Skip the dot itself
}

//Console Commands

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

		send(Socket, RequestBuffer, strlen(RequestBuffer), 0);
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

namespace ps3
{
	void WriteSingleByte(int address, unsigned int value)
	{
		char byts[]{ value };
		WriteBytes(address, byts, 1);
	}
	float ReadSingleFloat(int Address)
	{
		return *(float*)Address;
	}
	float floatArray[100];
	float* ReadFloat(int address, int length)
	{
		for (int i = 0; i < length; i++)
		{
			floatArray[i] = *(float*)(address + (i * 0x04));
		}
		return floatArray;
	}

	char byteArrayz[100];
	char* ReadBytes(int address, int length)
	{
		for (int i = 0; i < length; i++)
		{
			byteArrayz[i] = *(char*)(address + (i));
		}
		return byteArrayz;
	}

	void WriteFloat(int address, float* input, int length)
	{
		for (int i = 0; i < length; i++)
		{
			*(float*)(address + (i * 4)) = input[i];
		}
	}

	void WriteSingleFloat(int Address, float Input)
	{
		*(float*)Address = Input;
	}

	void WriteBytes(int address, char* input, int length)
	{
		for (int i = 0; i < length; i++)
		{
			*(char*)(address + (i)) = input[i];
		}
	}
	void WriteByte(int Address, unsigned char Input)
	{
		*(unsigned char*)Address = Input;
	}
	float intArray[100];
	float* ReadInt(int address, int length)
	{
		for (int i = 0; i < length; i++)
		{
			intArray[i] = *(int*)(address + (i * 0x04));
		}
		return intArray;
	}

	void WriteInt(int address, int* input, int length)
	{
		for (int i = 0; i < length; i++)
		{
			*(int*)(intArray + (i * 0x04)) = input[i];
		}
	}
	void WriteInt32(int Address, int Input)
	{
		*(int*)Address = Input;
	}

	void WriteString(int address, char* string)
	{
		int FreeMem = 0x1D00000;
		int strlength = strlen(string);
		*(char**)FreeMem = string;
		char* StrBytes = ReadBytes(*(int*)FreeMem, strlength);
		WriteBytes(address, StrBytes, strlength);
	}
	struct readstr
	{
		char returnRead[100];
	}ReturnRead[1000];
	int strcount;

	char* ReadStringz(int address)
	{
		strcount++;
		memset(&ReturnRead[strcount].returnRead[0], 0, sizeof(ReturnRead[strcount].returnRead));
		int strlength = 100;
		char* StrBytes = ReadBytes(address, strlength);
		for (int i = 0; i < strlength; i++)
		{
			if (StrBytes[i] != 0x00)
				ReturnRead[strcount].returnRead[i] = StrBytes[i];
			else
				break;
		}
		return ReturnRead[strcount].returnRead;
	}
	char byteArray[400];
	char* ReadBytesC(int address, int length)
	{
		for (int i = 0; i < length; i++)
		{
			byteArray[i] = *(char*)(address + (i));
		}
		return byteArray;
	}
	char returnRead[100];
	char* ReadStringC(int address)
	{
		memset(&returnRead[0], 0, sizeof(returnRead));
		int strlength = 100;
		char* StrBytes = ReadBytesC(address, strlength);
		for (int i = 0; i < strlength; i++)
		{
			if (StrBytes[i] != 0x00)
				returnRead[i] = StrBytes[i];
			else
				break;
		}
		return returnRead;
	}
	int ReadInt32(int Address)
	{
		return *(int*)Address;
	}
	char* ReadString(int Address)
	{
		return (char*)Address;
	}
	char returnReadd[100];
	char* ReadStringzz(int address, bool IncludeSpaces) {
		int strlength = 100;
		char* StrBytes = ps3::ReadBytes(address, strlength);

		char StopBytes = 0x00;
		if (!IncludeSpaces)
			StopBytes = 0x20;

		for (int i = 0; i < strlength; i++)
			returnReadd[i] = 0;
		for (int i = 0; i < strlength; i++) {
			if (StrBytes[i] != StopBytes)
				returnReadd[i] = StrBytes[i];
		}
		return returnReadd;
	}
};

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
	Memcpy((void*)Address, FuncBytes, 4 * 4);
}

void hookfunction(uint32_t address, uint32_t patchedfunc, uint32_t patchstub, const char* id = "") {
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

char* toSign(int character) {
	char s[]{ (char)character };
	return s;
}
char* sys_append(char* a, char* b) {
	char inp[200];
	_sys_snprintf(inp, 200, "%s%s", a, b);
	return inp;
}

namespace vector3_parse {

	size_t customStrlen(const char* str) {
		size_t len = 0;
		while (str[len] != '\0') {
			++len;
		}
		return len;
	}
	int customAtoi(const char* str) {
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
		// Initialize var
		*x = *y = *z = 0;

		// Parse x
		while (*vectorStr && !customIsDigit(*vectorStr) && *vectorStr != '-') {
			++vectorStr;
		}
		if (*vectorStr == '\0') {
			return 0; // Invalid format
		}
		*x = customAtoi(vectorStr);

		// Skip to next part
		while (*vectorStr && (customIsDigit(*vectorStr) || *vectorStr == '-')) {
			++vectorStr;
		}

		// Parse y
		while (*vectorStr && !customIsDigit(*vectorStr) && *vectorStr != '-') {
			++vectorStr;
		}
		if (*vectorStr == '\0') {
			return 0; // Invalid format
		}
		*y = customAtoi(vectorStr);

		// Skip to next part
		while (*vectorStr && (customIsDigit(*vectorStr) || *vectorStr == '-')) {
			++vectorStr;
		}

		// Parse z
		while (*vectorStr && !customIsDigit(*vectorStr) && *vectorStr != '-') {
			++vectorStr;
		}
		if (*vectorStr == '\0') {
			return 0; // Invalid format
		}
		*z = customAtoi(vectorStr);

		return 1; // Successful parsing
	}
}
#define itrcp hookfunction
uint32_t fn(void* f) {
	return *(uintaddr)f;
}

#define NADDR(var) (#var " " + fn(&var))
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

int atoi(const char* str) {
	int result = 0;
	int sign = 1;
	int i = 0;

	// Skip leading whitespace
	while (str[i] == ' ')
		i++;

	// Check for sign
	if (str[i] == '-') {
		sign = -1;
		i++;
	}
	else if (str[i] == '+') {
		i++;
	}

	// Convert digits to integer
	while (str[i] >= '0' && str[i] <= '9') {
		result = result * 10 + (str[i] - '0');
		i++;
	}

	return sign * result;
}

float nsqrtf(float x) {
	if (x <= 0.0f)
		return 0.0f;
	float result = x;

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
const char* nat_to_str(uint8_t nat) {
	if (nat == 0) {
		return "Open";
	}
	else if (nat == 1) {
		return "Moderate";
	}
	else if (nat == 2) {
		return "Badly";
	}
	else return "Unavailable";
}
// This function will store an empty char array for formatting at the specified buffer.
// Max: 256;

char* stack(char* forBuffer, int& size) {
	short len = _sys_strlen(forBuffer);
	size = 0;
	if (len > 0) {
		if (len < 8) {
			char b[12];
			size = 12;
			return b;
		}
		else if (len >= 8 && len <= 16) {

			char b[18];
			size = 18;
			return b;
		}
		else if (len >= 16 && len <= 32) {

			char b[34];
			size = 34;
			return b;
		}
		else if (len >= 32 && len <= 64) {

			char b[68];
			size = 68;
			return b;
		}
		else if (len >= 64) {

			char b[132];
			size = 132;
			return b;
		}
	}
	return nullptr;
}

template <class C, class T>
T reinterpret(C v) {
	return reinterpret_cast<T>(v);
}
template <typename From, typename To>
To cast(From v) {
	return static_cast<To>(v);
}
wchar_t* stackW(char* forBuffer, int& size) {

	short len = _sys_strlen(forBuffer);
	size = 0;
	if (len > 0) {
		if (len < 8) {
			wchar_t b[12];
			size = 12;
			return b;
		}
		else if (len >= 8 && len <= 16) {

			wchar_t b[18];
			size = 18;
			return b;
		}
		else if (len >= 16 && len <= 32) {

			wchar_t b[34];
			size = 34;
			return b;
		}
		else if (len >= 32 && len <= 64) {

			wchar_t b[68];
			size = 68;
			return b;
		}
		else if (len >= 64) {

			wchar_t b[132];
			size = 132;
			return b;
		}
	}
	return nullptr;
}


void printFloat(double value, char* buffer, int decimal_places) {
	double int_part, frac_part;
	frac_part = modf(value, &int_part);

	// Convertir la parte fraccional en un entero ajustado a la cantidad de decimales
	int scale = std::pow((double)10, (int)decimal_places);
	long long_frac_part = fabs(frac_part * scale);

	// Formatear como dos números enteros
	snprintf(buffer, 100, "%d.%0*lld", (int)int_part, decimal_places, long_frac_part);
}



std::string format_with_suffix(int& num) {
	std::string suffix;
	double formattedNumber = num;

	char buffer[50];
	if (num >= 1000000) {
		formattedNumber = num / 1000000.0;
		suffix = "M";
	}
	else if (num >= 1000) {
		formattedNumber = num / 1000.0;
		suffix = "K";
	}
	else {
		snprintf(buffer, 35, "%d", cast<double, int>(num));
		return std::string(buffer);
	}

	if (formattedNumber == static_cast<int>(formattedNumber)) {
		snprintf(buffer, sizeof(buffer), "%d%s", static_cast<int>(formattedNumber), suffix.c_str());

	}
	else {
		snprintf(buffer, sizeof(buffer), "%.1f%s", formattedNumber, suffix.c_str());
	}
	return std::string(buffer);

}


unsigned int _sys_seed;
// Generates a pseudo-random integer in the range [0, RAND_MAX]
int random() {
	// LCG parameters (these values are just examples, and you may need to choose different values for better randomness)
	const unsigned int a = 1664525;
	const unsigned int c = 1013904223;
	_sys_seed = a * _sys_seed + c;

	// Limit the range to [0, RAND_MAX]
	return static_cast<int>(_sys_seed % (RAND_MAX + 1));
}
#define thread_create sys_ppu_thread_create
#define alloc _sys_malloc

#pragma region OVERRIDE_NEW
void* operator new(std::size_t size) _THROW1(_XSTD bad_alloc) // allocate or throw exception
{
	return _sys_malloc(size);
}
void* operator new(std::size_t size, const _STD nothrow_t&) _THROW0() // allocate or return null pointer
{
	return _sys_malloc(size);
}
void* operator new(size_t size, size_t align)
{
	return _sys_memalign(align, size);
}
void* operator new(size_t size, size_t align, const _STD nothrow_t&) _THROW0()
{
	return _sys_memalign(align, size);
}
void* operator new[](std::size_t size) _THROW1(_XSTD bad_alloc)	// allocate array or throw exception
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
void operator delete(void* ptr, size_t align, const _STD nothrow_t&) _THROW0()
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
	int errn = sys_ppu_thread_create(&t, [](uint64 f)->void{void(*s)() = (void(*)())f;s();}, (uint64)entry, 1500, 5000, 0, name);
	return errn;
}


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

