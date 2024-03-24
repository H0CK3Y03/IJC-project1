// bitset.h
// Riešenie IJC-DU1, príklad a), 21.03.2024
// Autor: Adam Veselý, FIT
// Preložené gcc version 11.4.0


#include <stdlib.h>
#include <assert.h> /* Need static_assert.*/
#include <limits.h> /* Need CHAR_BIT. */
#include "error.h"

#ifndef BITSET_H
#define BITSET_H

/* BIT_AMOUNT -> amount of bits inside of a single unsigned long
   for a specific architecture */
#define BIT_AMOUNT (CHAR_BIT * sizeof(unsigned long))

// unsigned long -> 32 bits on 32-bit architecture
// unsigned long -> 64 bits on 64-bit architecture
typedef unsigned long* bitset_t;                                                                  \
typedef unsigned long bitset_index_t;                                                             \

#define bitset_create(name, size)                                                                 \
    static_assert(size > 0, "ERROR: bitset_create: Invalid size.\n");                             \
    /* Calculates how many unsigned long indices we need to satisfy                               \
       the amount of bits in size + another index to store the size in.                           \
       Then assigns the first index [0] with the size of the array in bits. */                    \
    bitset_index_t name[(size / BIT_AMOUNT) + 1] = {size, };                                      \

#define bitset_alloc(name, size)                                                                  \
    static_assert(size > 0, "ERROR: bitset_alloc: Invalid size.\n");                              \
    bitset_t name = malloc((size / BIT_AMOUNT) + 1);                                        \
    static_assert(name != NULL, "ERROR: bitset_alloc: Unable to allocate memory for array.\n");   \
    bitset_fill(name, 0);                                                                         \
    name[0] = size;                                                                               \

/* ---------------------- MACROS ---------------------- */

#ifndef USE_INLINE

#define bitset_free(name)                                                                         \
    if(name != NULL) {                                                                            \
        free(name);                                                                               \
        name = NULL;                                                                              \
    }                                                                                             \

#define bitset_size(name)                                                                         \
    name[0]                                                                                       \

#define bitset_fill(name, bit)                                                                    \
    static_assert(bit >= 0, "ERROR: bitset_fill: Invalid bit value\n");                           \
    bitset_index_t index_amount = (name[0] / BIT_AMOUNT) + 1;                                     \
    for(bitset_index_t index = 1; index < index_amount; index++) {                               \
        /* Sets all bits to 1 (~(0LU)) or to 0 for all indices. */                                \
        name[index] = bit ? ~(0LU) : 0;                                                           \
    }

#define bitset_setbit(name, index, bit)                                                           \
    static_assert(bit >= 0, "ERROR: bitset_setbit: Invalid bit value\n");                         \
    if(index >= bitset_size(name)) {                                                              \
        error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu\n", index, bitset_size(name));    \
    }                                                                                             \
    if(bit) {                                                                                     \
        /* First gets the index, where the bit is located (given by index),                       \
           then performs a bitwise shift to the left and a bitwise                                \
           "or" assignment operation (|=) with the number 1                                       \
           moved by the bit location (index % BIT_AMOUNT).                                        \
           This ensures that only the specified bit will be set to 1. */                          \
        name[(index / BIT_AMOUNT) + 1] |= (1LU << (index % BIT_AMOUNT));                          \
    }                                                                                             \
    else {                                                                                        \
        /* Gets index and shifts the number 1 to the left appropriately,                          \
           inverts the shifted number (0->1, 1->0) and performs                                   \
           a bitwise "and" assignment operation.                                                  \
           This insures that only the specified bit will be set to 0. */                          \
        name[(index / BIT_AMOUNT) + 1] &= ~(1LU << (index % BIT_AMOUNT));                         \
    }

#define bitset_getbit(name, index)                                                                \
    /* Position_value is the value of the index where the specified bit is located.               \
       bit_value will be set to 0 or 1.                                                           \
       Bit shifts position_value to the right by the amount that is specified in index.           \
       Then compares the LSB with 1 (performs a bitwise "and" operation), gets 0 or 1. */         \
    ((index <= 0 || index > bitset_size(name))                                                    \
    ? (error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu\n", index, bitset_size(name)), 0UL) \
    : ((name[(index / BIT_AMOUNT) + 1] >> (index % BIT_AMOUNT)) & 1LU))

#endif /* MACROS */

/* ---------------------- INLINE ---------------------- */

#ifdef USE_INLINE

inline void bitset_free(bitset_t name) {
    if(name != NULL) {
        free(name);
        name = NULL;
    }
}

inline bitset_index_t bitset_size(bitset_t name) {
    return name[0];
}

inline void bitset_fill(bitset_t name, bitset_index_t bit) {
    if(bit > 0 && bit <= bitset_size(name)) {
        error_exit("ERROR: bitset_fill: Invalid bit value\n");
    }
    bitset_index_t index_amount = (name[0] / BIT_AMOUNT) + 1;
    for(bitset_index_t index = 1; index <= index_amount; index++) {
        name[index] = bit ? ~(0) : 0;
    }
}

inline void bitset_setbit(bitset_t name, bitset_index_t index, bitset_index_t bit) {
    if(index > bitset_size(name)) {
        error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu\n", index, bitset_size(name));
    }
    if(bit) {
        name[(index / BIT_AMOUNT) + 1] |= (1LU << (index % BIT_AMOUNT));
    }
    else {
        name[(index / BIT_AMOUNT) + 1] &= ~(1LU << (index % BIT_AMOUNT));
    }
}

inline bitset_index_t bitset_getbit(bitset_t name, bitset_index_t index) {
    if(index > bitset_size(name)) {
        error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu\n", index, bitset_size(name));
    }
    bitset_index_t position_value = name[(index / BIT_AMOUNT) + 1];
    return (position_value >> (index % BIT_AMOUNT)) & 1;
}

#endif /* USE_INLINE */

#endif /* BITSET_H */