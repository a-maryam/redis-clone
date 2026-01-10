// read.c
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/read.h"

/* read does NOT own line */
char* read_input() {
    int line_length = 100;
    char* line = malloc(line_length + 1 * sizeof(*line));
    
    if(line == NULL) {
        return NULL;
    }

    // will need to implement error handling for invalid inputs
    if(fgets(line, line_length, stdin) == NULL) {
        free(line);
        return NULL;
    } 
    else {
        line[strcspn(line, "\n")]='\0';
    }
    return line; // seems correct
} 