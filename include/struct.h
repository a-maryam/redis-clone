/* struct.h 
Purpose: so far hold structs used at the heart of the key-value store
*/

// key will be char[] 

// union must hold pointers.
union Value {
    float f;
    char c; 
    double d;
    int i;
    int *arr_ptr; // will be dynamically allocated and live on heap
    int *char_ptr;
    // create structs for other data types later
    // lists, heaps, trees...
}