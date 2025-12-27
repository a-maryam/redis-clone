/* driver.c: main of program*/
#include "../include/parser.h"
#include "../include/read.h"

int main(void) {
    parse(read());
    return 0;
}