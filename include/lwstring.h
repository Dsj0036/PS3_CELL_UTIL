/**
 * @file lwstring.h
 * @brief Lightweight dynamically allocated string container.
 *
 * Provides a minimal heap-allocated string implementation intended for
 * low-overhead runtime usage and custom allocator integration.
 *
 * Features:
 * - Move semantics support
 * - Explicit ownership
 * - Lightweight storage
 * - Compatible with basic_string_view
 * - Manual CRT buffer adoption
 *
 * @note
 * This class is not intended to be STL-compatible.
 *
 * @warning
 * Internal allocation uses `_sys_memalign()` and `_sys_free()`.
 */

#pragma once

#ifndef SYS_LWSTRING
#define SYS_LWSTRING

#include "_ns.h"

#include "assert.h"
#include "strlen.h"
#include "string_view.h"
#include "exception.h"
#include "hash_code.h"
#include "memory.h"
#include "throw.h"
#include "unexpect.h"

_SYS_NS

namespace comparison {
	static constexpr int32_t EXACT = 0;
	static constexpr int32_t CASE_INSENSITIVE = 1;
}

/**
 * @brief Global empty string fallback.
 */
	extern const char* EMPTY_STRING;

/**
 * @brief Lightweight dynamically allocated string.
 *
 * Stores a heap-allocated null-terminated string using custom memory
 * allocation functions.
 *
 * @tparam Char Character type.
 */
template<class Char>
class basic_lightweight_string {
	Char* _Buffer;

	/**
	 * @brief Clears and releases the current internal buffer.
	 */
	void _clrprev() {
		if (_Buffer)
			_sys_free(_Buffer);

		_Buffer = nullptr;
	}

	/**
	 * @brief Replaces the current value.
	 *
	 * Allocates a new internal buffer and copies the specified string.
	 *
	 * @param str Source string.
	 * @param length String length.
	 */
	void _setVal(const Char* str, int length) {
		_clrprev();

		if (length == 0)
			return;

		size_t sz = (length + 1) * sizeof(Char);

		_Buffer = (Char*)_sys_memalign(4, sz);

		__expect(_Buffer != nullptr);

		_sys_memcpy(_Buffer, str, length * sizeof(Char));

		_Buffer[length] = L'\0';
	}

	/**
	 * @brief Initializes the internal value without clearing previous memory.
	 *
	 * @param str Source string.
	 * @param length String length.
	 */
	void _initVal(const Char* str, int length) {
		if (length == 0)
			return;

		size_t sz = (length + 1) * sizeof(Char);

		_Buffer = (Char*)_sys_memalign(4, sz);

		__expect(_Buffer != nullptr);

		_sys_memcpy(_Buffer, str, length * sizeof(Char));

		_Buffer[length] = L'\0';
	}

public:

	/**
	 * @brief Constructs an empty lightweight string.
	 */
	basic_lightweight_string() {
		_Buffer = nullptr;
	}

	/**
	 * @brief Constructs a string from a null-terminated buffer.
	 *
	 * Inline literals must now be explicitly constructed.
	 *
	 * @param text Input string.
	 */
	explicit basic_lightweight_string(const Char* text) {
		this->_Buffer = nullptr;

		__expect(text != nullptr);

		this->assign(text);
	}

	/**
	 * @brief Move constructor.
	 *
	 * Transfers ownership from another string instance.
	 *
	 * @param text Source instance.
	 */
	basic_lightweight_string(basic_lightweight_string&& text) {
		this->_Buffer = text._Buffer;
		text._Buffer = nullptr;
	}

	/**
	 * @brief Copy constructor.
	 *
	 * Performs deep-copy allocation.
	 *
	 * @param other Source string.
	 */
	basic_lightweight_string(const basic_lightweight_string& other) {
		if (other.got()) {
			_initVal(other._Buffer, other.length());
		}
		else {
			this->_Buffer = nullptr;
		}
	}

	/**
	 * @brief Move assignment operator.
	 *
	 * @param other Source instance.
	 * @return Reference to this object.
	 */
	basic_lightweight_string& operator=(basic_lightweight_string&& other) noexcept
	{
		if (this != &other)
		{
			_clrprev();

			_Buffer = other._Buffer;

			other._Buffer = nullptr;
		}

		return *this;
	}

	/**
	 * @brief Copy assignment operator.
	 *
	 * Performs deep-copy allocation.
	 *
	 * @param other Source string.
	 * @return Reference to this object.
	 */
	basic_lightweight_string& operator=(const basic_lightweight_string& other) {
		if (this != &other) {
			if (other.got()) {
				_setVal(other._Buffer, other.length());
			}
			else {
				_clrprev();
			}
		}

		return *this;
	}

	/**
	 * @brief Compares against a C-style string.
	 *
	 * @param inl Null-terminated string.
	 * @return True if equal.
	 */
	bool operator==(const Char* inl) const {
		return eq(inl);
	}

	/**
	 * @brief Compares against a C-style string.
	 *
	 * @param inl Null-terminated string.
	 * @return True if not equal.
	 */
	bool operator != (const Char* inl) const {
		return !this->operator==(inl);
	}

	/**
	 * @brief Performs string equality comparison.
	 *
	 * @param inl Input string.
	 * @return True if equal.
	 */
	bool eq(const Char* inl) const {
		if (inl == NULL)
			return 0;

		if (this->_Buffer == NULL && inl == NULL)
			return 0;

		size_t otherlength = sys::strlen(inl);
		size_t mylen = this->length();

		if (otherlength != mylen)
			return false;

		return !_sys_memcmp(this->c_str(), inl, otherlength);
	}

	/**
	 * @brief Compares two lightweight strings.
	 *
	 * @param other Other string instance.
	 * @return True if equal.
	 */
	bool operator ==(const basic_lightweight_string& other)const {
		if (this == &other)
			return true;

		if (this->got() != other.got())
			return false;

		if (this->got()) {
			size_t otherlength = other.length();
			size_t mylen = this->length();

			if (otherlength != mylen)
				return false;

			return !_sys_memcmp(this->c_str(), other.c_str(), otherlength);
		}

		return false;
	}

	/**
	 * @brief Compares two lightweight strings.
	 *
	 * @param other Other string instance.
	 * @return True if not equal.
	 */
	inline bool operator != (const basic_lightweight_string& other)const {
		return !((*this) == other);
	}

	/**
	 * @brief Checks whether the string is empty.
	 *
	 * @return True if empty.
	 */
	bool empty() const {
		return !got() || length() == 0;
	}

	/**
	 * @brief Checks whether a valid internal buffer exists.
	 *
	 * @return True if allocated.
	 */
	bool got() const {
		return _Buffer != nullptr;
	}

	/**
	 * @brief Assigns from a null-terminated string.
	 *
	 * @param buffer Source string.
	 * @return Assigned length.
	 */
	int assign(const Char* buffer);

	/**
	 * @brief Assigns from another lightweight string.
	 *
	 * @param buffer Source string.
	 * @return Assigned length.
	 */
	int assign(const basic_lightweight_string<Char>& buffer) {

		if (this == &buffer)
			return -1;

		bool eq = false;

		if (got() && buffer.length() > 0)
			eq = !_sys_memcmp(this->c_str(), buffer.c_str(), buffer.length());

		if (eq || (!buffer.length())) {
			return 0;
		}

		this->_setVal(buffer.c_str(), buffer.length());

		return buffer.length();
	}

	/**
	 * @brief Assigns from a string view.
	 *
	 * @param buffer Source view.
	 * @return Assigned length.
	 */
	int assign(const basic_string_view<Char>& buffer) {
		return assign(buffer.c_str());
	}

	/**
	 * @brief Assigns from a raw buffer with explicit size.
	 *
	 * @param src Source buffer.
	 * @param buffSize Buffer size.
	 * @return Assigned size.
	 */
	int assign(const Char* src, size_t buffSize) {
		if (!src) {
			this->_clrprev();
			return 0;
		}

		this->_setVal(src, buffSize);

		return buffSize;
	}

	/**
	 * @brief Clears the string contents.
	 */
	void clear() {
		this->_clrprev();
	}

	/**
	 * @brief Checks whether the internal pointer is non-null.
	 *
	 * @return True if valid.
	 */
	bool not_null() const {
		return _Buffer != nullptr;
	}

	/**
	 * @brief Returns string length.
	 *
	 * @return String length excluding null terminator.
	 */
	int length() const;

	/**
	 * @brief Creates a lightweight string instance.
	 *
	 * @param in Input string.
	 * @return New lightweight string.
	 */
	static inline basic_lightweight_string nw(const Char* in) {
		basic_lightweight_string lw = {};

		lw.assign(in);

		return lw;
	}

	/**
	 * @brief Adopts an external CRT-allocated buffer.
	 *
	 * Ownership is transferred directly without copying.
	 *
	 * @warning
	 * The provided buffer must be compatible with `_sys_free()`.
	 *
	 * @param other External buffer.
	 */
	inline void _unsafe_assign_crt(Char* other) {
		this->clear();
		this->_Buffer = other;
	}

	/**
	 * @brief Returns the internal null-terminated buffer.
	 *
	 * @return Internal string buffer.
	 */
	const Char* c_str() const;

	/**
	 * @brief Destructor.
	 */
	~basic_lightweight_string() {
		_clrprev();
	}

	/**
	 * @brief Creates a lightweight string view.
	 *
	 * @return String view instance.
	 */
	basic_string_view<Char> view() const {
		return basic_string_view<Char>(this->c_str(), this->length());
	}
};

/**
 * @brief UTF-8 lightweight string.
 */
using lwstring = basic_lightweight_string<char>;

/**
 * @brief Wide-character lightweight string.
 */
using lwwstring = basic_lightweight_string<wchar_t>;

template<>
int basic_lightweight_string<wchar_t>::length() const;

template<>
int basic_lightweight_string<char>::length() const;

template<>
int basic_lightweight_string<char>::assign(const char* p);

template<>
const char* basic_lightweight_string<char>::c_str() const;

/**
 * @brief Computes a hash code from a lightweight string.
 *
 * @param str Input string.
 * @return Hash value.
 */
size_t get_hash(const sys::lwstring& str);

_SYS_ENS

#endif