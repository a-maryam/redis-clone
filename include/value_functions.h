
#ifndef VALUE_FUNCTIONS_H
#define VALUE_FUNCTIONS_H

struct Value* create_string_value(char* s); // maybe change back to const.
void destroy_string(struct Value* val);
struct Value* copy_string(struct Value* old_value);

#endif // value_functions.h