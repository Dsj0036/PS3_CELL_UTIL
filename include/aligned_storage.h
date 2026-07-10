#pragma once
namespace sys{
	template <size_t Size, size_t Align>
	struct aligned_storage
	{
		struct type {
			__attribute__((aligned(Align)))
				unsigned char data[Size];
		};
	};
}