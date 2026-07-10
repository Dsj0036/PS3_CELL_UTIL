#pragma once
#include <ppu_asm_intrinsics.h>
#include <sys\process.h>
extern inline sys_pid_t sys_process_getpid(void);
namespace sys {

	namespace krn {
		int shutdown();
		int reboot_hard();
		int reboot_quick();

		int reboot_soft();
		// Sleep for a specified number of milliseconds
		void sleep(usecond_t time);
		int32_t read(uint64_t address, void* data, size_t size);
		int32_t write(uint64_t address, const void* data, size_t size);
		int32_t mapi_write(uint64_t ea, const void* data, size_t size);
		int32_t mapi_read(uint64_t ea, void* data, size_t size);
	}

}
