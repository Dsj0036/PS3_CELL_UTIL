#pragma once
#include "_ns.h"
#include <numeric>
#include <sys\sys_time.h>

_SYS_NS

class random {
private:
	static constexpr uint32_t MAGIC = 1812433253u;
	static constexpr uint32_t DBL_MAGIC = 0xffffffff;
	uint32_t state[4];
	static uint32_t rotl(const uint32_t x, int k) {
		return (x << k) | (x >> (32 - k));
	}

public:
	random();
	void seed(uint32_t s) noexcept;
	uint32_t next();
	inline bool isInitialized() const;
	int next(int min, int max);
	float nextFloat(float a, float b);
	double nextDouble(double a, double b);
	int nextInt(int a, int b);
	bool nextBool();
	static random& def();

};

_SYS_ENS