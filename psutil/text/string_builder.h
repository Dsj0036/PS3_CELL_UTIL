#pragma once
#pragma once
#ifndef _PS3_STRING_STREAM_
#define _PS3_STRING_STREAM_
#include <psutil\xtypes.h>
#include <psutil\vector.h>
#include <string>
_SYS_NS

class string_builder {
	sys::vector<char> buff;
public:
	string_builder() : buff() {}
	string_builder(const string_builder& str) : buff(str.buff) {}
	string_builder(const char* buffer, size_t count) {

		buff.reserve(count);
		buff.push_range(buffer, count);
	}
	inline static string_builder empty() {
		return {};
	}
	string_builder& operator <<(const char* str);
	string_builder& operator <<(const wchar* str);
	string_builder& operator <<(std::string const& txt);

	string_builder& operator <<(char c);
	template<typename ...T>
	string_builder& print(const char* format, T...args);
	template<typename N>
	void addNumber(const N& r);
	template<typename N>
	void addNumber(const char* f, const N& r);
	void pop_back();
	void push_back(char c);
	std::string tostring()const;
	size_t append(const char* buffer, size_t count = 0);
	const char* c_str() const;
	void clear();
	int length()const;
	int capacity() const;
	string_builder& reserve(size_t c);
	size_t indexOf(const std::string& str, size_t srcOffset = 0) const;
	int cpy(char* dst, int srcOffset, int dstLength);
	string_builder substream(int srcOffset = 0, int dstLength = 0) const;
	int cpy(char* buffer, size_t maxSize);
	inline string_builder& crlf();
	inline string_builder& pad(char c = ' ', byte count = 1);
	inline string_builder& tab();
	inline string_builder& removeAt(size_t index);
	inline string_builder& insertAt(size_t index, char c);
	inline char elementAt(size_t index)const;
	inline int trim();
	inline int trim(const vector<char>& chars);
	string_builder& operator<<(int32_t num);

	string_builder& operator<<(uint32_t num);
	string_builder& operator<<(int64_t num);
	string_builder& operator<<(uint64_t num);
	string_builder& operator<<(float num);
	string_builder& operator<<(double num);
	char& back();
	const char& back() const;
	void terminate();

};
_SYS_ENS
#endif
