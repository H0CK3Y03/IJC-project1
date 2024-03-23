// eratosthenes.c
// Riešenie IJC-DU1, príklad a), 21.03.2024
// Autor: Adam Veselý, FIT
// Preložené gcc version 11.4.0

#include <stdio.h>
#include <math.h>
#include "bitset.h"
#include "eratosthenes.h"

void eratosthenes(bitset_t p) {
    // 1. mission
    bitset_index_t size = bitset_size(p);
    bitset_fill(p, 1);
    bitset_setbit(p, 0, 0);
    bitset_setbit(p, 1, 0);

    for(bitset_index_t i = 2; i <= sqrt(size); i++) {
        if(bitset_getbit(p, i) == 1) {
            /* n = i*i -> ensures that "n" won't loop thorugh already non-prime numbers (like 2, 3, ...) */
            /* 3 * i is pointless if i was already 3 */
            for(int n = i * i; n <= size; n += i) {
                bitset_setbit(p, n, 0);
            }
        }
    }
}