#pragma once
#include "decimal4.h"
namespace pllx {
	namespace math {
		inline _decimal4 min(const _decimal4& left, const _decimal4& right) {
			if (left < right)
				return left;
			if (right < left)
				return right;
			return left;
		}
		inline _decimal4 max(const _decimal4& left, const _decimal4& right) {
			if (left > right)
				return left;
			if (right > left)
				return right;
			return left;
		}
	}
}