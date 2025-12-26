// hash_table.c
#include "../include/hash_table.h"

// djb2 non-cryptographic hash
static uint64_t hash(const unsigned char* str) { // high bit set characters can become negative. 
    uint64_t hash = 5381; 

    while(*str) {
        hash = hash * 33 + *str++; // original way is bit manipulation.
    }

    return hash; 
}

