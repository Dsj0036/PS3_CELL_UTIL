#pragma once
#include "_ns.h"
#include <stdint.h>
_SYS_NS
namespace _const {
	constexpr std::uint32_t fnv1a_prime = 16777619u;
	constexpr std::uint32_t fnv1a_basis = 2166136261u;
	static constexpr std::uint32_t constexpr_fnv1a_recursive_impl(const char* str, std::size_t count, std::uint32_t hash = fnv1a_basis) noexcept {
		return count == 0
			? hash
			: constexpr_fnv1a_recursive_impl(str + 1, count - 1,
				(hash ^ static_cast<std::uint8_t>(*str)) * fnv1a_prime);
	}
	template <std::size_t N>
	static constexpr std::uint32_t constexpr_fnv1a(const char(&str)[N]) noexcept {
		static_assert(N < 0x40, "str too large.");
		return constexpr_fnv1a_recursive_impl(str, N - 1);
	}

}
_SYS_ENS