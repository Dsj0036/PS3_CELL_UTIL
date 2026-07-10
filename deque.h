

/**
 * @file deque.h
 * @brief A dynamically resizing double-ended queue (deque) implementation with circular buffer semantics.
 *
 * Provides insertion and removal from both front and back in amortized constant time.
 * Includes cloning, comparison, and destruction traits.
 */

#pragma once
#include "_ns.h"
#include <limits>
#include <memory>
#include <initializer_list>
#include "array.h"

_SYS_NS

#define DEQUE_INITIAL_CAPACITY 4
#define DEQUE_MAX_CAPACITY 0xffff
#define DEQUE_TROUBLESHOOTING 0

/**
 * @brief Generic deque implementation with circular buffer logic.
 *
 * Supports pushing and popping elements from both ends in amortized O(1).
 * Grows dynamically when capacity is exceeded.
 * 
 *
 * @tparam T Type of elements stored.
 */
	template<typename T>
class alignas(4) deque  {
	T* _array;
	size_t _head;
	size_t _tail;
	size_t _size;
	size_t _capacity;

public:
	/**
	 * @brief Constructs an empty deque with optional initial capacity.
	 * @param capacity Desired initial capacity.
	 */
	deque(int capacity);

	/**
	 * @brief Default constructor.
	 */
	deque();

	/**
	 * @brief Copy constructor.
	 * @param other Deque to copy.
	 */
	deque(const deque<T>& other);

	/** @brief Returns whether the deque is empty. */
	bool empty() const;

	/** @brief Returns the number of elements. */
	int count() const;

	/** @brief Adds an element to the back. */
	void push_back(const T& value);
	/** @brief Adds an element to the back. */
	T& push_back_unsafe();

	/** @brief Adds a default-constructed element to the back. */
	T& push_back_default();

	/** @brief Adds a default-constructed element to the front. */
	T& push_front_default();

	/** @brief Removes and returns the last element. */
	T dequeue_back();

	/** @brief Removes and returns the last element (move). */
	T dequeue_back_move();

	/** @brief Removes and returns the first element. */
	T dequeue_front();

	/** @brief Removes and returns the first element (move). */
	T dequeue_front_move();

	/** @brief Adds an element to the front. */
	void push_front(const T& value);

	/** @brief Destroys all elements and frees memory. */
	void clear();

	/** @brief Returns the last element (mutable). */
	T& tail();

	/** @brief Returns the last element (const). */
	const T& tail() const;

	/** @brief Returns the first element (mutable). */
	T& head();

	/** @brief Returns the first element (const). */
	const T& head() const;

	/** @brief Element access (mutable). */
	T& operator[](size_t i);

	/** @brief Element access (const). */
	const T& operator[](size_t i) const;

	/** @brief Destructor. Calls @ref clear. */
	virtual ~deque();

private:
	/** @brief Ensures capacity is at least `required_capacity`. */
	void ensure_capacity(int required_capacity);

	/**
	 * @brief Grows the buffer to fit more elements.
	 * @param requiredCapacity Optional required capacity.
	 */
	void grow(int requiredCapacity = 0);

	/** @brief Compares two objects for equality or address identity. */
	bool compare_objects(const T& left, const T& right) const;

	bool compare_objects(T& left, T& right) const;
	bool compare_objects(const T& left, T& right) const;

	/** @brief Copies objects using copy constructor. */
	void copy_objects_non_trivial(T* origin, T* destination, int count);

	void copy_objects_non_trivial(T* origin, int originIndex, T* dest, int destIndex, int count);

	/** @brief Accesses an element at raw index without wrap. */
	T& _unsafe_element_at(int index) const;

	/** @brief Internal equality comparison. */
	bool equals(const deque<T>& other) const override;

	/** @brief Clones the current deque into another. */
	void _do_clone(deque<T>* other) const override;

	/** @brief Destroys the underlying array and all elements. */
	void destroy_array();
};

_SYS_ENS

#include "deque.inl"