#pragma once

#include <sys\synchronization.h>
#include "_ns.h"
_SYS_NS
class lightweight_mutex {
	sys_lwmutex_t _mutex;
	bool _lock{ false };
public:
	explicit lightweight_mutex(sys_protocol_t protocol = SYS_SYNC_PRIORITY,
		sys_recursive_t recursive = SYS_SYNC_NOT_RECURSIVE) noexcept;

	lightweight_mutex(const lightweight_mutex&) = delete;
	lightweight_mutex& operator=(const lightweight_mutex&) = delete;

	int lock(usecond_t timeout);
	int lock();
	bool locked() const;

	bool try_lock() noexcept;

	void unlock() noexcept;
	sys_lwmutex_t& handle();

	~lightweight_mutex();
};

using mutex = lightweight_mutex;

_SYS_ENS
