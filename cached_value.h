#pragma once
#include "_ns.h"

_SYS_NS

// does not need to lock on fundamental. 
// compiler will guide you with this one.
// not intended to be used with non-trivial specific operations defined.

/**
 * @brief Stores a fundamental value and reports whether it has changed.
 *
 * This utility is intended for inexpensive value change detection. It is
 * particularly useful to avoid redundant work, such as rebuilding cached
 * strings, invalidating render state, or triggering updates only when the
 * underlying value actually changes.
 *
 * @tparam T A fundamental or trivially comparable type.
 *
 * @note This class is not thread-safe.
 * @note Intended for fundamental or trivially copyable value types.
 * @note Use with user-defined types only if equality comparison is inexpensive
 *       and copy semantics are well-defined.
 */
	template<typename T>
class cached_value final
{
public:

	/// Constructs an empty cached value using T's default initialization.
	inline cached_value() = default;

	/// Constructs the cache with an initial value.
	inline cached_value(T value) : _wrapped_val(value) {}

	/// Copies the cached value.
	inline cached_value(const cached_value<T>& other)
		: _wrapped_val(other._wrapped_val) {
	}

	/**
	 * @brief Copy assignment is intentionally disabled.
	 *
	 * Use update() instead so callers explicitly acknowledge change detection.
	 */
	inline cached_value<T>& operator=(cached_value<T>) = delete;

	/**
	 * @brief Updates the stored value.
	 *
	 * @param value The new value.
	 * @return true if the stored value changed.
	 * @return false if the value was already equal to the current one.
	 */
	inline bool update(T value)
	{
		if (value != _wrapped_val)
		{
			_wrapped_val = value;
			return true;
		}
		return false;
	}

	/// Returns the currently cached value.
	inline T value() const { return _wrapped_val; }

private:
	T _wrapped_val{};
};

_SYS_ENS