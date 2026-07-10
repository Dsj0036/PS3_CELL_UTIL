#pragma once
#include "_ns.h"
#ifndef __SYS_ACTIVATE_INPLACE__
#define __SYS_ACTIVATE_INPLACE__
#define activate_inplace(memory, typename_) new (memory)typename_

_SYS_NS

_SYS_ENS

#endif 
