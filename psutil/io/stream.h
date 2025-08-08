#pragma once
#include <types.h>
_SYS_NS
class stream {
	

protected:
	stream(const stream& ) = default;
	stream(stream& ) = default;

public:
	stream() = default;

	virtual bool readable()const;
	virtual bool writable()const;
	virtual int close();
	virtual void flush();
	virtual int copyTo(stream*);

	virtual uint64_t length() const;
	virtual uint64_t position() const;
	virtual uint64_t seek(uint64_t p, int);

	virtual uint64_t write(const uint8_t*, uint16_t);
	virtual uint64_t write(uint8_t);

	virtual uint64_t read(uint8_t*, uint64_t);
	virtual uint8_t read();

	virtual ~stream() = default;
};
_SYS_ENS