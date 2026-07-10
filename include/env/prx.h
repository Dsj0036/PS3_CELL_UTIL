#pragma once
#include <sys/moduleexport.h>


namespace sys {
    namespace env {
        
        namespace modules {
            namespace detail {
                void initialize();
            }
        }
    }
}
#define __XSYS_DEFINE_ENTRY_POINT(ENTRY_POINT)  namespace sys {    \
    namespace env {                                                \
                                                                   \
        namespace modules {                                        \
            namespace detail {                                     \
                void initialize();                                 \
            }                                                      \
        }                                                          \
    }                                                              \
}\
extern "C" int __xsys_prx_initialize(size_t args, void* argp)\
{sys::env::modules::detail::initialize();\
return ENTRY_POINT(args, argp);\
}                     

#define __XSYS_LIB_TABEL_ADDRESS_DEFINE() namespace sys{namespace env{\
__attribute__((section(".rodata.progmoddef", "a"), used, unused)) static const char __begin_of_setion_progmodef_head[] = ".rodata.progmoddef";  \
__attribute__((section(".rodata.progmoddef", "a"), used, unused)) static const int __begin_of_section_progmoddef[1] = {0xffffff};}}  

#define __XSYS_PRX_MODULE(NAME, ATTRIBUTE, ENTRY_POINT, MAJOR, MINOR) __XSYS_DEFINE_ENTRY_POINT(ENTRY_POINT)\
__XSYS_LIB_TABEL_ADDRESS_DEFINE();\
SYS_MODULE_INFO(NAME, ATTRIBUTE, MAJOR, MINOR);\
SYS_MODULE_START(__xsys_prx_initialize);
