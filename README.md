# Flight-Ticket-Management-System


## Project Overview

The Flight-Ticket Management System is a sophisticated application designed to manage flight ticket data efficiently. It leverages a custom hash table implementation for fast data access and manipulation, providing features such as search, add, delete, and export functionalities for flight ticket records. This system showcases the application of object-oriented programming principles and manual implementation of complex data structures in C++.

## Key Features

- **Efficient Data Management**: Uses a hash table for optimized data storage and retrieval.
- **Flexible Search Functionality**: Allows searching for ticket records based on various criteria.
- **Custom Hash Functions**: Implements several hash functions to minimize collisions and enhance performance.
- **Data Export and Import**: Supports exporting and importing ticket records in CSV format for easy data exchange.

## Detailed Description

### Hash Table Implementation

The core of the system is a hash table designed to handle collisions using separate chaining. This custom implementation ensures efficient data management and retrieval.

## Features and Implementation

### Hash Table with Separate Chaining
- **Functionality**: Manages collisions through linked lists, allowing multiple records at the same index.
- **Code Reference**: See `flighthashtable.h` and `flighthashtable.cpp` for the class definition and methods for inserting, searching, and deleting records.

### Dynamic Hash Functions
- **Functionality**: Utilizes several hash functions to ensure optimal data distribution and minimize collisions.
- **Code Reference**: Implementation details can be found in `flighthashtable.cpp`, illustrating the use of Polynomial Rolling Hash, Polynomial Hash, and Cycle Shift Hash functions.

### Ticket Record Management (Add, Search, Delete)
- **Functionality**: 
  - **Add**: Inserts new flight ticket records.
  - **Search**: Retrieves records by criteria like flight number or destination.
  - **Delete**: Removes records from the hash table.
- **Code Reference**: Operations are implemented in `flighthashtable.cpp`, leveraging structures defined in `flightticket.h` and `flightticket.cpp`.

### CSV Export and Import
- **Functionality**: Supports exporting the hash table to CSV for backup/analysis and importing data from CSV files.
- **Code Reference**: `exportToCSV` and `importFromCSV` functions in `flighthashtable.cpp` manage file operations and data parsing.

### Collision Counting and Analysis
- **Functionality**: Offers analysis on the efficiency of hash functions through collision counting.
- **Code Reference**: Collision analysis is conducted within `flighthashtable.cpp`, with dedicated methods for counting and reporting collisions.


## Hash Function Explanation

The `FlightHASHTABLE::hashCode(string key)` method is pivotal for mapping flight ticket keys to indexes in the hash table. This method implements four distinct hash functions, providing flexibility and efficiency in data storage and retrieval. Here's a brief overview of each:

### 1. Polynomial Rolling Hash Function
- **Principle**: Calculates hash values by iterating over the string and multiplying each character's ASCII value (adjusted by subtracting 'a' and adding 1) by a power of 31. This approach accumulates the weighted sum of the characters.
- **Usage**: This function is particularly effective for distributing strings evenly across the hash table, minimizing collisions.

### 2. Polynomial Hash Function
- **Principle**: Similar to the rolling hash but splits the key into pieces, processes each segment, and then combines their values. It uses a prime number base (31) and handles each segment by its ASCII values.
- **Usage**: Offers a balanced compromise between complexity and distribution efficiency.

### 3. Cycle Shift Hash Function
- **Principle**: Employs cyclic shifting of hash values combined with the addition of each character's ASCII value. This method ensures that each character influences the hash value distinctly.
- **Usage**: Provides robustness against patterns in the input data, ensuring a uniform distribution.

### 4. Summation Hash Function
- **Principle**: A straightforward approach that sums the ASCII values of the characters in the key. The sum is then modulated by the capacity of the hash table.
- **Usage**: While simple, it's effective for short strings and offers quick computation.

Each of these hash functions has been carefully chosen to optimize the efficiency and performance of the Flight-Ticket Management System, ensuring fast access and manipulation of ticket records.

These functions are implemented to optimize the hash table's efficiency, ensuring quick access to and manipulation of ticket records.

## Installation

To install and run the Flight-Ticket Management System:

1. Clone the repository.
2. Compile the source files using the provided makefile:
   ```bash
   make all
