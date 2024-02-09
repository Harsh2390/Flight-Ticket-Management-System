# Experiment Report

## Evaluation of Three Different Hash Functions

Author: Harsh Sahu

### Overview
This report presents an evaluation of three distinct hash functions used within a flight ticket management system. Each hash function's efficiency and effectiveness in distributing records across a hash table are assessed through a series of tests.

### Hash Function 1: Polynomial Rolling Hash Function

This is an implementation of the Polynomial Rolling Hash algorithm, which is a commonly used hashing algorithm for strings. It uses a polynomial function to generate a hash code for a given string. The hash code is then used to determine the index of the string in the hash table.
The function takes a string key as input and initializes a hash variable to 0. It then iterates over each character in the string and calculates a polynomial function using the current character, a prime number (p = 31), and a variable (p_pow) that is used to calculate the polynomial. The hash variable is then updated by adding the value of the polynomial function for each character. Once the loop has been completed, the absolute value of the hash is taken and modulo'd by the capacity of the hash table. This resulting value is the index at which the string should be stored in the hash table.
```
const int p = 31;
    int hash = 0;
    int n = key.length();
    int p_pow = 1;

    // Polynomial rolling hash
    for (int i = 0; i < n; i++) {
        hash += (key[i] - 'a' + 1) * p_pow;
        p_pow *= p;
    }

    return abs(hash) % capacity;

```
For 1K lines of record with a hash array index size of 1003:

![image](https://github.com/Harsh2390/Flight-Ticket-Management-System/assets/63357632/d62735f8-8391-40b7-9fe8-6ccf514a9584)





For 10K lines of record with a hash array index size of 10003: 







For 100K lines of record with a hash array index size of 100003: 








**Results**: For record sizes ranging from 1K to 100K, with corresponding hash table sizes, the polynomial rolling hash function demonstrated an average of 740 collisions, indicating a moderate level of efficiency in collision handling.

### Hash Function 2: Polynomial Hash Function

This function splits a string into equal-length pieces, converting each to an integer value using bit-shifting. A hash code is computed by weighting each piece with a prime number-based hash function. The aim is to balance complexity and distribution efficiency.

**Results**: With the same record and hash table sizes, the polynomial hash function showed an average of 12,889 collisions, suggesting a higher collision rate compared to the rolling hash function.

### Hash Function 3: Cycle Shift Hash Function

Utilizes a cyclic shift and character addition method to produce hash codes. This approach ensures that different strings result in distinct hash codes, ideally leading to a uniform distribution across the hash table.

**Results**: The cycle shift hash function resulted in an average of 928 collisions, indicating a better distribution and collision handling than the polynomial hash function but more collisions than the rolling hash function.

### Conclusion

The experiment revealed varying levels of efficiency among the three hash functions. The Polynomial Rolling Hash Function emerged as the most effective in minimizing collisions, followed by the Cycle Shift Hash Function, with the Polynomial Hash Function experiencing the highest number of collisions. These findings highlight the importance of selecting an appropriate hash function for optimizing data storage and retrieval in hash tables.

