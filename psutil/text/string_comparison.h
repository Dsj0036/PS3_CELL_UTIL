#pragma once
#include <psutil\ns.h>
#include <string>
_SYS_NS


/**
 * @brief Specifies the rules for comparing strings.
 */
	
	typedef enum {
	ordinal,           /**< Compares strings based on binary value of each character (case-sensitive). */
	ordinalIgnoreCase, /**< Compares strings based on binary value of each character (case-insensitive). */
	exact,             /**< Compares strings for exact binary equality (byte-by-byte). */
	exactIgnoreCase   	 /**< Compares strings for exact lexical equality*/
} e_string_comparison;


/**
 * @brief Compares two character arrays ignoring case for a specified number of characters.
 *
 * @param a Pointer to the first character array.
 * @param b Pointer to the second character array.
 * @param count Number of characters to compare.
 * @return true if the specified character ranges are equal ignoring case; otherwise, false.
 */
int equals_ignore_case(const char* a, const char* b, size_t count);

/**
 * @brief Compares two character arrays for a specified number of characters, case-sensitive.
 *
 * @param a Pointer to the first character array.
 * @param b Pointer to the second character array.
 * @param count Number of characters to compare.
 * @return The number of differing characters, or -1 if either pointer is null.
 */
int compare(const char* a, const char* b, int count);

/**
 * @brief Compares two substrings according to a specified comparison rule.
 *
 * @param a The first string.
 * @param offsetA Starting position within the first string.
 * @param b The second string.
 * @param offsetB Starting position within the second string.
 * @param count Number of characters to compare.
 * @param comparison The type of comparison to perform.
 * @return true if the specified substring ranges are considered equal according to the comparison rule; otherwise, false.
 */
int compare(const std::string& a, size_t offsetA, const std::string& b, size_t offsetB,size_t count, e_string_comparison comparison);
int compare(const std::string& left, const std::string& right, int length, e_string_comparison comparison);


_SYS_ENS