#pragma once
#include "System.h"
#include "include\lgc.h"
#include "include\variadic_lgc.h"
namespace RandomLGC {
	uint64_t Gens[4];

	void Tick() {
		if (Gens[0] == -1 || Gens[0] >= -1ul) {
			Gens[0] %= (Gens[1] % Gens[2]) + Gens[3];
		}
		float R = Gens[0];
		Gens[0]+=__LGC__(*(int*) & R);

		for (int i = 1; i < 4; i++) {
			Gens[i] += __LGC__(Gens[i - 1]);
			if (Gens[i] >= -1UL) {
				Gens[i] %= (Gens[1]) % 0xFFFF + 0xFFFFFF;
			}
		}
	}
	uint64_t Next(uint64_t max) {
		uint64_t seed;
		uint64_t seed_final;
		for (int i = 0; i < 4; i++) {
			(seed += 1);
			seed <<= i;
			seed_final -= __LGC__(Gens[i]);
		}
		return (__LGC__(seed_final + seed) % max + 1);
	}
}