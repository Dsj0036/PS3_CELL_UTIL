#pragma once
#include "System.h"
#include "tcsb.h"
namespace sys {

	static char* _gdecstr(double val, int decimals = 4) {
		char* r = new char[40] {0};
		auto bs = tcsb::CStringBuilder(r, 40);
		bs.addf(val);
		if (decimals > 0) { // assume 0 indicates ignoring.
			char* dot_pos = std::strchr(r, '.');
			if (dot_pos) {
				int max_len = dot_pos - r + decimals + 1;
				if (max_len < std::strlen(r)) {
					r[max_len] = '\0';
				}
			}
		}


		return r;
	}
	static char* _ghexstr(uint64_t anyh, bool uppercase, bool i64 = false) {
		char* r = new char[32] {0};
		const char* format = i64 ? (uppercase ? "%llX" : "%llx") : (uppercase ? "%lX" : "%lx");
		sys::snprintf(r, 32, format, anyh);
		return r;
	}


	static void _itow(int value, wchar_t* out, int max_len) {
		int i = max_len - 2;
		bool isNegative = value < 0;
		if (isNegative) value = -value;

		out[i + 1] = L'\0';

		do {
			out[i--] = (wchar_t)(L'0' + (value % 10));
			value /= 10;
		} while (value && i >= 0);

		if (isNegative && i >= 0) {
			out[i--] = L'-';
		}

		for (int j = i + 1, k = 0; out[j]; ++j, ++k)
			out[k] = out[j];

		out[max_len - 1] = L'\0';
	}

	static inline bool _is_it(const wchar* data, const wchar* comparing) {
		return std::wcsncmp(comparing, data, std::wcslen(comparing)) == 0;
	}

	static inline bool _is_it(const char* data, const char* comparing) {
		return safest_compare(data, comparing);
	}
	static inline bool is_alnum(int c) {
		return is_char_integer(c) || is_char_letter(c);
	}

	template<typename ...va>
	static int wsnprintf_(wchar_t* buffer, size_t size, const wchar_t* format, va... select) {
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
				else if (*format == L'.' && is_char_integer(*(format + 1))) {
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

	template<typename ...va>
	static int snprintf_(char* buffer, size_t size, const char* format, va...select) {
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
				else if (*format != '.' && is_char_integer(*(format + 1))) {
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
				else if (*format == '.' && is_char_integer(*(format + 1))) {
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
						char* str = R ? "true" : "false";
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

		if (gotsRemainingSpecifiers) {
			char* alter = new char[size];
			// Handle additional system-specifiers
			sys::snprintf(alter, size, buffer, select...);
			sys::memcpy(buffer, alter, size);
			sys::memset(alter, 0, 0);
			delete[] alter;
		}

		buffer[pos] = '\0';
		return static_cast<int>(pos);
	}
	template<typename ...va>
	static int vasnprintf_(char* buffer, size_t size, const char* format, va_list list, bool& gotsRemainingSpecifiers) {
		if (!buffer || size == 0) return -1;

		size_t pos = 0;
		va_start(list, format);

		while (*format && pos < size - 1) {
			if (*format == '%') {
				format++;  // Move to the specifier

				if (_is_it(format, "ld")) {
					double val_ = va_arg(list, double);
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
					uint64_t val_ = va_arg(list, uint64_t);
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
				else if (*format != '.' && is_char_integer(*(format + 1))) {
					byte count_spec = *(format + 1) - '0';
					switch (*(format + 2)) {
					case 'w': {
						const wchar* str = va_arg(list, const wchar*);
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
						double val_ = va_arg(list, double);
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
						uint64_t val_ = va_arg(list, uint64_t);
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
				else if (*format == '.' && is_char_integer(*(format + 1))) {
					byte count_spec = *(format + 1) - '0';
					switch (*(format + 2)) {
					case 'w': {
						const wchar* str = va_arg(list, const wchar*);
						while (*str && pos < size - 1 && count_spec) {
							buffer[pos++] = (char)(*str++);
							count_spec--;
						}
						format++; format++;
						break;
					}
					case 'f': {
						double val_ = va_arg(list, double);
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
						uint64_t val_ = va_arg(list, uint64_t);
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
					case 'd': {
						int value = va_arg(list, int);
						wchar_t numBuffer[16];
						_itow(value, numBuffer, 10);  // Ensure base 10 for integer
						for (int i = 0; numBuffer[i] && pos < size - 1; ++i)
							buffer[pos++] = numBuffer[i];
						break;
					}
					case 'c': {
						char ch = (char)va_arg(list, int);
						if (pos < size - 1) buffer[pos++] = ch;
						break;
					}
					case 's': {
						const char* str = va_arg(list, const char*);
						while (*str && pos < size - 1)
							buffer[pos++] = (char)(*str++);
						break;
					}
					case 'S': {
						const char* str = va_arg(list, const char*);
						while (*str && pos < size - 1)
							buffer[pos++] = _sys_toupper((char)(*str++));
						break;
					}
					case 'f': {
						double val_ = va_arg(list, double);
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
						uint64_t val_ = va_arg(list, uint64_t);
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
		buffer[pos] = '\0';
		return static_cast<int>(pos);
	}
	template<typename ...va>
	static std::string format(const char* format, va...select) {
		char buffer[1024]{ 0 };
		sys::snprintf_(buffer, 1024, format, select...);
		return buffer;
	}
	template<typename ...va>
	static std::wstring format(const wchar* format, va...select) {
		wchar buffer[1024]{ 0 };
		sys::wsnprintf_(buffer, 1024, format, select...);
		return buffer;
	}

}