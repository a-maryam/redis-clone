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

## Process
- Debugged invalid memory access and memory leaks with Valgirind
- Wrote all functions just to support strings at first, and then adjusted for Value abstraction. Ultimately, the hashtable functions only needed minor adjustments to support the abstraction

## Design 
- Using C because that's what Redis is written in, and to recall lower level topics such as memory management. 
- Chaining for hashtable collisions: simple for now

## Usage
```
SSET key value
SGET key
> value
SDEL key
```

- S in the commands above is for string value commands

## Planned 
- RESP-like protocol parsing
- Single client TCP server
- Persistence: snapshot based
- Continually expanding test suite
