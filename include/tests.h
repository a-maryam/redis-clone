#ifndef TESTS_H
#define TESTS_H
#include "struct.h"
#include <stdbool.h>

bool test_kv_insert_and_get_value();
bool test_kv_get_value_when_empty();
bool test_kv_insert_collision();

#endif // TEST_H