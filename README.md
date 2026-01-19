# Toy Redis
Redis-like in-memory key value store using C. 
It is a learning project that is not feature-complete.
I did not follow a tutorial; my toy redis is built from a simplified, conceptual understanding of what redis does. 

## Implemented Features
- In-memory key-value store: 
    - hash table implemented using separate chaining (simple hash function), handles collisions
    - dynamically resizes 
    - safe deletion for linkedlist buckets in table
- Wrote a value abstraction that can support different data: currently only implemented functions for strings, but it is easily extensible 
    - keys stored as heap-allocated strings
    - hashes are created from the strings
- Interactive command loop supporting SET/GET/DEL
- Tests written for core command functions and collisions
- In-progress: Server over TCP sockets, with Node.js as a client, submitting commands to the key value store [Postponed]

## Bugs / Pitfalls
- Triggered invalid reads in Valgrind by traversing linked list incorrectly, assumed a node existed when it didn't, used freed memory
- Copied buckets directly into new table in resize when they were supposed to be rehashed  
- Revising the difference between ** and * - needed ** to resize my table
- Early on, had a lack of clarity about memory ownership rules
- When resizing we reinsert the new values, and at first I wrote it so that it was possible to trigger a resize in the middle of a resize which would have been bad. 
- Realized the memory ownership rule I set for parse caused problems when it came to implementing the TCP server - adjusted it to not take ownership of read buffer

## Process
- Debugged invalid memory access and memory leaks with Valgirind
- Wrote all functions just to support strings at first, and then adjusted for Value abstraction. Ultimately, the hashtable functions only needed minor adjustments to support the abstraction

## Memory Ownership Rules 
- Hashtable owns all inserted values, but if there is an error in any intermediary function, that function becomes responsible for releasing that memory. 
- Argument struct is owned by driver. Freed before exit. 
- Parser owns tokenized input.

## Design 
- Using C because that's what Redis is written in, and to recall lower level topics such as memory management. 
- Chaining for hashtable collisions: simple for now
- Made two entry points for insert: one for regular and one for resizing. I needed to avoid recursive resizing. There is one internal insert instead of using flags for code clarity

## Usage
```
// Set string value
SSET key value

GET key
// prints result
value

DEL key
```

## Planned [Postponed]
- RESP-like protocol parsing
- Persistence: snapshot based
- Continually expanding test suite
- Hashtable shrink
