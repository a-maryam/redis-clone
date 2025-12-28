// commands.h

#ifndef COMMANDS_H
#define COMMANDS_H
#include "hash_table.h"

char* get(struct hash_table* kv, char* key);
struct hash_table* set(struct hash_table* kv, struct Arguments* arg1);
int del(struct hash_table* kv, struct Arguments* arg1);
int exists(struct hash_table* kv, struct Arguments* arg1);

#endif