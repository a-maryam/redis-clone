// commands.c
#include "../include/commands.h"
#include "../include/hash_table.h"
#include "../include/struct.h"

/* COMMANDS */

struct hash_table* set(struct hash_table* kv, struct Arguments* arg1) {
    return insert(kv, arg1);
}

char* get(struct hash_table* kv, char* key) {
    return get_value(kv, key);
}

int del(struct hash_table* kv, struct Arguments* arg1) {
   
    return 0;
}

int exists(struct hash_table* kv, struct Arguments* arg1) {
    
    return 0;
}
