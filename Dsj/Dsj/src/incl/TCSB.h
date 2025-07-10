#pragma once
#include "..\system\types.h"
/*  MIT License

Copyright (c) 2016 Dmitry Romanov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */


#pragma diag_suppress  186

#define TCSB_fracmask  0x000FFFFFFFFFFFFFU
#define TCSB_expmask   0x7FF0000000000000U
#define TCSB_hiddenbit 0x0010000000000000U
#define TCSB_signmask  0x8000000000000000U
#define TCSB_expbias   (1023 + 52)
#define TCSB_tens_len (20)

#define TCDB_absv(n) ((n) < 0 ? -(n) : (n))
#define TCSB_minv(a, b) ((a) < (b) ? (a) : (b))


#define TCSB_npowers     87
#define TCSB_steppowers  8
#define TCSB_firstpower -348 /* 10 ^ -348 */

#define TCSB_expmax     -32
#define TCSB_expmin     -60

 // Allows to switch on/off floating point support.
 // Using floating point operations is ON by default
#define TCSB_USE_FP 1




typedef struct TCSB_Fp {
	uint64_t frac;
	int exp;
} TCSB_Fp;


class CStringBuilder {

	CStringBuilder(const CStringBuilder&) = delete;
	CStringBuilder& operator=(const CStringBuilder&) = delete;

private:
	char* _buffer;
	char _separator = ' ';
	std::size_t _bufferSize;
	std::size_t _cursor;
	bool _isOverflow;

	void set_string_end();

	/* reverse:  reverse string s in place */
	void reverse(char s[]);

	/* raisecase:  case string s in place */
	void raisecase(char s[]);

public:

	/**
	 \rst
	 Constructs a :class:`fmt::BasicArrayWriter` object for *array* of the
	 given size.
	 \endrst
	 */
	CStringBuilder(char* buffer, std::size_t bufferSize);

	/**
	 \rst
	 Constructs a :class:`fmt::BasicArrayWriter` object for *array* of the
	 size known at compile time.
	 \endrst
	 */
	template <std::size_t SIZE>
	explicit CStringBuilder(char(&array)[SIZE]);

	template<int SIZE>
	CStringBuilder& operator =(char(&data)[SIZE]);

	/** K&R int to string conversion */
	template <typename IntType>
	size_t add_integer(IntType n);


	/** returns current size of the _buffer */
	size_t buffer_size(void);


	/** The actual size of the resulting string */
	size_t size(void);


	/** returns pointer to a char[] buffer */
	char* cstr();


	/** Append by C string */
	template<class CharConstPtr>
	size_t add(CharConstPtr array, std::size_t size);

	/// add const string
	template <std::size_t SIZE>
	size_t add(const char(&array)[SIZE]);

	/// Adds char to the buffer
	size_t add(char value);
	/// Adds bool literal to the buffer
	size_t addb(bool value);
	/// Adds hexadecimal literal to the buffer
	size_t addhex(uint32_t value);
	/// Adds hexadecimal literal to the buffer
	size_t addhex(void* value);
	size_t add(bool value);
	size_t add(int8_t value);
	size_t add(uint8_t value);
	size_t add(int16_t value);
	size_t add(uint16_t value);
	size_t add(int32_t value);
	size_t add(uint32_t value);
	size_t add(int64_t value);
	size_t add(uint64_t value);


	/*----------------- FLOATING POINT -----------------------*/
	/* The next code is taken from fpconv library https://github.com/night-shift/fpconv
	 * fpconv is distributed by MIT license as this library
	 **/

private:

	static const TCSB_Fp& powers_ten(uint8_t index);
	static TCSB_Fp find_cachedpow10(int exp, int* k);
	static const uint64_t* tens();
	static inline uint64_t get_dbits(double d);
	TCSB_Fp build_fp(double d);

	void normalize(TCSB_Fp* fp);

	void get_normalized_boundaries(TCSB_Fp* fp, TCSB_Fp* lower, TCSB_Fp* upper);

	TCSB_Fp multiply(TCSB_Fp* a, TCSB_Fp* b);

	void round_digit(char* digits, int ndigits, uint64_t delta, uint64_t rem, uint64_t kappa, uint64_t frac);


	int generate_digits(TCSB_Fp* fp, TCSB_Fp* upper, TCSB_Fp* lower, char* digits, int* K);
	int grisu2(double d, char* digits, int* K);

	int emit_digits(char* digits, int ndigits, char* dest, int K, bool neg);
	int filter_special(double fp, char* dest);

	size_t fpconv_dtoa(double d, char dest[24]);
public:

	size_t addf(double value);


};

class CharPointerHelper {
public:
	CharPointerHelper(const char* buffer);

	const char* buffer()const;
	CharPointerHelper& operator= (const char* s);
private:
	const char* _buffer;
};


/// add const string
template <std::size_t SIZE>
CStringBuilder& operator<<(CStringBuilder& sb, const char(&array)[SIZE]);
CStringBuilder& operator<<(CStringBuilder& sb, CharPointerHelper value);
CStringBuilder& operator<<(CStringBuilder& sb, char value);
CStringBuilder& operator<<(CStringBuilder& sb, bool value);
CStringBuilder& operator<<(CStringBuilder& sb, int8_t value);
CStringBuilder& operator<<(CStringBuilder& sb, uint8_t value);
CStringBuilder& operator<<(CStringBuilder& sb, int16_t value);
CStringBuilder& operator<<(CStringBuilder& sb, uint16_t value);
CStringBuilder& operator<<(CStringBuilder& sb, int32_t value);
CStringBuilder& operator<<(CStringBuilder& sb, uint32_t value);
CStringBuilder& operator<<(CStringBuilder& sb, int64_t value);
CStringBuilder& operator<<(CStringBuilder& sb, uint64_t value);


typedef CharPointerHelper from_pchar;


#ifdef TCSB_USE_SIZE_OVERLOADS
CStringBuilder& operator<<(CStringBuilder& sb, size_t value) { sb.add_integer<size_t>(value); return sb; }   /// Add uint64_t to string and adds to the buffer
#endif

CStringBuilder& operator<<(CStringBuilder& sb, const double& value);

