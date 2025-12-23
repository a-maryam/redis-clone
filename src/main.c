#include <stdio.h>
#include "../include/struct.h"
// probably have to change from relative to whatever best practice is

int read() {
    char line[100];
    printf("**Toy Redis Started**\n Enter Commands:\n");
    // will need to implement error handling for invalid inputs
    if(fgets(line, sizeof(line), stdin) != NULL) {
        printf("Entered: %s", line);
    } 
    else {
        printf("Error reading input.");
    }
    return 0;
}

int main(void) {
    read();
    return 0;
}