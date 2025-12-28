// read.c
#include <stdlib.h>
#include <stdio.h>
#include "../include/read.h"


char* read() {
    int line_length = 100;
    char* line = malloc(line_length * sizeof(*line));

    if(line == NULL) {
        //printf("Memory allocation for line failed\n");
        return NULL;
    }

    
    // will need to implement error handling for invalid inputs
    if(fgets(line, line_length, stdin) == NULL) {
        free(line);
        return NULL;
    } 
    else {
        printf("Entered: %s", line); // for test purposes
    }
    return line; // seems correct
} 