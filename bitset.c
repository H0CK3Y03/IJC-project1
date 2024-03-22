// bitset.c
// Riešenie IJC-DU1, príklad a), 21.03.2024
// Autor: Adam Veselý, FIT
// Preložené gcc version 11.4.0

#include "bitset.h"

#ifdef USE_INLINE

extern void bitset_free(bitset_t name);
extern bitset_index_t bitset_size(bitset_t name);
extern void bitset_fill(bitset_t name, bitset_index_t bit);
extern void bitset_setbit(bitset_t name, bitset_index_t index, bitset_index_t bit);
extern bitset_index_t bitset_getbit(bitset_t name, bitset_index_t index);

#endif /* USE_INLINE */