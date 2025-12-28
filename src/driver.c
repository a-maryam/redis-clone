/* driver.c: main of program*/
#include "../include/parser.h"
#include "../include/read.h"
#include "../include/struct.h"
#include "../include/commands.h"
#include "../include/hash_table.h"
#include <stdio.h>

int main(void) {
    struct Arguments* a1 = parse(read());
    struct hash_table* kv_store = create_table();

    // command loop logic: 
    // oh yeah it's not a loop yet haha -- going to have to keep waiting for input /
    switch(a1->command) {
        case CMD_SET:
            set(kv_store, a1);
            break;
        case CMD_GET:
            get(kv_store, a1->key);
            break;
        case CMD_DEL:
            del(kv_store, a1);
            break;
        case CMD_EXISTS:
            exists(kv_store, a1);
            break;
        case CMD_UNKNOWN:
            printf("Unknown command."); // should likely exit program.
            break;
        default:
            printf("Unusual program behavior"); // this case should never occur.
            break; // exit program?
    }
    
    free_arg_struct(a1);
    free_hash_table(kv_store);
    return 0;
}