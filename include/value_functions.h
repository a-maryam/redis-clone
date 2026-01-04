
#ifndef VALUE_FUNCTIONS_H
#define VALUE_FUNCTIONS_H

struct Value* create_string_value(const char* s);
void destroy_string(struct Value* val);
struct Value* copy_string(struct Value* old_value);
//Value* create_int_value(int x);


#endif // value_functions.h