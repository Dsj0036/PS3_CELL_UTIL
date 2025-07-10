#pragma once
#include "types.h"
#include "util.h"
namespace sys
{
	namespace formatter {

		inline char* _gdecstr(double val, int decimals = 4);
		inline char* _ghexstr(uint64_t anyh, bool uppercase, bool i64 = false);
		inline void _itow(int value, wchar_t* out, int max_len);
		inline bool _is_it(const wchar* data, const wchar* comparing);
		inline bool _is_it(const char* data, const char* comparing);
		inline bool is_alnum(int c);

		inline int wsnprintf_(wchar_t* buffer, size_t size, const wchar_t* format, ...) {
			if (!buffer || size == 0) return -1;

			size_t pos = 0;
			va_list args;
			va_start(args, format);
			while (*format && pos < size - 1) {
				if (*format == L'%') {
					format++;

					if (_is_it(format, L"ld")) {
						double val_ = va_arg(args, double);
						char* decstr = _gdecstr(val_, 0);
						if (!decstr) decstr = "~";
						char* itt = decstr;
						while (*itt && pos < size - 1) {
							buffer[pos++] = *itt++;
						}
						delete[] decstr;
						++format;
					}
					else if (_is_it(format, L"lx")) {
						uint64_t val_ = va_arg(args, uint64_t);
						char* hexstr = _ghexstr(val_, false, true);
						if (!hexstr) {
							hexstr = "~";
						}
						char* itt = hexstr;
						while (*itt && pos < size - 1) {
							buffer[pos++] = *itt++;
						}
						if (*hexstr != L'~') {
							delete[] hexstr;
						}
						++format;
					}
					else if (_is_it(format, L"ws")) {
						const wchar_t* str = va_arg(args, const wchar_t*);
						while (*str && pos < size - 1)
							buffer[pos++] = *str++;
					}
					else if (*format == L'.' && sys::util::isnum(*(format + 1))) {
						byte count_spec = *(format + 1) - L'0';
						switch (*(format + 2)) {
						case L'w': {
							const wchar_t* str = va_arg(args, const wchar_t*);
							while (*str && pos < size - 1 && count_spec) {
								buffer[pos++] = *str++;
								count_spec--;
							}
							++format;
							++format;
							break;
						}
						case L'f': { // originally not supported by system.
							double val_ = va_arg(args, double);
							char* decstr = _gdecstr(val_, count_spec);
							if (!decstr) decstr = "~";
							char* itt = decstr;
							while (*itt && pos < size - 1) {
								buffer[pos++] = *itt++;
							}
							delete[] decstr;
							++format;
							++format;
							break;
						}
						default: {
							if (pos < size - 1) buffer[pos++] = L'%';
							if (pos < size - 1) buffer[pos++] = *format;
							break;
						}
						}
					}
					else {
						switch (*format) {
						case L'd': {
							int value = va_arg(args, int);
							wchar_t numBuffer[16];
							_itow(value, numBuffer, 10);
							for (int i = 0; numBuffer[i] && pos < size - 1; ++i)
								buffer[pos++] = numBuffer[i];
							break;
						}
						case L'c': {
							wchar_t ch = (wchar_t)va_arg(args, int);
							if (pos < size - 1) buffer[pos++] = ch;
							break;
						}
						case L's': {
							const wchar_t* str = va_arg(args, const wchar_t*);
							while (*str && pos < size - 1)
								buffer[pos++] = *str++;
							break;
						}
						case L'f': {
							double val_ = va_arg(args, double);
							char* decstr = _gdecstr(val_);
							if (!decstr) {
								decstr = "~";
							}
							char* itt = decstr;
							while (*itt && pos < size - 1) {
								buffer[pos++] = *itt++;
							}
							if (*decstr != '~') {
								delete[] decstr;
							}
							break;
						}
						case L'x':
						case L'X': {
							uint64_t val_ = va_arg(args, uint64_t);
							char* R = _ghexstr(val_, *format == L'X', false);
							if (R) {
								char* itt = R;
								while (*itt && pos < size - 1) {
									buffer[pos++] = *itt++;
								}
								delete[] R;
							}
							break;
						}
						case L'%': {
							if (pos < size - 1) buffer[pos++] = L'%'; // escape.
							break;
						}
						default: {
							if (pos < size - 1) buffer[pos++] = L'%';
							if (pos < size - 1) buffer[pos++] = *format;
							break;
						}
						}
					}
				}
				else {
					buffer[pos++] = *format;
				}
				++format;
			}

			va_end(args);
			buffer[pos] = L'\0';

			return static_cast<int>(pos);
		}

		inline int snprintf_(char* buffer, size_t size, const char* format, ...) {
			if (!buffer || size == 0) return -1;

			size_t pos = 0;
			va_list args;
			va_start(args, format);
			bool gotsRemainingSpecifiers = false;

			while (*format && pos < size - 1) {
				if (*format == '%') {
					format++;  // Move to the specifier

					if (_is_it(format, "ld")) {
						double val_ = va_arg(args, double);
						char* decstr = _gdecstr(val_, 0);
						if (!decstr) decstr = "~";
						char* itt = decstr;
						while (*itt && pos < size - 1) {
							buffer[pos++] = (char)*itt++;
						}
						delete[] decstr;
						format++; format++;  // Skip the 'l' and 'd'
					}
					else if (_is_it(format, "lx")) {
						uint64_t val_ = va_arg(args, uint64_t);
						char* hexstr = _ghexstr(val_, false, true);  // Check whether the flag is working properly
						if (!hexstr) {
							hexstr = "~";
						}
						char* itt = hexstr;
						while (*itt && pos < size - 1) {
							buffer[pos++] = (char)*itt++;
						}
						if (*hexstr != '~') {
							delete[] hexstr;
						}
						format++; format++;  // Skip 'l' and 'x'
					}
					else if (*format != '.' && sys::util::isnum(*(format + 1))) {
						byte count_spec = *(format + 1) - '0';
						switch (*(format + 2)) {
						case 'w': {
							const wchar* str = va_arg(args, const wchar*);
							while (count_spec && pos < size - 1) {
								buffer[pos++] = (char)(*format);
								count_spec--;
							}

							while (*str && pos < size - 1 && count_spec) {
								buffer[pos++] = (char)(*str++);
							}
							format++; format++;
							break;
						}
						case 'f': {
							float val_ = va_arg(args, float);
							char* decstr = _gdecstr(val_, 0);  // Apply decimal precision
							if (!decstr) decstr = "~";
							char* itt = decstr;
							while (count_spec) {
								buffer[pos++] = '0';
								count_spec--;
							}
							while (*itt && pos < size - 1) {
								buffer[pos++] = (char)*itt++;
							}
							delete[] decstr;
							format++; format++;  // Skip 'f'
							break;
						}
						case 'X':
						case 'x': {
							uint64_t val_ = va_arg(args, uint64_t);
							char* hexstr = _ghexstr(val_, *(format + 2) == 'X', false);
							if (!hexstr) {
								hexstr = "~";
							}
							char* itt = hexstr;
							while (count_spec) {
								buffer[pos++] = *format;
								count_spec--;
							}
							while (*itt && pos < size - 1) {
								buffer[pos++] = (char)*itt++;
							}
							if (*hexstr != '~') {
								delete[] hexstr;
							}
							format++; format++;
						}
						default:
							if (pos < size - 1) buffer[pos++] = '%';
							if (pos < size - 1) buffer[pos++] = *format;
							gotsRemainingSpecifiers = true;
							break;
						}
					}
					else if (*format == '.' && sys::util::isnum(*(format + 1))) {
						byte count_spec = *(format + 1) - '0';
						switch (*(format + 2)) {
						case 'w': {
							const wchar* str = va_arg(args, const wchar*);
							while (*str && pos < size - 1 && count_spec) {
								buffer[pos++] = (char)(*str++);
								count_spec--;
							}
							format++; format++;
							break;
						}
						case 'f': {
							float val_ = va_arg(args, float);
							char* decstr = _gdecstr(val_, count_spec);  // Apply decimal precision
							if (!decstr) decstr = "~";
							char* itt = decstr;
							while (*itt && pos < size - 1) {
								buffer[pos++] = (char)*itt++;
							}
							delete[] decstr;
							format++; format++;  // Skip 'f'
							break;
						}
						case 'X':
						case 'x': {
							uint64_t val_ = va_arg(args, uint64_t);
							char* hexstr = _ghexstr(val_, *format == 'X', false);
							if (!hexstr) {
								hexstr = "~";
							}
							char* itt = hexstr;
							while (count_spec) {
								buffer[pos++] = '0';
								count_spec--;
							}
							while (*itt && pos < size - 1) {
								buffer[pos++] = (char)*itt++;
							}
							if (*hexstr != '~') {
								delete[] hexstr;
							}
							format++; format++;
						}
						default:
							if (pos < size - 1) buffer[pos++] = '%';
							if (pos < size - 1) buffer[pos++] = *format;
							gotsRemainingSpecifiers = true;
							break;
						}
					}
					else {
						switch (*format) {
						case 'b': {
							bool R = (bool)va_arg(args, int);
							const char* str = R ? "true" : "false";

							while (*str && pos < size - 1) {
								buffer[pos++] = (char)(*str++);
							}
							break;
						}
						case 'd': {
							int value = va_arg(args, int);
							wchar_t numBuffer[16];
							_itow(value, numBuffer, 10);  // Ensure base 10 for integer
							for (int i = 0; numBuffer[i] && pos < size - 1; ++i)
								buffer[pos++] = numBuffer[i];
							break;
						}
						case 'c': {
							char ch = (char)va_arg(args, int);
							if (pos < size - 1) buffer[pos++] = ch;
							break;
						}
						case 's': {
							const char* str = va_arg(args, const char*);
							while (*str && pos < size - 1)
								buffer[pos++] = (char)(*str++);
							break;
						}
						case 'S': {
							const char* str = va_arg(args, const char*);
							while (*str && pos < size - 1)
								buffer[pos++] = _sys_toupper((char)(*str++));
							break;
						}
						case 'f': {
							float val_ = va_arg(args, float);
							char* decstr = _gdecstr(val_, 0);  // Default precision
							if (!decstr) decstr = "~";
							char* itt = decstr;
							while (*itt && pos < size - 1) {
								buffer[pos++] = (char)*itt++;
							}
							delete[] decstr;
							break;
						}
						case 'x':
						case 'X': {
							uint64_t val_ = va_arg(args, uint64_t);
							char* R = _ghexstr(val_, *format == 'X', false);  // Handle 'X' vs 'x'
							if (R) {
								char* itt = R;
								while (*itt && pos < size - 1) {
									buffer[pos++] = (char)*itt++;
								}
								delete[] R;
							}
							break;
						}
						case '%': {
							if (pos < size - 1) buffer[pos++] = '%';  // escape character
							break;
						}
						default: {
							if (pos < size - 1) buffer[pos++] = '%';
							if (pos < size - 1) buffer[pos++] = *format;
							gotsRemainingSpecifiers = true;
							break;
						}
						}
					}
				}
				else {
					buffer[pos++] = *format;
				}
				++format;
			}

			va_end(args);

#if FALSE
			if (gotsRemainingSpecifiers) {
				char* alter = new char[size];
				// Handle additional system-specifiers
				sys::snprintf(alter, size, buffer, select...);
				sys::memcpy(buffer, alter, size);
				sys::memset(alter, 0, 0);
				delete[] alter;
			}
#endif
			buffer[pos] = '\0';
			return static_cast<int>(pos);
		}

	}
}
#include "formatter.inl"