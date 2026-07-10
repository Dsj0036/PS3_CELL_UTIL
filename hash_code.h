#pragma once
#include "_sys_mem.h"

namespace sys {

	static constexpr uint32_t Prime1 = 2654435761U;
	static constexpr uint32_t Prime2 = 2246822519U;
	static constexpr uint32_t Prime3 = 3266489917U;
	static constexpr uint32_t Prime4 = 668265263U;
	static constexpr uint32_t Prime5 = 374761393U;

	struct hasher {
		uint32_t _v1, _v2, _v3, _v4;
		uint32_t _queue1, _queue2, _queue3;
		uint32_t _length;

		static uint32_t getSeed();

		static unsigned long rotl(unsigned long value, int offset);
		static void initialize(uint32_t* v1, uint32_t* v2, uint32_t* v3, uint32_t* v4);

		static uint32_t mix_state(uint32_t v1, uint32_t v2, uint32_t v3, uint32_t v4);

		static uint32_t queue_round(uint32_t hash, uint32_t queuedValue);
		static uint32_t mix_empty_state();
		static uint32_t round(uint32_t hash, uint32_t input);

		static int TrailingZeroCount(unsigned long value);
		static int log2(unsigned long value);
		static int log2ceiling(unsigned long value);
		void addbytes(const void* data, size_t length);


		static int popcount(unsigned long value);
		static uint32_t mix_final(uint32_t hash);
		static int combine(uint32_t input);
		static int combine(uint32_t value1, uint32_t value2);

		void add(int value);
		int to_hash_code();
	};

	int get_hash_small(const char* ptr, int length);
	// fnv1a
	size_t get_hash(const wchar_t* str, int length);
	// fnv1a
	size_t get_hash(const char* str, int length);
	size_t get_hash(bool b);

	size_t get_hash(const wchar_t* text, size_t length);

	size_t get_hash(const char* str);

	static inline uint32_t ppc_hsh(uint32_t x) {
		x ^= x >> 15;
		x *= 0xd168aae1;
		x ^= x >> 15;
		x *= 0xaf723597;
		x ^= x >> 15;
		return x;
	}
}