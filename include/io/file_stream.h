#pragma once
#include "..\_ns.h"
#include "stream.h"

#include "..\algorithm.h"
#include <cell/cell_fs.h>
_SYS_NS

static constexpr int fs_open_readonly = CELL_FS_O_RDONLY;
static constexpr int fs_open_append = CELL_FS_O_APPEND;
static constexpr int fs_open_create = CELL_FS_O_CREAT;
static constexpr int fs_open_readwrite = CELL_FS_O_RDWR;
static constexpr int fs_open_trunc = CELL_FS_O_TRUNC;
static constexpr int fs_open_write_only = CELL_FS_O_WRONLY;

class file_stream : public stream{
	int _handle{0};
	int _flags{0};

protected: 
	file_stream() = default;
public: 
	file_stream(int handle, int flags) : _handle(handle), _flags(flags) {
		
	}
	bool can_read()const {
		return (_flags & fs_open_readwrite) &&  (!(_flags & fs_open_write_only));
	}
	bool can_write() const{
		return (_flags & fs_open_readwrite) || (_flags & fs_open_write_only);
	}
	virtual uint64_t write(const void* data, size_t count) override {
		if (!can_write()) CELL_FS_EPERM;

		uint64_t nwr = 0;
		
		int  r = cellFsWrite(_handle, data, static_cast<uint64_t>(count), &nwr);

		return sys::select(CELL_ERROR_IS_FAILURE(r), (uint64_t)r, nwr);

	}

	virtual uint64_t read(void* buffer, size_t count)override {
		if (!can_read()) CELL_FS_EPERM;

		uint64_t nrd = 0;

		int r = cellFsWrite(_handle, buffer, static_cast<uint64_t>(count), &nrd);

		return sys::select(CELL_ERROR_IS_FAILURE(r), (uint64_t)r, nrd);
	}

	virtual uint64_t seek(int64_t offset, int origin)override {
		uint64_t position = 0;
		
		int R = cellFsLseek(this->_handle, offset, origin, &position);

		return sys::select(CELL_ERROR_IS_FAILURE(R), (uint64_t)R, position);
	}

	virtual uint64_t get_length() const override {
		uint64_t eof = 0;
		uint64_t _ = 0;
		cellFsLseek(this->_handle, 0, SEEK_END, &eof);
		cellFsLseek(this->_handle, 0, SEEK_SET, &_);

		return eof;
	}

	virtual uint64_t get_position() const override {
		uint64_t _ = 0;
		cellFsLseek(this->_handle, 0, SEEK_CUR, &_);
		return _;
	}

	virtual ~file_stream() = default;
};



_SYS_ENS