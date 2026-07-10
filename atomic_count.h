#pragma once
#include <cell/atomic.h>
namespace sys {

	class atomic_count
	{
	public:

		explicit atomic_count(uint32_t v);

		uint32_t operator++();

		uint32_t operator--();

		void set_value(uint32_t v) {
			this->value_ = v;
		}

		operator uint32_t() const
		{
			
			return value_;
		}

	private:
		atomic_count(atomic_count const&);
		atomic_count& operator=(atomic_count const&);

		mutable uint32_t value_;
	};
}