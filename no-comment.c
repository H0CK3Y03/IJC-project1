// no-comment.c
// Riešenie IJC-DU1, príklad b), 21.03.2024
// Autor: Adam Veselý, FIT
// Preložené gcc version 11.4.0

#include <stdio.h>
#include "error.h"
// the current character / case
enum state {initial, forward_slash1, forward_slash2,
            star1, star2, double_quote, backslash_double,
            single_quote, backslash_single};

int main(int argc, int **argv) {
    // file / stdin handling
    FILE *file = NULL;

    if(argc == 2) {
        file = fopen(argv[1], "r");
        if(file == NULL) {
            error_exit("Error: Unable to open file.");
        }
    }
    else if(argc == 1){
        file = stdin;
    }
    else {
        error_exit("Error: Wrong amount of arguments.");
    }
    // Finite-state machine
    int c;
    int state = initial;
    while (c = getc(file) != EOF) {
        switch(state) {

            case initial:
                if(c == '/') {
                    state = forward_slash1;
                }
                else if(c == '"') {
                    state = double_quote;
                }
                else if(c == '\'') {
                    state = single_quote;
                }
                else {
                    putchar(c);
                }
                break;

            case forward_slash1:
                if(c == '/') {
                    state = forward_slash2;
                }
                else if(c == '*') {
                    state = star1;
                }
                else {
                    putchar('/');
                    putchar('c');
                }
                break;

            case forward_slash2:
                if(c == '\n') {
                    putchar(c);
                    state = initial;
                }
                else {
                    putchar(c);
                }
                break;

            case star1:
                if(c == '*') {
                    state = star2;
                }
                else {
                    putchar(c);
                }
                break;
            
            case star2:
                if(c == '*') {
                    putchar(c);
                }
                else if(c == '/') {
                    putchar(' ');
                    state = initial;
                }
                else {
                    putchar('*');
                    putchar(c);
                    state = star1;
                }
                break;

            case double_quote:
                if(c == '\\') {
                    state = backslash_double;
                }
                else if(c == '"') {
                    state = initial;
                }
                else {
                    putchar(c);
                }
                break;

            case backslash_double:
                if(c == '\\' || c == '"') {
                    putchar(c);
                    state = double_quote;
                }
                else {
                    putchar(c);
                    // debatable here
                }
                break;

            case single_quote:
                if(c == '\\') {
                    state = backslash_single;
                }
                else if(c == '\'') {
                    state = initial;
                }
                else {
                    putchar(c);
                }
                break;
            
            case backslash_single:
                if(c == '\'' || c == '\\') {
                    putchar(c);
                    state = single_quote;
                }
                else {
                    putchar(c);
                    // debatable here, maybe \c should work
                }
                break;
            
            default:
                exit_error("Error: Something wrong with finite-state machine.");
        }
    }

    return 0;
}