#pragma once
#include "_ns.h"
_SYS_NS
static inline short bswap16(short v)
{
	return (short)((v >> 8) | (v << 8));
}

static inline uint16_t bswap16(uint16_t v)
{
	return (uint16_t)((v >> 8) | (v << 8));
}

static inline uint32_t bswap32(uint32_t v)
{
	return ((v >> 24) & 0x000000FF) |
		((v >> 8) & 0x0000FF00) |
		((v << 8) & 0x00FF0000) |
		((v << 24) & 0xFF000000);
}

static inline float bswapf(float v)
{
	int i = 0;
	sys::memcpy(&i, &v, 4);
	i = bswap32(i);
	return *(float*)&i;
}
static inline uint64_t bswap64(uint64_t i)
{

	return i =
		((i >> 56) & 0x00000000000000FFULL) |
		((i >> 40) & 0x000000000000FF00ULL) |
		((i >> 24) & 0x0000000000FF0000ULL) |
		((i >> 8) & 0x00000000FF000000ULL) |
		((i << 8) & 0x000000FF00000000ULL) |
		((i << 24) & 0x0000FF0000000000ULL) |
		((i << 40) & 0x00FF000000000000ULL) |
		((i << 56) & 0xFF00000000000000ULL);
}
static inline double bswapd(double v)
{
	unsigned long long i = 0;//*(unsigned long long*) & v;
	sys::memcpy(&i, &v, 8);
	i =
		((i >> 56) & 0x00000000000000FFULL) |
		((i >> 40) & 0x000000000000FF00ULL) |
		((i >> 24) & 0x0000000000FF0000ULL) |
		((i >> 8) & 0x00000000FF000000ULL) |
		((i << 8) & 0x000000FF00000000ULL) |
		((i << 24) & 0x0000FF0000000000ULL) |
		((i << 40) & 0x00FF000000000000ULL) |
		((i << 56) & 0xFF00000000000000ULL);

	return *(double*)&i;
}
_SYS_ENS