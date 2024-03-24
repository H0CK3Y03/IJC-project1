// error.h
// Riešenie IJC-DU1, príklad b), 21.03.2024
// Autor: Adam Veselý, FIT
// Preložené gcc version 11.4.0

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h> // for exit() function
#include "error.h"

// ... -> ellipsis, variable number of arguments, accessible by the library stdarg.h
void warning(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "Warning: ");
    vfprintf(stderr, fmt, args);
    va_end(args);
}

void error_exit(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "Error: ");
    vfprintf(stderr, fmt, args);
    va_end(args);
    exit(1);
}