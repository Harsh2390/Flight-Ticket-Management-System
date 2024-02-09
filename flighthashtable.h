#ifndef FlightHASHTABLE_H
#define FlightHASHTABLE_H
#include<iostream>
#include "flightticket.h"
#include<fstream>
#include<sstream>
#include<cmath>

const int hasharrylength = 100003; //length of the hash array

// bool isPrime(int n)
// {
//     if (n <= 1)
//         return false;

//     for (int i = 2; i <= sqrt(n); i++)
//     {
//         if (n % i == 0)
//             return false;
//     }

//     return true;
// }

// int closestPrime(int n)
// {
//     int i = n;
//     while (!isPrime(i))
//     {
//         i++;
//     }
//     return i;
// }

// include additional header files as needed

using namespace std;

class HashNode
{
	private:
		string key; // key = companyName+','+flightNumber
		Flight_Ticket value;
	public:
		HashNode(){} //default constructor for the HashNode class as required by the MyList class
		HashNode(string key, Flight_Ticket value) //constructor
		{
			this->key = key;
			this->value = value;
		}
		friend class FlightHASHTABLE; //friend class
		friend struct Node; //friend struct from MyList class
};
//=============================================================================
// Data type for the MyList class (HashNode) it is easier to change the data type this way.
// You can change the data type to whatever you want by changing the typedef statement below.
// the implementation is easier this way. as per lecture 6 slide 11
typedef HashNode Data; 
class MyList{ //doubly linked list class
	public:
		
		struct Node{ //nested struct for node
			Data data;
			Node* prev;
			Node* next;
			Node(): next(NULL), prev(NULL){} //default constructor
			Node(Data): data(data), next(NULL), prev(NULL){}
		};

	
		// reference for the iterator class: lab 8 assignment
		class Iterator{  	//nested class for iterator which is used to traverse the list
			private:
				Node* ptr; 	//pointer to point to the current node in the list
			public:
				Iterator(Node* p){ 	//constructor
					ptr = p;
				}

				Iterator& operator++(){   	//overload operator ++ for prefix increment
					ptr = ptr->next;
					return *this;
				}

				Iterator& operator--(){		//overload operator -- for prefix decrement
					ptr = ptr->prev;
					return *this;
				}

				Data& operator*(){ 		//overload operator * for dereferencing
					return ptr->data;
				}

				bool operator==(const Iterator& other) const{  //overload operator == for equality
					return ptr == other.ptr;
				}

				bool operator!=(const Iterator& other) const{ 	//overload operator != for inequality
					return ptr != other.ptr;
				}
				friend class FlightHASHTABLE;
				friend class MyList;
		};

	private:
		Node* head; //pointer to the head of the list
		Node* tail; //pointer to the tail of the list
		int size; //size of the list

	public:
		MyList(); //default constructor
		~MyList(); //destructor
		void erase(const Iterator& x); //erase a node from the list
		int getSize() const; //return the size of the list
		void addBefore(const Iterator& x, const Data& data); //add a node before a given node
		void push_back(const Data& data); //add a node to the end of the list
		Iterator begin() const{ //return an iterator to the head of the list
			return Iterator(head->next);
		}
		Iterator end() const{ //return an iterator to the tail of the list
			return Iterator(tail);
		}
		Data& operator[](int index); //overload operator [] to access a node in the list

		// all method above are implemented utilizing the class slides

	
		
};
//=============================================================================
class FlightHASHTABLE //HashTable class
{
	private:
		MyList *buckets;		//List of Buckets, Please create your own Linked List Class called MyList
		int size;					    //Current Size of HashTable
		int capacity;				    // Total Capacity of HashTable
		int collisions;				    //Total Collisions in HashTable
		int hasharraycode[hasharrylength];	//Array to store the hashcode of the keys
	public:
		
		FlightHASHTABLE();						//constructor
		~FlightHASHTABLE();						//destructor
		long hashCode(string key); 						//implement and test different hash functions 
		int importCSV(string path); 			//Load all the flight-tickets from the CSV file to the HashTable
		int exportCSV(string path); 			//Export all the flight-tickets from the HashTable to a CSV file
		int count_collisions();					//return the number of collisions in the HashTable
		int add(Flight_Ticket* data);			//add new flight to the HashTable
		bool searchfor(Flight_Ticket *data);	//search for a flight in the HashTable and return true if found, this is helper function.
		void removeRecord (string companyName, int flightNumber);	//Delete a record with key from the hashtable
		void find(string companyName, int flightNumber);		//Find and Display records with same key entered 
		void allinday(string date);  					//Find and Display records with same day entered
		friend class Flight_Ticket; //friend class
		void printASC(string companyName, int flightNumber);  		//display the collisions for the entered key in an ascending order 
		int getSize();							//return the size of the hashtable
		

			
};


//============================================================================

#endif


