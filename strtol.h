#pragma once
#include <sys\types.h>
namespace sys{

	/// @brief Converts a string representation of a number to an unsigned 64-bit integer.
	///
	/// This function parses a string containing either a decimal or hexadecimal number
	/// and converts it to a uint64_t value. Hexadecimal numbers must be prefixed with
	/// "0x" or "0X". The function performs extensive validation including checking for
	/// valid digit characters and string length constraints.
	///
	/// @param[in] text Pointer to the string to be converted. Must not be nullptr.
	/// @param[in] len Length of the string in characters. Must be greater than 0.
	/// @param[out] val Pointer to uint64_t where the converted value will be stored.
	///                 If nullptr, the conversion is still performed but the result
	///                 is not stored. Initialized to 0 if val is not nullptr.
	/// @param[out] err Pointer to int where error code will be stored (optional).
	///                 If nullptr, error information is not returned.
	///                 Error codes:
	///                 - 0: Success
	///                 - 1: Invalid input (null pointer, empty string, or zero-terminated)
	///                 - 4: No valid digits found in the string
	///                 - 5: String length exceeds maximum of 20 characters
	///
	/// @return 0 on successful conversion, 1 on error.
	///
	/// @note The function supports:
	///       - Decimal numbers: "123", "456789"
	///       - Hexadecimal numbers: "0xFF", "0x1A2B3C4D"
	///       - Case-insensitive hexadecimal digits (a-f, A-F)
	///       - Trailing non-digit characters are ignored after valid digits are consumed
	///
	/// @warning The maximum valid decimal value is 20 digits long. Values exceeding
	///          this length will return error code 5.
	///
	/// @example
	///       uint64_t result = 0;
	///       int error = 0;
	///       int ret = _atod("0xFF", 4, &result, &error);
	///       // result = 255, error = 0, ret = 0
	int strtol(const char* buf, size_t len, uint64_t* num);


}