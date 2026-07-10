#pragma once
#include "..\_ns.h"
#include "..\types.h"
#include <stdint.h>
#include "..\exception.h"
#include "..\throw.h"
_SYS_NS

class stream {
protected: 
	stream() = default;
	
public:
	virtual uint64_t write(const void* data, size_t count) {
		sys::throw_pure_virtual_usage();
		return 0;
	}
	virtual bool is_opened() const {
		return true;
	}
	
	virtual uchar read() {
		sys::throw_pure_virtual_usage();
		return 0;

	}

	virtual uint64_t read(void* buffer, size_t count) {
		sys::throw_pure_virtual_usage();
		return 0;
	}

	virtual uint64_t seek(int64_t offset, int origin) {
		sys::throw_pure_virtual_usage();
		return 0;
	}

	virtual uint64_t get_length() const {
		sys::throw_pure_virtual_usage();
		return 0;
	}
	virtual uchar* dta() {
		sys::throw_pure_virtual_usage();
		return 0;

	}
	const uchar* dta() const {
		return ((stream*)this)->dta();
	}

	virtual uint8_t* cur() {
		sys::throw_pure_virtual_usage();
		return 0;
	}
	const uint8_t* cur() const {
		return ((stream*)this)->cur();
	}
	virtual uint64_t get_position() const {
		sys::throw_pure_virtual_usage();
		return 0;

	}

	inline bool is_eof() const {
		return get_position() >= get_length();
	}
protected:
	virtual ~stream() = default;
};
_SYS_ENS