#pragma once
#include "_ns.h"
#include "types.h"
namespace sys {

	// Convert a wide character to UTF-8 encoding
	void utf16_to_utf8_char(wchar_t wchar, char* utf8Buffer, size_t bufferSize, size_t& written);
	// Convert a wide character string to UTF-8 encoding
	void utf16_to_utf8_string(const wchar_t* wcharString, char* utf8Buffer, size_t bufferSize);

	// Inversed convertion UTF-8  wchar_t
	wchar_t utf8_to_utf16_char(const char* utf8Char, size_t& bytesRead);
	// Convert a UTF-8 string to a wide character string
	void utf8_to_utf16_string(const char* utf8String, wchar_t* wcharBuffer, size_t wcharBufferSize);
}