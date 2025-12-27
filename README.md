# Toy Redis
Using C
- Redis-like in-memory key value store. 
- implementing data structures
- currently building to support strings and hoping to build support from there 
- Commands intended: SET key value, GET key, DEL key, EXISTS key, EXPIRE key seconds
- Text based protocol: space separated commands (maybe implement RESP in future)
- Planning to implement single client TCP Server
- Hash table implemented
- Planning for persistence: write key/value pairs to file and load back on startup

The first iteration of this project is going to be pretty bare bones.
