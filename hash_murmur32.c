#include "pch.h"
#include "hash_murmur32.h"
extern "C" {

    unsigned int murmurhash3_32(const char* key, int len, unsigned int seed) {
        const unsigned int c1 = 0xcc9e2d51;
        const unsigned int c2 = 0x1b873593;
        unsigned int h1 = seed;

        const int nblocks = len / 4;
        const unsigned int* blocks = reinterpret_cast<const unsigned int*>(key);

        for (int i = 0; i < nblocks; ++i) {
            unsigned int k1 = blocks[i]; // Assumes little-endian/aligned safe architecture

            k1 *= c1;
            k1 = (k1 << 15) | (k1 >> 17); // Rotl32
            k1 *= c2;

            h1 ^= k1;
            h1 = (h1 << 13) | (h1 >> 19); // Rotl32
            h1 = h1 * 5 + 0xe6546b64;
        }

        // Tail processing for remaining 1-3 bytes
        const unsigned char* tail = reinterpret_cast<const unsigned char*>(key + nblocks * 4);
        unsigned int k1 = 0;

        switch (len & 3) {
        case 3: k1 ^= tail[2] << 16;
        case 2: k1 ^= tail[1] << 8;
        case 1: k1 ^= tail[0];
            k1 *= c1;
            k1 = (k1 << 15) | (k1 >> 17);
            k1 *= c2;
            h1 ^= k1;
        };

        // Finalization mix
        h1 ^= len;
        h1 ^= (h1 >> 16);
        h1 *= 0x85ebca6b;
        h1 ^= (h1 >> 13);
        h1 *= 0xc2b2ae35;
        h1 ^= (h1 >> 16);

        return h1;
    }
}