#pragma once
#include "_ns.h"

#include "strlen.h"


_SYS_NS
template<class Char>
class basic_string_view {
	const Char* _pBegin = nullptr;
	const Char* _pEnd = nullptr;

public:
	static constexpr size_t npos = static_cast<size_t>(-1);

	basic_string_view()
	{
		_pBegin = nullptr;
		_pEnd = nullptr;
	}
	basic_string_view(const basic_string_view& other) :
		_pBegin(other._pBegin), _pEnd(other._pEnd)
	{
	}
	basic_string_view(basic_string_view&& other) : _pBegin(other._pBegin), _pEnd(other._pEnd)
	{
		other._pBegin = nullptr;
		other._pEnd = nullptr;
	}
	basic_string_view(const Char* str, size_t len)
		: _pBegin(str), _pEnd(str + len) {
	}
	template<size_t len>
	basic_string_view(const Char(&str)[len])
		: _pBegin(str), _pEnd(str + len) {
	}
	explicit basic_string_view(const Char* str)
		: _pBegin(str), _pEnd(str + sys::strlen(str)) {
	}


	size_t size() const { return static_cast<size_t>(_pEnd - _pBegin); }
	bool empty() const { return (_pBegin == _pEnd) || ((!_pBegin) && (!_pEnd)); }

	const Char* c_str() const { return this->_pBegin; }
	const Char* c_str() { return this->_pBegin; }

	const Char* begin() const { return this->_pBegin; }
	const Char* begin() { return this->_pBegin; }
	const Char* end() const { return this->_pEnd; }
	const Char* end() { return this->_pEnd; }
	void set(const Char* begin, const Char* end) {
		this->_pBegin = begin;
		this->_pEnd = end;
	}
	void remove_prefix(size_t n) { _pBegin += n; }
	void remove_suffix(size_t n) { _pEnd -= n; }


	basic_string_view substr(size_t pos, size_t count = npos) const {
		_sys_assert(pos <= size());
		size_t rlen = std::min(count, size() - pos);
		return basic_string_view(_pBegin + pos, rlen);
	}

	basic_string_view& operator=(const basic_string_view<Char>& other) {
		this->_pBegin = other._pBegin;
		this->_pEnd = other._pEnd;
		return *this;
	}

};
using string_view = basic_string_view<char>;
using wstring_view = basic_string_view<wchar_t>;

_SYS_ENS