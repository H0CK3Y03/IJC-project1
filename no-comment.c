// no-comment.c
// Riešenie IJC-DU1, príklad b), 21.03.2024
// Autor: Adam Veselý, FIT
// Preložené gcc version 11.4.0

#include <stdio.h>
#include "error.h"
// the current character / case
enum state {initial, forward_slash1, forward_slash2,
            star1, star2, double_quote, backslash_double,
            single_quote, backslash_single, backslash_slash};

int main(int argc, char **argv) {
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
    while ((c = getc(file)) != EOF) {
        switch(state) {

            case initial:
                if(c == '/') {
                    state = forward_slash1;
                }
                else if(c == '"') {
                    putchar(c);
                    state = double_quote;
                }
                else if(c == '\'') {
                    putchar(c);
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
                    state = initial;
                }
                break;

            case forward_slash2:
                if(c == '\\') {
                    state = backslash_slash;
                }
                else if(c == '\n') {
                    putchar(c);
                    state = initial;
                }
                else {
                    ;
                }
                break;

            case star1:
                if(c == '*') {
                    state = star2;
                }
                else {
                    ;
                }
                break;
            
            case star2:
                if(c == '*') {
                    ;
                }
                else if(c == '/') {
                    putchar(' ');
                    state = initial;
                }
                else {
                    state = star1;
                }
                break;

            case double_quote:
                if(c == '\\') {
                    state = backslash_double;
                }
                if(c == '"') {
                    putchar(c);
                    state = initial;
                }
                else {
                    putchar(c);
                }
                break;

            case backslash_double:
                putchar(c);
                state = double_quote;
                break;

            case single_quote:
                if(c == '\\') {
                    state = backslash_single;
                }
                if(c == '\'') {
                    putchar(c);
                    state = initial;
                }
                else {
                    putchar(c);
                }
                break;
            
            case backslash_single:
                putchar(c);
                state = single_quote;
                break;

            case backslash_slash:
                if(c == '\\') {
                    ;
                }
                else {
                    state = forward_slash2;
                }
                break;
            
            default:
                error_exit("Error: Something wrong with finite-state machine.");
        }
    }

    if(file != stdin && file != NULL) {
        fclose(file);
    }

    return 0;
}