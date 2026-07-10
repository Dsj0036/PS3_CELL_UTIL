#include "_ns.h"
#include <stdint.h>
#include <stdio.h>
#include "traits.h"
#pragma once

_SYS_NS

// Defines an key value pair. Fixed hash map entry.
template <typename K, typename V>
struct fixed_hash_map_entry
{
    K key;
    V value;
    size_t hash;
    fixed_hash_map_entry(K k, V v, size_t hash) : key(k), value(v), hash(hash) {}
};
// Defines an fixed container for indexing data created at compile time.
template <typename K, typename V, size_t(HashFunction)(const K&)>
class fixed_hash_map
{
public:
    using entry = fixed_hash_map_entry<K, V>;
private:
    entry* buckets = { nullptr };
    const int length;

public:
    fixed_hash_map(entry* field, int N) : length(N){
        buckets = field;
    }

    ~fixed_hash_map()
    {
        for (size_t i = 0; i < length; ++i)
        {
            fixed_hash_map_entry<K, V>& current = buckets[i];
            if (current.hash != 0) sys::typed_destructor<fixed_hash_map_entry<K, V>>(&current);
        }
    }

    bool insert(K key, V value)
    {
        uint32_t hash = HashFunction(key);

        size_t index = hash & (length - 1);

        for (size_t i = 0; i < length; i++)
        {
            entry& e = buckets[index];

            if (e.hash == 0)
            {
                new(&e) entry{ key, value, hash };
                return true;
            }

            if (e.hash == hash && e.key == key)
            {
                e.value = value;
                return true;
            }

            index = (index + 1) & (length - 1);
        }

        return false;
    }

    bool get(const K& key, V& outValue) const
    {
        size_t hash = HashFunction(key);
        size_t bucketIndex = hash & (length - 1);
        V* foundValue = internal_lookup(bucketIndex, hash, &key);
        if (foundValue) outValue = *foundValue;

        return foundValue != NULL;
    }

    V* get_hash(size_t hash) {
        size_t bucketIndex = hash & (length - 1);
        if (bucketIndex < 0 || bucketIndex >= length) return false;
        return internal_lookup(bucketIndex, hash, NULL);
    }

    const V* get_hash(size_t hash) const {
        size_t bucketIndex = hash & (length - 1);
        if (bucketIndex < 0 || bucketIndex >= length) return false;
        return internal_lookup(bucketIndex, hash, NULL);
    }
private:
    V* internal_lookup(size_t startIndex, size_t hash, const K* expectKey) const {
        fixed_hash_map_entry<K, V>* current = &(buckets[startIndex]);

        size_t index = hash & (length - 1);

        for (size_t i = 0; i < length; i++)
        {
            entry& e = buckets[index];

            if (e.hash == 0)
            {
                return NULL;
            }

            if (expectKey != NULL)
                if (e.key == *expectKey)
                    return &e.value;

            if (e.hash == hash)
            {
                return &e.value;;
            }

            index = (index + 1) & (length - 1);
        }

        return NULL;
    }
};

_SYS_ENS