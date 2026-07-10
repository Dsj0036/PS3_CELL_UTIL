#pragma once
#if false
#include "traits.h"
#include "smart_pointer/_sp_convertible.h"
#include "hash_traits.h"


template<typename T>
struct hash_argument
{
	using type =
		typename sys::_Select<
		sys::is_fundamental<T>::value,
		T,
		const T&
		>::type;
};


template<typename T>
using hash_function_t =
uint32_t(*)(typename hash_argument<T>::type);


template<typename K, typename V>
struct entry
{
	K key;
	V value;
	entry* next = nullptr;

	entry(K k, V v)
		: key(k), value(v) {
	}
};

// Improve.
template<typename K, typename V, hash_function_t<K> HashFunction = sys::hash_traits::get_hash<K>>
class hash_map
{

	entry<K, V>** buckets;
	size_t capacity;
	size_t size;
	float maxLoad = 0.75f;
public:
	using entry_ = entry<K, V>;
	using value_argument = typename hash_argument<V>::type;

	static constexpr hash_function_t<K> FUNCTION = HashFunction;


	hash_map(size_t initialCapacity = 16)
	{
		capacity = initialCapacity;
		size = 0;

		buckets = new entry<K, V>* [capacity];

		for (size_t i = 0; i < capacity; i++)
			buckets[i] = nullptr;
	}

	size_t index(size_t hash)
	{
		return hash & (capacity - 1);
	}
	void insert(K key, value_argument value)
	{
		if ((float)size / capacity > maxLoad)
			rehash(capacity * 2);

		size_t bucketIndex = index(hash(key));
		entry<K, V>* current = buckets[bucketIndex];

		while (current)
		{
			if (current->key == key)
			{
				current->value = value;
				return;
			}
			current = current->next;
		}

		entry<K, V>* node = new entry<K, V>(key, value);
		node->next = buckets[bucketIndex];
		buckets[bucketIndex] = node;

		size++;
	}

	void rehash(size_t newCapacity)
	{
		entry<K, V>** oldBuckets = buckets;
		size_t oldCapacity = capacity;

		buckets = new entry<K, V>* [newCapacity];
		capacity = newCapacity;
		size = 0;

		for (size_t i = 0; i < capacity; i++)
			buckets[i] = nullptr;

		for (size_t i = 0; i < oldCapacity; i++)
		{
			entry<K, V>* node = oldBuckets[i];

			while (node)
			{
				entry<K, V>* next = node->next;

				insert(node->key, node->value);

				delete node; 
				node = next;
			}
		}

		delete[] oldBuckets;
	}
};


#endif