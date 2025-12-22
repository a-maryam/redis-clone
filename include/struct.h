/* struct.h 
Purpose: so far hold structs used at the heart of the key-value store
*/

// key will be char[] 

typedef enum {
    VALUE_FLOAT;
    VALUE_CHAR;
    VALUE_DOUBLE;
    VALUE_INT;
    VALUE_INT_PTR;
    VALUE_CHAR_PTR;
} ValueType;

// union must hold pointers.
typedef struct {
    enum ValueType value;
    union {
        float f;
        char c; 
        double d;
        int i;
        int *arr_ptr; // will be dynamically allocated and live on heap
        int *char_ptr;
        // create structs for other data types later
        // lists, heaps, trees...
    } Value
} Value
