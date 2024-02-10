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

![image](https://github.com/Harsh2390/Flight-Ticket-Management-System/assets/63357632/67c71c8b-dd2c-44d4-a878-329e1356f83e)






For 100K lines of record with a hash array index size of 100003: 

![image](https://github.com/Harsh2390/Flight-Ticket-Management-System/assets/63357632/d1f17122-5db1-4a3d-9c8d-443fda121a97)







**Results**: For record sizes ranging from 1K to 100K, with corresponding hash table sizes, the polynomial rolling hash function demonstrated an average of 740 collisions, indicating a moderate level of efficiency in collision handling.

### Hash Function 2: Polynomial Hash Function

The hashing function takes a string as input and splits it into four pieces of equal length. Each piece is then converted to an integer value using bit-shifting operations. The hash code is computed by iterating over each piece of the string and using a hash function based on the prime number 31 to weight each piece. The weights decrease for each piece from left to right.
Finally, the hash value is returned modulo the capacity of the hash table, which is the maximum number of indices in the table.

```
unsigned int hash = 0;
    int a = 31; // a prime number for the hash function
    int m = 4; // Number of pieces to split key into
    int n = key.length(); // length of key
    int k = n / m; // length of each piece

    //split key into pieces and cast each into int
    for (int i = 0; i < k; i++) {
        uint64_t piece = 0;
        for (int j = i*m; j<(i + 1)*m; j++) {
            piece = (piece << 8) | key[j];
        }
        hash += piece *pow(a,m-i-1);
    }

    // Handle the last piece
    uint64_t lastPiece = 0;
    int j = k * m;
    int shift = 0;
    while (j < n) {
        lastPiece |= key[j] << shift;
        j++;
        shift += 8;
    }
    hash += lastPiece * pow(a, 0);

    return hash % this->capacity;

```
For 1K lines of record with a hash array index size of 1003:

![image](https://github.com/Harsh2390/Flight-Ticket-Management-System/assets/63357632/54504331-7a81-414c-a94f-9550cbe1ce38)





For 10K lines of record with a hash array index size of 10003: 


![image](https://github.com/Harsh2390/Flight-Ticket-Management-System/assets/63357632/e8fe5db3-5d51-46e7-a0bc-b8a01e5145d3)





For 100K lines of record with a hash array index size of 100003: 


![image](https://github.com/Harsh2390/Flight-Ticket-Management-System/assets/63357632/6a1db861-69c1-4fa4-9491-2bb70b55cdc6)


**Results**: With the same record and hash table sizes, the polynomial hash function showed an average of 12,889 collisions, suggesting a higher collision rate compared to the rolling hash function.

### Hash Function 3: Cycle Shift Hash Function

The hash code is computed using a simple algorithm that iterates over each character in the input string. For each character, the function first performs a cyclic shift of the current hash value by 5 bits to the left and then performs a bitwise OR with the current hash value shifted by 27 bits to the right. This operation essentially multiplies the current hash value by 32 and then performs a cyclic shift to preserve the high-order bits. Next, the function adds the integer value of the current character to the hash value. This step ensures that different strings with different character values produce different hash codes. After iterating over all characters in the string, the function returns the hash value modulo the capacity of the hash table. This ensures that the resulting hash code falls within the valid range of indices in the table.

```
int index = key.length();

    unsigned int hash = 0;

    for (int i = 0; i < index; i++) {
       
        hash = (hash << 5) | (hash >> 27);  // hash * 32 cyclic shift
        hash += (unsigned int)key[i]; // add key[i] to hash

    }
   
    return hash % this->capacity;

```
For 1K lines of record with a hash array index size of 1003:




![image](https://github.com/Harsh2390/Flight-Ticket-Management-System/assets/63357632/354100a3-7145-4293-b280-364722a8217a)




For 10K lines of record with a hash array index size of 10003: 

![image](https://github.com/Harsh2390/Flight-Ticket-Management-System/assets/63357632/2619fddb-9ae0-4ef2-aaa0-74d652ff86ef)






For 100K lines of record with a hash array index size of 100003: 



![image](https://github.com/Harsh2390/Flight-Ticket-Management-System/assets/63357632/91cb75de-73fb-426b-8635-37ac0cc93fcc)




**Results**: The cycle shift hash function resulted in an average of 928 collisions, indicating a better distribution and collision handling than the polynomial hash function but more collisions than the rolling hash function.

### Conclusion

The experiment revealed varying levels of efficiency among the three hash functions. The Polynomial Rolling Hash Function emerged as the most effective in minimizing collisions, followed by the Cycle Shift Hash Function, with the Polynomial Hash Function experiencing the highest number of collisions. These findings highlight the importance of selecting an appropriate hash function for optimizing data storage and retrieval in hash tables.

