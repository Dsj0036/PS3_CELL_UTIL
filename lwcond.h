#pragma once

#include "_ns.h"

#include <sys\synchronization.h>
#include "resulting.h"
#include "thread.h"
#include "smart_pointer/unique_ptr.h"
_SYS_NS

class lwcond {
public:
	class Factory;
	friend Factory;

private:
	sys_lwcond_t mHdl{};
	sys_lwcond_attribute_t mAttrib{};

public:
	lwcond() {}

	class  Factory final{
		
	public :
		static int create(lwcond* output) {
			int R = create(*output);
			return R;
		}

		static int create(sys::lwcond& lwcond) {
			sys_lwmutex_t mutex;
			sys_lwmutex_attribute_t mutex_Attrib;

			sys_lwmutex_attribute_initialize(mutex_Attrib);
			int R = sys_lwmutex_create(&mutex, &mutex_Attrib);
			if (R < 0) return R;
			sys_lwcond_attribute_initialize(lwcond.mAttrib);
			return sys_lwcond_create(&lwcond.mHdl, &mutex, &lwcond.mAttrib);
		}
	};

	CellError dispose() {
		return sys_lwcond_destroy(&mHdl);
	}
	/*Wait for a signal from another PPU thread*/
	CellError wait(usecond_t timeout) {
		return sys_lwcond_wait(&mHdl, timeout);
	}

	/*Signal to a PPU thread waiting on a lightweight condition variable*/
	CellError signal() {
		return sys_lwcond_signal(&mHdl);
	}

	/*Signal to a specific PPU thread waiting on a lightweight condition variable*/
	CellError signal_to(sys::ppu_thread* knThread) {
		if (!knThread) return EINVAL;
		return sys_lwcond_signal_to(&mHdl, knThread->handle());
	}

	/*Signal to all PPU threads waiting on a lightweight condition variable*/
	CellError signal_all() {
		return sys_lwcond_signal_all(&mHdl);
	}

	~lwcond() {
		//Release resources if necessary, do nothing otherwise.
		dispose();
	}

};

static CellError create_condition(sys::unique_ptr<sys::lwcond>* output) {

	

	lwcond* m = new lwcond();

	int R = sys::lwcond::Factory::create(m);

	if (R != 0) {
		delete m;
		return R;
	}
	output->reset(m);
	return R;
}

_SYS_ENS