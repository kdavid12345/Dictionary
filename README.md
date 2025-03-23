# Dictionary Application with Custom Hash Table

## Overview
This project is a **console-based dictionary application** implemented in C++. It uses a **custom-built hash table** to store and manage key-value pairs (words and their translations). The application supports multiple dictionaries, allowing users to add, search, update, delete, and load entries from files. The hash table implementation includes collision handling and dynamic resizing for efficient performance.

---

## Features
- **Custom Hash Table**:
  - Efficient storage and retrieval of key-value pairs.
  - Collision handling using **linear probing**.
  - Dynamic resizing (rehashing) when the load factor exceeds 0.75.
- **Dictionary Operations**:
  - **Add**: Insert a new word and its translation.
  - **Search**: Look up the translation of a word.
  - **Delete**: Remove a word and its translation.
  - **Load from File**: Populate the dictionary from a text file.
  - **List**: Display all entries in the dictionary.
- **Multiple Dictionaries**:
  - Users can create, select, and manage multiple dictionaries.
- **User-Friendly Interface**:
  - Simple console-based menu for interacting with the dictionaries.

---

## Technical Details
- **Hash Function**: A simple hash function is used to map strings to array indices.
- **Collision Handling**: Linear probing is used to resolve collisions.
- **Dynamic Resizing**: The hash table automatically resizes when the load factor exceeds 0.75.
- **File Loading**: Words and translations can be loaded from a text file in the format:

---

## Credits
- Developed as a learning project to practice C++ and data structures.
