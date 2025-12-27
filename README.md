# Toy Redis
Redis-like in-memory key value store using C. 
It is a learning project that is not feature-complete.
I did not follow a tutorial; my toy redis is built from a simplified, conceptual understanding of what redis does. 

## Implemented Features:
- In-memory key-value store: 
    - hash table implemented using chaining (simple hash function)
    - dynamically allocated
- String key support 
    - keys stored as heap-allocated strings
    - hashes are created from the strings
- Basic command parsing
- Tests started
    - tests for validating core data structures started

## Design: 
- Using C because that's what Redis is written in, and to recall lower level topics such as memory management. 
- Chaining for hashtable collisions: simple for now

## Usage
`SET key value`
`GET key`
`> value`

## Planned 
- RESP-like protocol parsing
- Single client TCP server
- Persistence: snapshot based
- Hashtable resizing / performance enhancements
- Expanded test suite
