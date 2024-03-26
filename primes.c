// primes.c
// Riešenie IJC-DU1, príklad a), 21.03.2024
// Autor: Adam Veselý, FIT
// Preložené gcc version 11.4.0

#include <stdio.h>
#include <time.h>
#include "bitset.h"
#include "eratosthenes.h"

#define N 666000000UL

int main(void) {
    clock_t start = clock();
    bitset_create(p, N);
    // bitset_alloc(p, N);
    eratosthenes(p);
    int count = 0;
    bitset_index_t bits[10] = {0};
    /* Goes until 10 primes have been printed */
    for(bitset_index_t i = N - 1; (i > 1) && (count < 10); i--) {
        if(bitset_getbit(p, i) == 1) {
           bits[count] = i;
           count++; 
        }
    }
    for(count -= 1; count >= 0; count--) {
        printf("%lu\n", bits[count]);
    }
    // bitset_free(p);
    /* Prints the amount of time the program takes. */
    fprintf(stderr, "Time=%.3g\n", (double)(clock() - start) / CLOCKS_PER_SEC);
}
