#pragma once
#include "_ns.h"
_SYS_NS

inline bool contains_zero_byte(uint64_t x) {
	return(((x - ((uint64_t)0x0101010101010101L)) & ~x & ((uint64_t)0x8080808080808080L)) != 0);
}

inline uint64_t repeat_byte(uint8_t b) {
	return(((uint64_t)b) * (0xffffffffffffffffULL / 255));
}

uint64_t read_unaligned64(const uint8_t* ptr);
void* forward_search(const uint8_t* start_ptr,const uint8_t* end_ptr, const uint8_t* ptr, uint8_t n);
void* fast_memchr(const void* haystack, int b, size_t len);
_SYS_ENS
