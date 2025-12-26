# Questions to guide implementation

1. what kinds of values would redis store: string, integer, linkedlists, hashmaps, characters, heaps, trees

2. will the value be heap allocated? if i malloc, calloc, or realloc it, yes. if it is allocated on the stack no - it is up to how it is allocated. 

3. who is responsible for freeing the memory? -- common patterns from Search:

Function allocates, caller frees: A common pattern is for a function to return a pointer to newly allocated memory, with the clear understanding that the caller is responsible for calling free() when they are finished with it.
Example: The standard strdup() function is an example of this, where you must free the returned string yourself.

Caller allocates, function frees: Less common, but possible, a function might take a pointer as an argument, use the data, and then free it internally before returning 

Caller allocates, function does not free: Most frequently, a function takes a pointer, uses the data temporarily (e.g., reads from it), and returns without modifying the memory management status. The original owner (the caller) retains responsibility. 

4. Can a value change type after creation? I don't really know. It would only make sense for compatible values. I guess in that case sure, but probably not in high priority of things to implement.

5. Value sharing? 