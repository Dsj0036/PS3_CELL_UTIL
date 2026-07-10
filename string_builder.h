#pragma once
#include "_ns.h"
#include "list.h"
#include "lwstring.h"
#include "string_view.h"
#include "io\text_reader.h"
#include "io\stream.h"
#include "array_param.h"
_SYS_NS

template<class Char>
class lightweight_string_builder {
	sys::list<Char> _buffer;

public:
	using lwstring_type = sys::basic_lightweight_string<Char>;

	lightweight_string_builder() {
		this->_buffer.reserve(128);
	}
	lightweight_string_builder(const lightweight_string_builder&) = delete;
	lightweight_string_builder& operator==(const lightweight_string_builder&) = delete;



	lightweight_string_builder& append(array_param<Char>);
	lightweight_string_builder& append(Char c);
	lightweight_string_builder& append(const lwstring_type& str);
	lightweight_string_builder& append(const Char* str, size_t count);
	lightweight_string_builder& append(const Char* str);
	lightweight_string_builder& appendf(const Char* str, ...);

	lightweight_string_builder& terminate();

	lightweight_string_builder& crlf();
	lightweight_string_builder& pad(Char ch, int8_t count);

	lightweight_string_builder& clear();

	// [appendv] Functions that write type value representations. Core StringBuilder.

	lightweight_string_builder& appendv(bool);
	lightweight_string_builder& appendv(int32_t);
	lightweight_string_builder& appendv(double);



	void copy_to(sys::stream*);

	void copy_to(char* out, size_t out_buffer_size);
	void copy_to(char* out, size_t srcOffset, size_t count);

	size_t capacity()const;
	size_t length()const;
	void reserve(size_t capacity);
	const Char* dta() const;
	basic_string_view<Char> view() const;

	lwstring_type to_string() const;

};
using string_builder = lightweight_string_builder<char>;
using wstring_builder = lightweight_string_builder<wchar_t>;
_SYS_ENS
