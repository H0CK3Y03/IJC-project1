// bitset.h
// Riešenie IJC-DU1, príklad a), 21.03.2024
// Autor: Adam Veselý, FIT
// Preložené gcc version 11.4.0

#ifndef BITSET_H
#define BITSET_H

#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include "error.h"

typedef unsigned long* bitset_t; \
typedef unsigned long bitset_index_t; \
// check
#define bitset_create(name, size) {                                                  \
    static_assert(size > 0, "ERROR: bitset_create: Invalid size.\n");                \
    unsigned long name[size] = {0};                                                  \
}
// check
#define bitset_alloc(name, size) {                                                   \
    static_assert(size > 0, "ERROR: bitset_alloc: Invalid size");                    \
    unsigned long *name = malloc(sizeof(unsigned long) * size);                      \
    if(name == NULL) {                                                               \
        error_exit("ERROR: bitset_alloc: Unable to allocate memory.\n");             \
    }                                                                                \
}
// should be good
#define bitset_free(name) {                                                          \
    if(name != NULL) {                                                               \
        free(name);                                                                  \
        name = NULL;                                                                 \
    }                                                                                \
}

#define bitset_size(name) {                                                          \

}

#endif BITSET_H