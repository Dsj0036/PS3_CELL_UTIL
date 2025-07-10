#pragma once
#include "System.h"
#include "BinaryReader.h"
#include "Buffer.h"
#include "Optional.h"
enum FileStreamMode {
	Readonly,
	WritingOnly,
	CreateReadWrite,
	Truncate,
};
class FileStream{
	int			_descriptor;	// file stream descriptor.
	std::string _filepath;		// fully qualified filename
	uint64_t	_srcLen;		// current buffer max length
	uint64_t	_readLen;		// current readed length
	uint64_t	_currentPos;	// current pos
	int			_error;			// last error
	int			_flags;			// stream flags
	bool		_opened;		// opened without errors.
	FileStream(const std::string& path, FileStreamMode mode){

	}
	Buffer ReadBytes(int startOffset, int count){
		Buffer container(count);
		BinaryWriter writer = container.write();
		
	}
	uint64_t Read(void* dst, uint64_t count) {
		uint64_t readed;
		_error = cellFsRead(_descriptor, dst, count, &readed);
		if (_error == 0)
			this->_readLen = readed;
		return _error == 0 ? readed : _error;
	}
	int open(const std::string& path, FileStreamMode mode) {

		int flags = 0;
		if (mode & FileStreamMode::WritingOnly)
			flags |= CELL_FS_O_WRONLY;
		else if (mode & FileStreamMode::Readonly)
			flags = CELL_FS_O_RDONLY;
		else if (mode & FileStreamMode::CreateReadWrite)
			flags |= CELL_FS_O_RDWR;
		if (mode & FileStreamMode::Truncate)
			flags |= CELL_FS_O_TRUNC;
		
		_error = cellFsOpen(path.c_str(), flags, &_descriptor, 0, 0);
		if (_error == 0) {
			_flags = flags;
			_filepath = path;
		}
		return _error;
	}
	
};

Optional<std::string> ReadAllText(const std::string& filename) {
	Optional<std::string> opt;
	CellFsStat STAT;
	int stream;
	if (cellFsStat(filename.c_str(), &STAT) == 0) {
		Buffer buffer(STAT.st_size);
		uint64_t dummy;
		if (cellFsOpen(filename.c_str(), CELL_FS_O_RDONLY, &stream, 0, 0) == 0 && STAT.st_size > 0) {
			if (cellFsRead(stream, buffer.getData(), STAT.st_size, &dummy) == 0) {
				opt.emplace((const char*)buffer.getData());
				return opt;
			}
		}
	}
	return opt;
}