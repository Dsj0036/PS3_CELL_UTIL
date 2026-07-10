#pragma once
#include <cell/error.h>
#include <errno.h>
namespace sys {
	inline bool is_failure(int num_) {
		return CELL_ERROR_IS_FAILURE(num_) && num_ < 0;
	}
	extern const char* what(int);
}