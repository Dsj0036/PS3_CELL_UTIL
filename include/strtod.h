#pragma once
#include <sys\types.h>
namespace sys {

	/**
	 * @brief Determines whether a character is considered whitespace.
	 *
	 * This helper function implements the whitespace characters accepted by
	 * the numeric parser. Supported characters are:
	 *
	 * - Space (`' '`)
	 * - Line feed (`'\n'`)
	 * - Carriage return (`'\r'`)
	 * - Horizontal tab (`'\t'`)
	 * - Vertical tab (`'\v'`)
	 * - Form feed (`'\f'`)
	 *
	 * @param x Character to evaluate.
	 *
	 * @return true if the character is whitespace, otherwise false.
	 */
	bool is_space(char x);
	/**
	 * @brief Implementation of a string-to-double conversion.
	 *
	 * Parses a character buffer containing a decimal floating-point representation
	 * and converts it into a double precision value.
	 *
	 * The parser supports:
	 *
	 * - Optional leading whitespace.
	 * - Optional sign (`+` or `-`).
	 * - Integer and fractional components.
	 * - Scientific notation using `e` or `E`.
	 *
	 * Unlike the standard C runtime implementation, this function operates on a
	 * bounded buffer using an explicit length parameter.
	 *
	 * Expected formats:
	 *
	 * ```
	 * 10
	 * -10.25
	 * +3.14
	 * 1.5e10
	 * -2.0E-4
	 * ```
	 *
	 * @param text Input character buffer.
	 * @param len Number of characters available in the buffer.
	 * @param val Output destination for the parsed value. Can be nullptr.
	 *
	 * @return Error code:
	 *
	 * - `0` Conversion succeeded.
	 * - `1` Invalid input buffer.
	 * - `2` No numeric digits found.
	 * - `3` Multiple exponent markers detected.
	 * - `4` Multiple decimal points detected.
	 * - `5` Invalid alphabetic character detected.
	 * - `6` Invalid sign placement detected.
	 */
	extern int strtod(const char* text, size_t len, double* val);
}

