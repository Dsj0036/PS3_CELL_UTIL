#pragma once
_SYS_NS

/**
 * @brief Performs a lightweight lexical scan of a numeric token.
 *
 * Searches for the specified delimiter starting from the current character
 * pointer, validates that the extracted range represents a numeric value,
 * and optionally converts the token into an integer result.
 *
 * This function does not allocate memory unless the output value is requested.
 * When conversion is required, the temporary string wrapper is used only for
 * lexical conversion.
 *
 * @param cur
 * Pointer to the beginning of the text range to inspect.
 *
 * @param terminatorDelimiter
 * Character that marks the end of the numeric token.
 *
 * @param length
 * Maximum number of characters available for scanning.
 *
 * @param output
 * Optional pointer receiving the converted integer value.
 * If null, the function only validates the token.
 *
 * @param count
 * Optional pointer receiving the number of characters consumed before the
 * delimiter.
 *
 * @return
 * Status code:
 *
 * - 0: Token found, validated, and optionally converted successfully.
 * - 1: Terminator delimiter was not found inside the provided range.
 * - 2: The extracted range does not represent a valid numeric value.
 *
 * @note
 * The returned count represents the amount of characters consumed from
 * @p cur up to (but excluding) the delimiter.
 *
 * @warning
 * The input range must remain valid for the duration of the operation.
 */
int lexical_walk(
	const char* cur,
	char terminatorDelimiter,
	int length,
	int* output,
	int* count
);


_SYS_ENS