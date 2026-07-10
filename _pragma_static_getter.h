#pragma once
#define _SYS_DEFINE_STATIC_GETTER(NAME, RETURN_TYPE) \
namespace __getter { \
    class __##NAME##_wrapper final { \
public:\
        operator RETURN_TYPE();\
    }; \
} \
static __getter::__##NAME##_wrapper NAME{};



#define _SYS_DEFINE_STATIC_GETTER_INLINE(NAME, RETURN_TYPE, BODY) \
namespace __getter { \
    class __##NAME##_wrapper final { \
public:\
        inline operator RETURN_TYPE(){BODY;}\
    }; \
} \
static __getter::__##NAME##_wrapper NAME{};