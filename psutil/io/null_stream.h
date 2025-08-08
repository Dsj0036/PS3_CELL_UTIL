#pragma once
#include <psutil\ns.h>
#include "stream.h"
_SYS_NS
class null_stream : public stream  {
public:

protected:

public:
	null_stream(const null_stream&) {}
	null_stream(null_stream&) {}

	virtual bool readable()const;
	virtual bool writable()const;
	int close()override;
	void flush()override;
	int copyTo(stream*)override;
	uint64_t length()const override;
	uint64_t position()const override;
	uint64_t seek(uint64_t, int) override;
	uint64_t write(const uint8_t*, uint16_t)override;
	uint64_t write(uint8_t)override;

	virtual uint64_t read(uint8_t*, uint64_t)override;
	virtual uint8_t read()override;
};
_SYS_ENS