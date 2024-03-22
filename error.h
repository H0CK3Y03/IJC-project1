// error.h
// Riešenie IJC-DU1, príklad b), 21.03.2024
// Autor: Adam Veselý, FIT
// Preložené gcc version 11.4.0

#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>

void warning(const char *fmt, ...);
void error_exit(const char *fmt, ...);

#endif /* ERROR_H */