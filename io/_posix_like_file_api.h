#pragma once
#include "..\_ns.h"
#include "..\error_code.h"

_SYS_NS


/**
 * @brief Validates a file open flag combination.
 *
 * Checks whether the supplied file access flags represent a valid combination
 * supported by the CELL filesystem API.
 *
 * Validation includes:
 * - Access mode correctness.
 * - Creation and exclusive creation rules.
 * - Truncation restrictions.
 * - Unsupported flag detection.
 *
 * @param flags File opening flags.
 *
 * @return true if the flag combination is valid, otherwise false.
 */
	extern bool is_valid_file_oflag(int flags);


/**
 * @brief Determines whether a file flag combination allows writing.
 *
 * This function validates the flags before checking the access mode.
 *
 * @param flags File opening flags.
 *
 * @return true if the file can be opened for writing.
 */
extern bool file_flag_can_write(int flags);


/**
 * @brief Determines whether a file flag combination allows reading.
 *
 * This function validates the flags before checking the access mode.
 *
 * @param flags File opening flags.
 *
 * @return true if the file can be opened for reading.
 */
extern bool file_flag_can_read(int flags);


/**
 * @brief Checks whether a file handle references a valid open file.
 *
 * Performs a non-destructive seek operation to verify that the handle
 * is accepted by the underlying CELL filesystem.
 *
 * @param handle File descriptor returned by fopen().
 *
 * @return true if the handle is valid.
 *
 * @note This function does not close or modify the file position.
 */
extern bool is_valid_file_handle(int handle);


/**
 * @brief Opens a file using CELL filesystem services.
 *
 * Wrapper around cellFsOpen providing a simplified POSIX-like interface.
 *
 * @param filename Path of the file to open.
 * @param flags File opening flags.
 *
 * @return File handle on success, otherwise a CellError code.
 */
extern int fopen(
	const char* filename,
	int flags
);


/**
 * @brief Writes data to an opened file.
 *
 * Writes the requested number of bytes from the input buffer into the file
 * represented by the handle.
 *
 * @param handle Valid file handle.
 * @param data Source buffer.
 * @param size Number of bytes to write.
 *
 * @return Number of bytes written, or CellError on failure.
 */
extern uint64_t fwrite(
	int handle,
	const void* data,
	uint64_t size
);


/**
 * @brief Reads data from an opened file.
 *
 * Reads bytes from the current file position into the destination buffer.
 *
 * @param handle Valid file handle.
 * @param outBuffer Destination buffer.
 * @param count Number of bytes requested.
 *
 * @return Number of bytes read, or CellError on failure.
 */
extern uint64_t fread(
	int handle,
	void* outBuffer,
	uint64_t count
);


/**
 * @brief Retrieves the current file position.
 *
 * Equivalent to a 32-bit compatible ftell operation.
 *
 * @param handle Valid file handle.
 *
 * @return Current byte offset, or CellError on failure.
 */
extern long ftello(int handle);


/**
 * @brief Retrieves the current file position using 64-bit offset.
 *
 * @param handle Valid file handle.
 *
 * @return Current byte offset, or CellError on failure.
 */
extern uint64_t ftello64(int handle);


/**
 * @brief Changes the current file position.
 *
 * Moves the file cursor according to the specified origin.
 *
 * @param handle Valid file handle.
 * @param whence Seek origin:
 *        - SEEK_SET
 *        - SEEK_CUR
 *        - SEEK_END
 * @param offset Relative offset.
 *
 * @return New file position after seeking, or CellError on failure.
 */
extern uint64_t fseek(
	int handle,
	int whence,
	int64_t offset
);


/**
 * @brief Retrieves the total length of a file.
 *
 * The current file position is restored after querying the size.
 *
 * @param handle Valid file handle.
 *
 * @return File length in bytes, or CellError on failure.
 */
extern uint64_t flength(int handle);


/**
 * @brief Closes an opened file handle.
 *
 * Releases the filesystem resource associated with the handle.
 *
 * @param handle File handle to close.
 *
 * @return Zero on success, otherwise a CellError code.
 */
extern int fclose(int handle);


_SYS_ENS


