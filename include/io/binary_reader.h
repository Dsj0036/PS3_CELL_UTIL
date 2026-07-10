#pragma once
#include "stream.h"
#include "..\exception.h"
#include "..\throw.h"
#include "..\lwstring.h"
#include "..\buffer.h"
_SYS_NS

static constexpr int32_t BINARY_LITTLE_ENDIAN = 1 << 2;
class binary_reader {
	sys::stream* _stream{ NULL };
	int flags;
public:

	binary_reader(sys::stream* stream) : _stream(stream), flags(0) {}
	bool opened()const;

	sys::buffer read_buffer(size_t length);


	uint8_t read8();
	uint16_t read16();
	uint32_t read32();
	uint64_t read64();

	bool read_str(sys::lwstring* output);
	bool read_wstr(sys::lwwstring* output);

	double read_double();
	float read_float();

	uint8_t peek8();
	uint16_t peek16();
	uint32_t peek32();
	uint64_t peek64();
	double peek_double();
	float peek_float();

	size_t read_cpy(uint8_t* out, size_t count);

	inline uint32_t pos() const {
		unexpect(this->_stream == NULL);


		if (!stream()->is_opened()) return -1u;

		return stream()->get_position();
	}
	inline uint32_t length() const {
		unexpect(this->_stream == NULL);
		if (!stream()->is_opened()) return -1u;
		return stream()->get_length();
	}
	inline int64_t remaining() const {
		return (int64_t)length() - pos();
	}

	const uint8_t* cur() const;
	uint8_t* cur();

	const uint8_t* dta() const;
	uint8_t* dta();

	binary_reader& set_little_endian(bool is_little);
	inline bool is_little_endian() const {
		return this->flags & BINARY_LITTLE_ENDIAN;
	}

	inline const sys::stream* stream() const {
		return _stream;
	}
	inline sys::stream* stream() {
		return _stream;
	}

	void _unsafe_assign(binary_reader * other) {
		this->_stream = other->_stream;
		this->flags = other->flags;
	}

	bool is_eof()const;

};

_SYS_ENS

