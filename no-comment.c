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
// starting state
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
// when c is the first forward slash
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
// when c is the second forward slash
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
// when c is a star after a forward slash
            case star1:
                if(c == '*') {
                    state = star2;
                }
                else {
                    ;
                }
                break;
// when c is the second star in the multiline comment            
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
// when c is a double quote
            case double_quote:
                if(c == '\\') {
                    state = backslash_double;
                }
                else if(c == '"') {
                    putchar(c);
                    state = initial;
                }
                else {
                    putchar(c);
                }
                break;
// when c is a backslash in a string
            case backslash_double:
                putchar(c);
                state = double_quote;
                break;
// when c is a single quote
            case single_quote:
                if(c == '\\') {
                    state = backslash_single;
                }
                else if(c == '\'') {
                    putchar(c);
                    state = initial;
                }
                else {
                    putchar(c);
                }
                break;
// when c is a backslash in a character (single quotes)
            case backslash_single:
                putchar(c);
                state = single_quote;
                break;
// when c is a backlash in a single line comment 
            case backslash_slash:
                if(c == '\\') {
                    ;
                }
                else {
                    state = forward_slash2;
                }
                break;
// if c is not a valid character
            default:
                error_exit("Error: Something wrong with finite-state machine.\n");
        }
    }
// checks if the file has any errors (unfinished comments, strings...)
    if(state != initial) {
        error_exit("Error: Unfinished comment or string.\n");
    }
// closes the file if data is read from a file
    if(file != stdin && file != NULL) {
        fclose(file);
    }

    return 0;
}