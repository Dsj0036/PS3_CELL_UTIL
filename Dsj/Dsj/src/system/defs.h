#pragma once
#include <types.h>
#pragma region DEFINITIONS

#define THIS ((unsigned int)this)
#define INT8_MIN	(-0x7f - _C2)
#define INT16_MIN	(-0x7fff - _C2)
#define INT32_MIN	(-0x7fffffff - _C2)

#define INT8_MAX	0x7f
#define INT16_MAX	0x7fff
#define INT32_MAX	0x7fffffff
#define UINT8_MAX	0xff
#define UINT16_MAX	0xffff
#define UINT32_MAX	0xffffffff

#define INT_LEAST8_MIN		(-0x7f - _C2)
#define INT_LEAST16_MIN		(-0x7fff - _C2)
#define INT_LEAST32_MIN		(-0x7fffffff - _C2)

#define INT_LEAST8_MAX		0x7f
#define INT_LEAST16_MAX		0x7fff
#define INT_LEAST32_MAX		0x7fffffff
#define UINT_LEAST8_MAX		0xff
#define UINT_LEAST16_MAX	0xffff
#define UINT_LEAST32_MAX	0xffffffff

#define INT_FAST8_MIN		(-0x7fffffff - _C2)
#define INT_FAST16_MIN		(-0x7fffffff - _C2)
#define INT_FAST32_MIN		(-0x7fffffff - _C2)

#define INT_FAST8_MAX		0x7fffffff
#define INT_FAST16_MAX		0x7fffffff
#define INT_FAST32_MAX		0x7fffffff
#define UINT_FAST8_MAX		0xffffffff
#define UINT_FAST16_MAX		0xffffffff
#define UINT_FAST32_MAX		0xffffffff

#define __reserved_stub() __nop();__nop();__nop();__nop();__nop()

#ifndef RAND_MAX
#define RAND_MAX	0x3fffffff
#endif

#define MAX(a, b)			((a) >= (b) ? (a) : (b))

#define MIN(a, b)			((a) <= (b) ? (a) : (b))

#define ABS(a)				(((a) < 0) ? -(a) : (a))


#define TRUNC_DECIMALS(x) (floorf(x * 100) / 100.0)

#define HIWORD(l) ((unsigned short)(((unsigned long)(l) >> 16) & 0xFFFF))

#define LOWORD(l) ((unsigned short)((unsigned long)(l) & 0xFFFF))

#define MAKELONG(low, high) ((unsigned long)(((unsigned short)(low)) | (((unsigned long)((unsigned short)(high))) << 16)))

