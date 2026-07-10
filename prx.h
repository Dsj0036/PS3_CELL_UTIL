#pragma once
#include "_ns.h"
#include <sys\prx.h>
#include <sys\prx_error.h>

_SYS_NS

namespace env {
#ifdef SYS_MODULE_INFO

	extern const sys_prx_id_t id;
	namespace detail {
		extern sys_prx_module_info_t info;
		extern sys_prx_segment_info_t segments[8];
		extern bool is_application;
		extern bool initialized;
		extern char mdname[SYS_PRX_MODULE_FILENAME_SIZE];
		sys_prx_id_t static_initialization();
	}

	static inline bool is_prx() {
		return id != -1;
	}
	sys_addr_t module_load_base();
	uint32_t num_segments();
	const char* name();
	uint16_t version();
	void** start_entry();
	void** stop_entry();
	const char* filename();

#endif
}

_SYS_ENS

