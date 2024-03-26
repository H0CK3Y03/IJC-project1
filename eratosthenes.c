// eratosthenes.c
// Riešenie IJC-DU1, príklad a), 21.03.2024
// Autor: Adam Veselý, FIT
// Preložené gcc version 11.4.0

#include <math.h>
#include "bitset.h"
#include "eratosthenes.h"

void eratosthenes(bitset_t p) {
    // 1. mission
    bitset_index_t size = bitset_size(p);
    bitset_fill(p, 1);
    /* index 1 and 2 -> in reality will be 0 and 1 -> that's how it's implemented in bitset.h. */
    bitset_setbit(p, 0LU, 0);
    bitset_setbit(p, 1LU, 0);

    for(bitset_index_t i = 2; i < size; i+=2) {
        if(bitset_getbit(p, i) == 1) {
            /* Sets all even numbers to 0 besides 2. */
            bitset_setbit(p, i, 0);
        }
    }

    for(bitset_index_t i = 3; i <= (bitset_index_t) sqrt(size); i+=2) {
        if(bitset_getbit(p, i) == 1) {
            /* n = i*i -> ensures that "n" won't loop thorugh already non-prime numbers (like 2, 3, ...) */
            /* 3 * i is pointless if i was already 3 */
            /* n += i * 2 -> so we skip over even numbers. */
            for(bitset_index_t n = i * i; n < size; n += i*2) {
                if(bitset_getbit(p, n) == 1) {
                    bitset_setbit(p, n, 0);
                }
            }
        }
    }
}