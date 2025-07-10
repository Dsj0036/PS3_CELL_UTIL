#pragma once
#include "include\vector.h"
#include "System.h"
class string_stream  {
	vector<char> buff;
public:
	string_stream() : buff() {}
	string_stream(const string_stream& str) : buff(str.buff) {}
	string_stream(const char* buffer, size_t count) {

		buff.reserve(count);
		buff.push_range(buffer, count);
	}
	static string_stream empty() {
		return string_stream();
	}


	string_stream& operator <<(const char* str) {
		while (*str) {
			buff.push_back(*str);
			str++;
		}
		return *this;
	}
	string_stream& operator <<(const wchar* str) {
		while (*str) {
			buff.push_back(*str);
			str++;
		}
		return *this;
	}
	string_stream& operator <<(std::string const& txt) {

		buff.f_inject_at(txt.size() - 1, txt.c_str(), txt.length());
		return *this;
	}

	string_stream& operator <<(char c) {
		buff.push_back(c);
		return *this;
	}
	template<typename ...T>
	string_stream& print(const char* format, T...args) {
		char buffer[500]{ 0 };
		sys::snprintf(buffer, 500, format, args...);
		buff.push_range(buffer);
		return *this;
	}
	template<typename N>
	void addNumber(const N& r) {
		char buffer[32]{ 0 }; {
			sys::snprintf(buffer, 32, "%i", r);
		}
		(*this) << buffer;
	}
	template<typename N>
	void addNumber(const char* f, const N& r) {
		char buffer[64]{ 0 }; {
			sys::snprintf(buffer, 32, f, r);
		}
		(*this) << buffer;
	}
	void pop_back() {
		buff.pop_back();
	}
	void push_back(char c) {
		buff.push_back(c);
	}
	std::string tostring()const {
		return std::string(buff.data(), buff.size());
	}
	size_t append(const char* buffer, size_t count = 0) {
		size_t length = count == 0 ? sys::strlen(buffer) : count;
		forIndexIn(length) {
			this->push_back(buffer[i]);
		}
		return length;
	}
	const char* c_str() const {
		return buff.data();
	}
	void clear() {
		this->buff.clear();
	}
	int length()const {
		return this->buff.size();
	}
	int capacity() const {
		return this->buff.capacity();
	}
	string_stream& reserve(size_t c) {
		this->buff.reserve(c);
		return *this;
	}
	size_t indexOf(const std::string& str, size_t srcOffset = 0) const {
		size_t index = srcOffset > this->length() ? 0 : srcOffset;
		while (index < this->length()) {
			
			if (sys::strncmp(c_str() + index, str.c_str(), str.length()) == 0) {
				return index;
			}
			++index;
		}
		return -1ull;

	}
	int cpy(char* dst, int srcOffset, int dstLength) {

		sys::memset(dst, 0, dstLength);

		forIndexIn(this->length()) {
			dst[i] = this->buff[i + srcOffset];
		}
		return dstLength;
	}
	string_stream substream(int srcOffset = 0, int dstLength = 0) const {
		if (dstLength == 0) {
			dstLength = this->length();
		}
		char* buff = new char[dstLength + 1];
		sys::strncpy(buff, this->c_str() + srcOffset, dstLength + 1);
		string_stream result(buff, dstLength + 1);
		sys::memset(buff, 0, dstLength + 1);
		delete[] buff;
		return result;
	}

	int cpy(char* buffer, size_t maxSize) {
		sys::memset(buffer, 0, maxSize);
		size_t len = MIN(maxSize - 1, this->buff.size());
		forIndexIn(len) {
			buffer[i] = this->buff[i];
		}
		return sys::strlen(buffer);
	}
	inline string_stream& crlf() {
		this->buff.push_back('\r');
		this->buff.push_back('\n');
		return  *this;
	}
	inline string_stream& pad(char c = ' ', byte count = 1) {
		while (count > 0) {
			this->buff.push_back(c);
			count--;
		}
		return  *this;
	}
	inline string_stream& tab() { return operator<<('\t'); }
	inline string_stream& removeAt(size_t index) {
		if (index < this->length()) {
			this->buff.remove_at(index);
		}
		return *this;
	}
	inline string_stream& insertAt(size_t index, char c) {
		if (index < this->length()) {
			this->buff.insert(index, c);
		}
		return *this;
	}
	inline char elementAt(size_t index)const {
		if (index >= this->length()) {
			return 0;
		}
		return this->buff[index];
	}
	inline int trim() {
		int count = 0;
		forIndexIn(this->length()) {
			char r = elementAt(i);
			if (r == ' ' || (r > 1 && r < 20)) {
				removeAt(i);
				i--;
				count++;
			}
		}
		return count;
	}
	inline int trim(const vector<char>& chars) {
		int count = 0;
		forIndexIn(this->length()) {
			if (chars.contains(elementAt(i))) {
				removeAt(i);
				i--;
				count++;
			}
		}
		return count;
	}
	string_stream& operator<<(int32_t num) {
		char buffer[32]{ 0 };
		sys::snprintf(buffer, sizeof(buffer), "%d", num);
		return (*this) << buffer;
	}

	string_stream& operator<<(uint32_t num) {
		char buffer[32]{ 0 };
		sys::snprintf(buffer, sizeof(buffer), "%u", num);
		return (*this) << buffer;
	}

	string_stream& operator<<(int64_t num) {
		char buffer[32]{ 0 };
		sys::snprintf(buffer, sizeof(buffer), "%lld", num);
		return (*this) << buffer;
	}

	string_stream& operator<<(uint64_t num) {
		char buffer[32]{ 0 };
		sys::snprintf(buffer, sizeof(buffer), "%llu", num);
		return (*this) << buffer;
	}

	string_stream& operator<<(float num) {
		char buffer[32]{ 0 };
		sys::snprintf(buffer, sizeof(buffer), "%.6f", num); // 6 decimales por defecto
		return (*this) << buffer;
	}

	string_stream& operator<<(double num) {
		char buffer[32]{ 0 };
		sys::snprintf(buffer, sizeof(buffer), "%.6lf", num);
		return (*this) << buffer;
	}
	char& back() {
		if (this->buff.size() == 0) {
			return  this->buff[0];
		}
		return this->buff[this->buff.size() - 1];
	}
	const char& back() const {
		if (this->buff.size() == 0) {
			return  this->buff[0];
		}
		return this->buff[this->buff.size() - 1];
	}
	void terminate() {
		int R = this->buff.size();
		if (this->buff[R > 0 ? R - 1 : 0] != '\0') {
			this->buff.push_back(0);
		}
	}

};