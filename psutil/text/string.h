#pragma once
#include <psutil\memory.h>
#include <psutil\xmemory.h>
#include <psutil\xtypes.h>
#include <string>

_SYS_NS

/// <summary>
/// Counts the number of alphabetic characters (letters) in a given string.
/// </summary>
/// <param name="x">A pointer to the character array (C-string) to be analyzed.</param>
/// <returns>The count of letters that appear in the string.</returns>
int count_alpha(const char*);
/// <summary>
/// Counts the number of digits (integers) in a given string.
/// </summary>
/// <param name="x">A pointer to the character array (C-string) to be analyzed.</param>
/// <returns>The count of digits that appear in the string.</returns>
/// 
/// This function iterates through the given string and increments a counter 
/// for each character that is recognized as a digit (as determined by the `is_char_integer` function).
int countNumbers(const char* x);
/**
 * @brief Compares two text strings in a case-sensitive manner.
 *
 * This function compares two strings (`textData` and `query`) and checks if they are equal.
 * If the lengths of the strings are not the same, it returns -1.
 * Otherwise, it uses the `_sys_strncmp` function to perform the comparison.
 *
 * @param textData A pointer to the first text string.
 * @param query A pointer to the second text string.
 * @return An integer value:
 *         - 0 if the strings are equal.
 *         - A value less than 0 if the first string is less than the second.
 *         - A value greater than 0 if the first string is greater than the second.
 */
signed int case_compare(const char* textData, const char* query);
/**
 * @brief Compares two text strings in a case-sensitive manner.
 *
 * This function compares each character of the `textData` and `query` strings and counts
 * the number of positions where the characters differ.
 * If the lengths of the strings are not the same, it returns -1.
 *
 * @param textData A pointer to the first text string.
 * @param query A pointer to the second text string.
 * @return An integer value representing the number of positions where the
 *         strings differ, or -1 if the lengths of the strings are different.
 */
int compare(const char* textData, const char* query);


/// <summary>
/// Determines if a given string could represent an integer.
/// </summary>
/// <param name="x">A pointer to the character array (C-string) to be analyzed.</param>
/// <returns>Returns true if the string consists only of digits and contains no alphabetic characters.</returns>
/// 
/// This function checks whether the string has no letters (by using `countCharacters`) and consists 
/// only of digits (by ensuring the number of digits matches the string length).
bool could_be_int_representation(const char* x);

/**
* Determines if a given string could represent a valid floating-point2i number
* with a specified decimal separator.
*
* @param x A pointer to the character array (C-string) that potentially represents a float.
*          This string will be checked to see if it follows a valid floating-point2i format.
* @param decimalGap A character that represents the decimal separator in the float value.
*                   The default value is ',' (comma), which is commonly used in locales
*                   outside the US. You can change this to '.' for standard US formatting.
* @param ignoreTrailingSpace A boolean flag that indicates whether leading spaces should
*                            be ignored or not. If true, the function will skip any leading
*                            spaces before attempting to validate the string.
*                            The default value is true.
*
* @return Returns true if the string could represent a valid float in the specified format.
*         The string must begin with an integer part followed by the decimal separator,
*         and the remaining characters after the separator must be digits.
*         Returns false otherwise.
*
* The function works by:
* 1. Optionally skipping leading spaces if `ignoreTrailingSpace` is set to true.
* 2. Checking if the first non-space character is a digit (integer part).
* 3. Searching for the decimal separator within the string.
* 4. Verifying that there is at least one digit both before and after the decimal separator.
* 5. Ensuring all characters after the separator are digits.
*
* If any of the above checks fail, the function returns false.
*/
bool could_be_float_representation(const char* x, char decimalGap = ',', bool ignoreTrailingSpace = true);
int trim_non_numerical(char* data);
/// <summary>
/// Checks if a character is a valid hexadecimal character.
/// </summary>
/// <param name="c">The character to check.</param>
/// <returns>Returns true if the character is a valid hexadecimal digit (0-9, A-F, or a-f), otherwise false.</returns>
bool ishexc(char c);
byte hxtob(char c);
/// <summary>
/// Determines if a given string represents a valid hexadecimal value.
/// </summary>
/// <param name="x">A pointer to the character array (C-string) to be analyzed.</param>
/// <returns>Returns true if the string contains only valid hexadecimal characters, otherwise false.</returns>
bool could_be_hex_representation(const char* x);
/// <summary>
///	Parses a hexadecimal value representation of the given string assumming that all characters are valid.
/// </summary>
/// <param name="x">A pointer to the character array (C-string) to be analyzed.</param>
/// <returns>Returns the hexadecimal value represented by the string.</returns>
unsigned long long stoxu(char* x);

/**
* @brief Extracts a substring from a given character array.
*
* This function copies a segment of the `base` string into the `output` string, starting from a specified index
* and up to a specified number of characters.
*
* @param base The source character array from which the substring will be extracted.
* @param output The destination character array where the extracted substring will be stored.
* @param startIndex The starting index in the `base` array from which to begin copying.
* @param count The number of characters to copy from the `base` array.
* @return A pointer to the modified `output` array, containing the substring.
*/
char* substring(char* base, char* output, size_t startIndex, size_t count);

/**
 * @brief Extracts a substring starting from a given index until the end of the output string.
 *
 * This overload copies characters from `base` starting at the `startIndex` and continues
 * copying until the end of the `output` string.
 *
 * @param base The source character array from which the substring will be extracted.
 * @param output The destination character array where the extracted substring will be stored.
 * @param startIndex The starting index in the `base` array from which to begin copying.
 * @return A pointer to the modified `output` array, containing the substring.
 */
char* substring(char* base, char* output, size_t startIndex);
/**
 * @brief Extracts a substring starting from a given index until the end of the output string.
 *
 * This overload copies characters from `base` starting at the `startIndex` and continues
 * copying until the end of the `output` string.
 *
 * @param base The source character array from which the substring will be extracted.
 * @param output The destination character array where the extracted substring will be stored.
 * @param startIndex The starting index in the `base` array from which to begin copying.
 * @return A pointer to the modified `output` array, containing the substring.
 */
char* substring(char* base, char* output, size_t startIndex);

/**
* @brief Extracts a substring from a given character array.
*
* This function copies a segment of the `base` string into the `output` string, starting from a specified index
* and up to a specified number of characters.
*
* @param base The source character array from which the substring will be extracted.
* @param output The destination character array where the extracted substring will be stored.
* @param startIndex The starting index in the `base` array from which to begin copying.
* @param count The number of characters to copy from the `base` array.
* @return A pointer to the modified `output` array, containing the substring.
*/
char* substring(char* base, char* output, size_t startIndex, size_t count);
/**
 * @brief Compares two strings for equality.
 *
 * This function checks if the provided strings, `text` and `query`, are equal in length
 * and content. It first compares the lengths of both strings. If they are equal, it then
 * performs a safe comparison of their contents using the `safest_compare` function.
 *
 * @param text A pointer to the first string to compare.
 * @param query A pointer to the second string to compare.
 * @return true if both strings are equal; false otherwise.
 */
bool equals(const char* text, const char* query);

/**
* Replaces occurrences of characters by a qury in the specified range of the data string with the overridden character.
*
* @param data A pointer to the data (character array) where the replacements will be made.
* @param startIndex The starting index within the data where the replacements will begin.
* @param length The number of characters to consider for replacement starting from startIndex.
* @param query Character to replace
* @param overriden The character that will replace any character found in the query list.
* @return The number of replacements made. If no replacement is made, returns -1.
*/
signed int replace(char* data, size_t startIndex, size_t length, char query, char overriden);


/**
 * Replaces occurrences of characters from the query list in the entire data string.
 *
 * @param data A pointer to the data (character array) where the replacements will be made.
 * @param query Target character to replace
 * @param overriden The character that will replace any character found in the query list.
 * @return The number of replacements made. If no replacement is made, returns -1.
 */
signed int replace(char* data, char query, char overriden);


/**
 * Checks if an string starts with the specified phrase
 *
 * @param str A pointer to the data (character array)
 * @param query Target start to compare
 * @return True or false
 */
bool starts_with(const char* str, const char* query);

/**
 * @brief Counts the number of numeric characters in a given line of text.
 *
 * This function scans through the input string `str` and counts the number
 * of characters that represent numeric digits (e.g., '0' to '9'). The function
 * stops counting when it reaches a newline character ('\n' or '\r') or the end of the string ('\0').
 *
 * @param str The input character array (string) to process.
 *
 * @return int The number of numeric characters found in the input line.
 */
int count_numbers_in_line(const char* str);

/**
 * @brief Counts the number of spaces and tab characters in a given line of text.
 *
 * This function scans through the input string `str` and counts the number of
 * space (' ') and tab ('\t') characters. The function stops counting when it
 * encounters a newline character ('\n' or '\r') or the end of the string ('\0').
 *
 * @param str The input character array (string) to process.
 *
 * @return int The number of spaces and tabs found in the input line.
 */
int count_spaces_in_line(const char* str);
/**
 * @brief Counts the number of alphabetic characters in a given line of text.
 *
 * This function scans through the input string `str` and counts the number
 * of alphabetic characters (e.g., 'A' to 'Z' or 'a' to 'z'). The function stops
 * counting when it reaches a newline character ('\n' or '\r') or the end of the string ('\0').
 *
 * @param str The input character array (string) to process.
 *
 * @return int The number of alphabetic characters found in the input line.
 */
int count_letters_in_line(char* str);

int trim_start(char* buffer, char c);

int trim_end(char* buffer, char c);

bool split_line_by(const char* original, char key, char* buffer1, char* buffer2);

signed int index_of(const char* linePtr, char key);
std::string pad_left(std::string str, char c, size_t count);
std::string pad_right(std::string str, char c, size_t count);
void unescapeString(std::string& str);
std::string unescapeString(const char* data, int length);
std::string to_lower(const std::string& str);
std::string to_lower(const std::string& str);


#undef memalign
#undef memmove
#undef strlen
#undef strchr
#undef memcpy
#undef memset
#undef strncpy
#undef strcpy
#undef strncat
#undef strncmp
#undef strcmp
#undef memcmp
#undef malloc
#undef toupper
#undef tolower
#undef printf
#undef sprintf
#undef snprintf
#undef free
static inline void* memalign(size_t boundary, size_t size) {
	return _sys_memalign(boundary, size);
}
static inline void* memmove(void* dest, const void* src, size_t n) {
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

static inline void* nmalloc(size_t size) {
	void* m = _sys_malloc(size + sizeof(uint32_t));
	if (!m)
		return nullptr;
	*(uint32_t*)m = size;
	return (void*)(uintptr_t(m) + sizeof(uint32_t));
}
static inline void nfree(void* p) {
	if (p)
		_sys_free((void*)(uintptr_t(p) - sizeof(uint32_t)));
}
static inline size_t get_malloc_used_size(void* nptr) {
	if (!nptr)
		return 0;
	return *(uint32_t*)(uintptr_t(nptr) - sizeof(uint32_t));
}
static inline void* nrealloc(void* ptr, size_t new_size, bool clr = false) {
	if (!ptr) return nmalloc(new_size); // No origin specified. Assign new.
	if (new_size == 0) {
		nfree(ptr);                      // zero specified. Deassign.
		return nullptr;
	}

	size_t old_size = get_malloc_used_size(ptr); // Size count at the back px - 4u.
	void* new_block = nmalloc(new_size);
	if (!new_block) return nullptr;

	_sys_memmove(new_block, ptr, old_size < new_size ? old_size : new_size);
	if (clr)
		_sys_memset(ptr, 0, old_size);

	nfree(ptr);
	return new_block;
}



#define does(x) { x; }

static inline size_t strlen(const char* x) does(return _sys_strlen(x));
typedef int int32_t;
typedef uint32_t size_t;
typedef uint uint32_t;
typedef unsigned long long uint64_t;

template <typename x>	static inline x abs(x a) does(ABS(a));
template <typename x>	static inline x min(x a, x b) does(MIN(a, b));
template <typename x>	static inline x max(x a, x b) does(MAX(a, b));
static inline int memcmp(const void* a, const void* b, size_t num) does(return _sys_memcmp(a, b, num));
static inline void* memcpy(const void* srcDest, const void* srcSrc, size_t num) does(return _sys_memcpy((void*)srcDest, (void*)srcSrc, num));
static inline void* memset(void* srcDest, int value, size_t len) does(return _sys_memset(srcDest, value, len));
static inline char* strncpy(char* srcDest, const char* srcSrc, size_t srcSize) does(return _sys_strncpy(srcDest, srcSrc, srcSize));
static inline char* strcpy(char* srcDest, const char* srcSrc) does(return _sys_strcpy(srcDest, srcSrc));


static inline int strncmp(const char* srcDest, const char* srcSrc, size_t srcSize) does(return _sys_strncmp(srcDest, srcSrc, srcSize));

static inline int strcmp(const char* s1, const char* s2) {
	while (*s1 && (*s1 == *s2)) {
		++s1;
		++s2;
	}
	return *(unsigned char*)s1 - *(unsigned char*)s2;
}


static inline const char* strstr_array(const char* const strings[], const char* target, int count, bool matchCase) {
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

static inline int wcsncmp(const wchar_t* a, const wchar_t* b, size_t size) {
	size_t iter = 0;
	while (iter < size) {
		if (_sys_memcmp(a, b, 2) != 0) {
			return false;
		}
		iter++;
	}
	return iter == size;
}
static inline size_t wcslen(const wchar_t* widestring) {
	if (!widestring) {
		return 0;
	}
	size_t x = 0;
	while (widestring[x] != L'\0') {
		x++;
	}
	return x;
}

static inline void* malloc(size_t size) does(return _sys_malloc(size));
static inline void free(void* alloc) does(_sys_free(alloc));

static inline size_t find(const char* _Ptr,
	size_t _Off, size_t _Count, const char* content, size_t contentSize)
{	// look for [_Ptr, _Ptr + _Count) beginnng at or after _Off
	if (_Count == 0 && _Off <= contentSize)
		return (_Off);	// null string always matches (if inside string)

	size_t _Nm;
	if (_Off < contentSize && _Count <= (_Nm = contentSize - _Off))
	{	// room for match, look for it
		const char* _Uptr, * _Vptr;
		for (_Nm -= _Count - 1, _Vptr = content + _Off;
			(_Uptr = std::char_traits<char>::find(_Vptr, _Nm, *_Ptr)) != 0;
			_Nm -= _Uptr - _Vptr + 1, _Vptr = _Uptr + 1)
			if (std::char_traits<char>::compare(_Uptr, _Ptr, _Count) == 0)
				return (_Uptr - content);	// found a match
	}

	return static_cast<size_t>(-1);	// no match
}

template <typename ...args> static inline int printf(const char* format, args...x) does(_sys_printf(format, x...));
template <typename ...args> static inline int printf(const std::string & format, args...x) does(_sys_printf(format.c_str(), x...));

template <typename ...args> int snprintf(char* buff, size_t num, const char* frm, args...x) does(_sys_snprintf(buff, num, frm, x...));
static inline void strncat(char* dest, char* src, size_t num) { _sys_strncat(dest, src, num); }
static inline void* strchr(char* src, int ch)  does(return _sys_strrchr(src, ch));
static inline int tolower(int c) does(return _sys_tolower(c));
static inline int toupper(int c) does(return _sys_toupper(c));
#undef does
_SYS_ENS