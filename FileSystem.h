#pragma once
#ifndef __PS3_SYSTEM_UTILITIES__
#include "System.h"
#endif

#ifndef __FILESYSTEM_H__
#define __FILESYSTEM_H__
std::string FS_GET_DIRECTORY_NAME(char* cs) {
	std::string base(cs);
	short index = base.find_last_of('/');
	return base.substr(0, index);
}

std::string FS_SAFEFILENAME(const char* cs) {
	std::string base(cs);
	short index = base.find_last_of('/');
	return base.substr(index + 1);
}
std::string get_safe_filename(const char* cs) {
	std::string sn = FS_SAFEFILENAME(cs);
	short i = sn.find_last_of('.');
	if (i != -1) {
		return sn.substr(0, i);
	}
	else {
		return sn;
	}
}
std::string FS_PATHEXTENSION(const char* cs) {
	std::string sn = FS_SAFEFILENAME(cs);
	short i = sn.find_last_of('.');
	std::string extension = sn.substr(i + 1);
	return extension;
}
bool FS_MKDIR(char* path) { return cellFsMkdir(path, CellFsMode(CELL_FS_O_RDWR) == CELL_OK); }
void FS_RECREATE(const char* b)
{
	int d;
	cellFsOpen(b, CELL_FS_O_CREAT | CELL_FS_O_TRUNC, &d, 0, 0);
	cellFsClose(d);
}
uint64_t FS_GETSIZE(char* path)
{
	struct CellFsStat s;
	if (cellFsStat(path, &s) == CELL_FS_SUCCEEDED) {
		if (s.st_size > 0) {
			return s.st_size;
		}
	}
	return -1;
}void FS_REPLACEXT(char* path, const char* newExtension) {
	int length = 0;

	// Find the length of the path
	while (path[length] != '\0') {
		length++;
	}

	// Traverse the path backward to find the last '.'
	int i = length - 1;
	while (i >= 0 && path[i] != '.') {
		i--;
	}

	// If a dot was found, replace the extension
	if (i >= 0) {
		int j = 0;
		while (newExtension[j] != '\0') {
			path[i + 1 + j] = newExtension[j];
			j++;
		}

		// Set the null terminator at the end of the new path
		path[i + 1 + j] = '\0';
	}
}
int FS_PURGE(const char* filePath) {
	CellFsErrno fsErr;
	CellFsStat stat;

	// Check if the file exists
	if (cellFsStat(filePath, &stat) != 0) {
		// File doesn't exist
		return -1;
	}

	// Delete the file
	if (cellFsUnlink(filePath) != 0) {
		// Failed to delete the file
		return -1;
	}

	return 0; // File deleted successfully
}

void EXTRACT_DIRECTORY(const char* filename, char* directory) {
	int length = 0;

	// Find the length of the filename
	while (filename[length] != '\0') {
		length++;
	}

	// Traverse the filename backward to find the last '/'
	int i = length - 1;
	while (i >= 0 && filename[i] != '/') {
		i--;
	}

	// Copy the directory to the output buffer
	int j = 0;
	while (j <= i) {
		directory[j] = filename[j];
		j++;
	}

	// Add null terminator to the directory string
	directory[j] = '\0';
}

int FS_DIREXISTS(const char* path, CellFsErrno* e)
{
	int fd;
	int errn;
	errn = cellFsOpendir(path, &fd);
	if (errn != 0) {
		errn = cellFsClosedir(fd);
		return false;
	}
	e = &errn;
	cellFsClosedir(fd);
	return true;
}
bool FS_DIREXISTS(const char* path)
{
	int fd;
	int errn;
	errn = cellFsOpendir(path, &fd);
	if (errn != 0) {
		errn = cellFsClosedir(fd);
		return false;
	}
	cellFsClosedir(fd);
	return true;
}

bool FS_FILEEXISTS(const char* path)
{
	int fdl;
	CellFsErrno readLic;
	readLic = cellFsOpen(path, CELL_FS_O_RDONLY, &fdl, NULL, 0);
	cellFsClose(fdl);
	if (readLic == CELL_OK)
	{
		return true;
	}
	else return false;
}
char* FS_BUFFREAD(char* File)
{
	int fdl;
	char licStr[32];
	CellFsErrno readLic;
	uint64_t swl;

	readLic = cellFsOpen(File, CELL_FS_O_RDONLY, &fdl, NULL, 0);

	if (readLic == 0)
	{
		cellFsRead(fdl, licStr, sizeof(licStr), &swl);
		cellFsClose(fdl);
	}
	return licStr;
}
bool FS_REN(char* target, char* renameTo)
{
	return cellFsRename(target, renameTo) == 0;
}
bool FS_PURGE(char* path)
{
	return cellFsRmdir(path) == 0;
}
void FS_CREATE(char* loc) {
	int fd;
	int ret;
	ret = cellFsOpen(loc, CELL_FS_O_CREAT | CELL_FS_O_RDWR | CELL_FS_O_TRUNC, &fd, NULL, 0);
	cellFsClose(fd);
}
void FS_TRUNCATE(char* loc) {
	int fd;
	int ret;
	ret = cellFsOpen(loc, CELL_FS_O_RDWR | CELL_FS_O_TRUNC, &fd, 0, 0);
	cellFsClose(fd);
	if (!ret) {
		cellFsClose(fd);
	}
}
int FS_WRITE(char* file, char buf[] = 0, int size = 0) {
	CellFsErrno err;
	int fd;
	uint64_t nrw;
	int ret;
	err = cellFsOpen(file, CELL_FS_O_RDWR | CELL_FS_O_CREAT, &fd, 0, 0);
	if (size != 0)
		err = cellFsWrite(fd, (const void*)buf, (uint64_t)size, &nrw);
	cellFsClose(fd);
	return err;
}
void FS_APPEND(char* file, char buf[] = 0, int size = 0) {
	int err;
	int fd;
	uint64_t nrw;
	int ret;
	err = cellFsOpen(file, CELL_FS_O_RDWR | CELL_FS_O_APPEND | CELL_FS_O_CREAT, &fd, NULL, 0);
	if (size != 0)
		err = cellFsWrite(fd, (const void*)buf, (uint64_t)size, &nrw);
	err = cellFsClose(fd);
}
void appendToFileN(char* file, char* buf, int size = 0) {
	int err;
	int fd;
	uint64_t nrw;
	int ret;
	err = cellFsOpen(file, CELL_FS_O_RDWR | CELL_FS_O_APPEND | CELL_FS_O_CREAT, &fd, NULL, 0);
	if (size != 0)
		err = cellFsWrite(fd, (const void*)buf, (uint64_t)size, &nrw);
	err = cellFsClose(fd);
}
void FS_APPEND(char* file, char buf[] = 0, int size = 0, void(*writeadd)(int fd) = 0) {
	int err;
	int fd;
	uint64_t nrw;
	int ret;
	err = cellFsOpen(file, CELL_FS_O_RDWR | CELL_FS_O_APPEND | CELL_FS_O_CREAT, &fd, NULL, 0);
	if (size != 0)
		err = cellFsWrite(fd, (const void*)buf, (uint64_t)size, &nrw);
	if (writeadd != 0) { writeadd(fd); }

	err = cellFsClose(fd);
}
void FS_APPEND(int fd, char buff[] = 0, int size = 0) {
	uint64_t nrw;
	cellFsWrite(fd, (const void*)buff, size, &nrw);
}
void FS_APPEND_STRING(char* file, char buf[] = 0)
{
	FS_APPEND(file, buf, sys::strlen(buf), 0);
}
void FS_APPEND_STRING(char* file, char buf[], void(*writeadd)(int fd))
{
	FS_APPEND(file, buf, sys::strlen(buf), writeadd);
}
void appendLines(char* file, char* lines[5]) {
	int err;
	int fd;
	uint64_t nrw;
	int ret;
	int size = sys::strlen(lines[0]);
	err = cellFsOpen(file, CELL_FS_O_RDWR | CELL_FS_O_APPEND | CELL_FS_O_CREAT, &fd, NULL, 0);
	if (size != 0)
		err = cellFsWrite(fd, (const void*)(lines[0]), (uint64_t)size, &nrw);
	if (sizeof(lines[1]) > 0) {
		int sz1 = sys::strlen(lines[1]);
		err = cellFsWrite(fd, (const void*)(lines[1]), (uint64_t)sz1, &nrw);
	}
	if (sizeof(lines[2]) > 0) {
		int sz2 = sys::strlen(lines[2]);
		err = cellFsWrite(fd, (const void*)(lines[2]), (uint64_t)sz2, &nrw);
	}

	if (sizeof(lines[3]) > 0) {
		int sz3 = sys::strlen(lines[3]);
		err = cellFsWrite(fd, (const void*)(lines[3]), (uint64_t)sz3, &nrw);
	}

	if (sizeof(lines[4]) > 0) {
		int sz4 = sys::strlen(lines[4]);
		err = cellFsWrite(fd, (const void*)(lines[4]), (uint64_t)sz4, &nrw);
	}

	if (sizeof(lines[4]) > 0) {
		int sz5 = sys::strlen(lines[5]);
		err = cellFsWrite(fd, (const void*)(lines[5]), (uint64_t)sz5, &nrw);
	}
	err = cellFsClose(fd);
}
static const char* get_ext(const char* path)
{
	if (!path || !(*path)) return path;

	const int len = sys::strlen(path);
	const char* ext = path + len - 1;
	const char* end = ext - ((*ext == ']') ? 13 : 6); // search limit 6 or 13 chars
	if (*ext == '0') ext--;
	while (--ext > path)
		if ((*ext == '.') || (ext <= end)) break;
	if (*ext != '.') ext = path + len;
	return ext;
}

size_t FS_READ_WITH_OFFSET(char* file, char* data, const size_t size, int64_t offset)
{
	if (!file || !data) return 0; // sanity check

	int fd = 0; uint64_t read_e = 0;

	if (cellFsOpen(file, CELL_FS_O_RDONLY, &fd, NULL, 0) == CELL_FS_SUCCEEDED)
	{
		if (cellFsReadWithOffset(fd, offset, (void*)data, size, &read_e) != CELL_FS_SUCCEEDED) read_e = 0;
		cellFsClose(fd);
	}
	else
	{
		return -1;
	}
	return read_e;
}

#endif
