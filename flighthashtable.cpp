#include "flighthashtable.h"
#include "flightticket.h"
#include<fstream>
#include<cmath>
#include<sstream>
#include<iostream>


using namespace std;



MyList::MyList(){  // constructor
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->prev = head;
    size = 0;
}


MyList::~MyList(){ // destructor
    Node* temp = head;
    while (temp->next != tail) { // loop through the list
        Node* next = temp->next; // set next to temp's next
        delete temp; // delete temp
        temp = next; // set temp to next
    }
}

void MyList::addBefore(const Iterator& x, const Data& data){ // this is the addBefore function which is basically use by push_back function
// other than that, it is not used anywhere else,

    Node* newNode = new Node; // create new node with all the data
    newNode->data = data;

    newNode->prev = x.ptr->prev; // set the new node's prev to x's prev
    newNode->next = x.ptr; // set the new node's next to x
    x.ptr->prev->next = newNode; // set x's prev's next to the new node
    x.ptr->prev = newNode; // set x's prev to the new node
    size++; // increment size
}


void MyList::erase(const Iterator& x){ // this is the erase function which is used to remove a node from the list

    x.ptr->prev->next = x.ptr->next; // set x's prev's next to x's next
    x.ptr->next->prev = x.ptr->prev; // set x's next's prev to x's prev
    delete x.ptr; // delete x
    size--; // decrement size
}


void MyList::push_back(const Data& data){
    addBefore(end(), data); // add data before the end
}

int MyList::getSize() const{
    return size; // return size
}


Data& MyList::operator[](int index){ // this is the overloading operator[] function which is used to access a node in the list
    Node* temp = head; // set temp to head // Node<T>* temp = head;
    for (int i = 0; i < index; i++) { // loop through the list
        temp = temp->next; // set temp to temp's next
    }
    return temp->data; // return temp's data
}


//====================================================================================================
FlightHASHTABLE::FlightHASHTABLE(){ // constructor for FlightHASHTABLE

    buckets = new MyList[hasharrylength]; // create a new list of size hasharrylength
    this->size = 0; // set size to 0
    this->capacity = hasharrylength; // set capacity to hasharrylength
    this->collisions = 0; // set collisions to 0
    for (int i = 0; i < hasharrylength; i++) { // loop through the list
        hasharraycode[i] = -1; // set hasharraycode[i] to -1 (empty)
    }
}

//====================================================================================================
FlightHASHTABLE::~FlightHASHTABLE(){
    delete[] buckets; // delete buckets in order to free up memory
}

//====================================================================================================
int FlightHASHTABLE::getSize(){
    return this->size; // return size
}

//====================================================================================================
int FlightHASHTABLE::count_collisions(){
    return this->collisions; // return collisions
}

//====================================================================================================
long FlightHASHTABLE::hashCode(string key){ // this is the hash function which is used to get the index of the key using the different hash functions.

//------------------------------------------------------------------------------------------------------------
    // hash function 1

    /* This is polynomial rolling hash function which is used to get the index of the key
    we implement the polynomial rolling hash algorithm. In this algorithm, we iterate over the key and for each character, 
    we multiply its corresponding value (ASCII value - 'a' + 1) by p_pow and add it to the hash. 
    We then multiply p_pow by p for the next iteration. 
    This way, the hash value is calculated by adding the products of each character's value with its corresponding power of p. */


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
    
//------------------------------------------------------------------------------------------------------------
    // hash function 2
    // this is polynomial hash function which is used to get the index of the key

    /*unsigned int hash = 0;
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

    return hash % this->capacity; */



//-------------------------------------------------------------------------------------------------------------
    // hash function 3
    //cycle shift hash function sudo code from the book (Data Structures and Algorithms in C++ 2nd Edition)

    
    /* int index = key.length();

    unsigned int hash = 0;

    for (int i = 0; i < index; i++) {
        
        hash = (hash << 5) | (hash >> 27);  // hash * 32 cyclic shift
        hash += (unsigned int)key[i]; // add key[i] to hash

    }
    
    return hash % this->capacity; */

//-------------------------------------------------------------------------------------------------------------
    // hash function 4
    // summation hash function sudo code from the book (Data Structures and Algorithms in C++ 2nd Edition)

    /*unsigned int hash = 0;
    for (int i = 0; i < key.length(); i++) {
        hash += (unsigned int)key[i]; // add key[i] to hash
    }
    int32_t index = hash % this->capacity;
    return index;*/
}

//====================================================================================================
int FlightHASHTABLE::exportCSV(string path){
    ofstream myfile; // opens file
    myfile.open(path, ios::out); // opens file
    if (!myfile.is_open()) { // if file fails to open then exit the function and return -1 which will be used to display an error message in the main function
        cout << "File failed to open" << endl;
        return -1;
    }

    myfile << "companyName" << "," << "flightNumber" << "," << "country_of_origin" << "," << "country_of_destination" << "," << "stopOver" << "," << "price" << "," << "time_of_departure" << "," << "time_of_arrival" << "," << "date" << endl; // write column names to file


    int count = 0; // count is used to count the number of lines of data exported

    for (int i = 0; i < this->capacity; i++) { // loop through the list
        
        if(hasharraycode[i] != -1){ // if hasharraycode[i] is not -1 (empty)
            int index = hasharraycode[i]; // set index to hasharraycode[i]
            MyList::Iterator it = buckets[index].begin(); // create an iterator for the list at index i
            while (it != buckets[index].end()) { // loop through the list
                Flight_Ticket expo = it.ptr->data.value; // set temp to it's data
                
                myfile << expo.companyName << "," << expo.flightNumber << "," << expo.country_of_origin << "," << expo.country_of_destination << "," << expo.stopOver << "," << expo.price << "," << expo.time_of_departure << "," << expo.time_of_arrival << "," << expo.date << endl; // write data to file
                count++; // increment count
                ++it; // increment iterator
            }
        }
        }
    
   

    myfile.close(); // close the file
    return count; // return number of records exported

}

//====================================================================================================
int FlightHASHTABLE::importCSV(string path){ // this is the importCSV function which is used to import data from a csv file

    ifstream myfile(path); // opens file

    // for the increasing the hasharrylength capacity by 1.5 times
    // int linecount = 0; // linecount is used to count the number of lines of data imported
    // string line; // line is used to store each line of data
    // while (getline(myfile, line)) { // loop through the file line by line
    //     linecount++; // increment linecount
    // }
    // int newlength = closestPrime(static_cast<int>(linecount * 1.5)); // set newlength to the closest prime number to linecount * 1.5
    // if (newlength > hasharrylength){
    //     hasharrylength = newlength; // set hasharrylength to newlength
    // }

	if (!myfile.is_open()) { // if file fails to open then exit the function and return -1 which will be used to display an error message in the main function
		cout << "File failed to open" << endl;
		return -1;
	}

	int count = 0; // count is used to count the number of lines of data imported
	string line; // line is used to store each line of data
    getline(myfile, line); // skips the first line (column names) comment out if there is no header in the csv file
// some csv file do have header and some don't, so it is better to comment out this line if there is no header in the csv file
	while (getline(myfile, line)) { // loop through the file line by line
		istringstream ss(line); // creates an input stream for each line

        // declare variables to store each value
		string companyName, flightNumberstr, country_of_origin, country_of_destination, stopOver, price, time_of_departure, time_of_arrival, date; 
		

		// read in each value separated by commas
		if (getline(ss, companyName, ',') && getline(ss, flightNumberstr, ',') && getline(ss, country_of_origin, ',') && getline(ss, country_of_destination, ',')
			&& getline(ss, stopOver, ',') && getline(ss, price, ',') && getline(ss, time_of_departure, ',') && getline(ss, time_of_arrival, ',') && getline(ss, date, ',')) {

			// create a new Flight_Ticket object and set its values
			Flight_Ticket* temp = new Flight_Ticket;
			temp->companyName = companyName;
			temp->flightNumber = stoi(flightNumberstr); // convert flightNumberstr to int
			temp->country_of_origin = country_of_origin;
			temp->country_of_destination = country_of_destination;
			temp->stopOver = stopOver;
			temp->price = price;
			temp->time_of_departure = time_of_departure;
			temp->time_of_arrival = time_of_arrival;
			temp->date = date;
            //temp->printFlightTicket();

			// add the Flight_Ticket object to the hashtable
			this->add(temp); // add the Flight_Ticket object to the hashtable using the add function
			count++;
		}
	}

	myfile.close(); // close file
	return count; // return count
    

}

//====================================================================================================
bool FlightHASHTABLE::searchfor(Flight_Ticket* data){ // this is the searchfor function which is used to search for a Flight_Ticket object in the hashtable

    string key = data->companyName +","+ to_string(data->flightNumber); // create key as per the requirement
    
    int index = hashCode(key); // get the index of the key to search for the entry in the hash table

    if (hasharraycode[index] == -1) { // if the index is empty
        return false; // return false
    }
    else { // if the index is not empty
        MyList::Iterator it = buckets[index].begin(); // create an iterator to iterate through the list
        while (it != buckets[index].end()) { // loop through the list
            if (it.ptr->data.value == data) { // if the data is found
                return true; // return true
            }
            ++it; // increment iterator
        }
        return false; // return false
    }
    
}
//====================================================================================================
int FlightHASHTABLE::add(Flight_Ticket* data){ // this is the add function which is used to add a Flight_Ticket object to the hashtable

    string key = data->companyName +","+ to_string(data->flightNumber); // create key as per the requirement
   

    if (searchfor(data)) { // if the data is already in the hash table
        return -1; // return -1
    }

    int index = hashCode(key); // get the index of the key to add the entry in the hash table
    //cout<<index<<endl;

    if (hasharraycode[index] == -1) { // if the index is empty
        hasharraycode[index] = index; // set the index to the index
        buckets[index].push_back(HashNode(key, *data)); // add the data to the list
        size++; // increment size
        return 1; // return 1
    }
    else { // if the index is not empty
        //buckets[index].push_back(HashNode(key, *data)); // add the data to the list
            MyList::Iterator it = buckets[index].begin(); // create an iterator to iterate through the list
            while (it != buckets[index].end()) { // loop through the list
                if (it.ptr->data.key == key) { // if the data is found
                    buckets[index].push_back(HashNode(key, *data)); // add the data to the list
                    size++; // increment size
                    return 1;
                 }
                else if (it.ptr->data.key != key){
                     buckets[index].push_back(HashNode(key, *data)); // add the data to the list
                     collisions++; // increment collisions
                     size++; // increment size
                     return 1;
                 }
                 ++it; // increment iterator
            }
           
    
       
    }
    
    return 1;
}

//====================================================================================================
void FlightHASHTABLE::removeRecord (string companyName, int flightNumber){

    string key = companyName +","+ to_string(flightNumber); // create key as per the requirement
    int index = hashCode(key); // get the index of the key to search for the entry in the hash table

    int result = 0; // variable for no. of records found

    if (hasharraycode[index] == -1) { // if the index is empty
        cout << "No records found" << endl;
        return;
    }
    else {
        MyList::Iterator it = buckets[index].begin(); // create an iterator to iterate through the list
        while (it != buckets[index].end()){ // loop through the list
            if (it.ptr->data.key == key) { // if the data is found

                result++; // increment result
                
                cout << result << ". "; // print result
                it.ptr->data.value.printFlightTicket2(); // print the data
                
            }
            ++it; // increment iterator
        }
        
    }
    int choice; // variable for the choice of record to delete
    do{ // loop to get the choice of record to delete
        cout << "Enter the record number to delete: ";
        cin >> choice;
        if (choice < 1 || choice > result) {
            cout << "Invalid choice" << endl;
        }
    } while (choice < 1 || choice > result); // loop until the choice is valid

    int count = 1; // variable for no. of records found
    MyList::Iterator it = buckets[index].begin(); // create an iterator to iterate through the list
    while(it != buckets[index].end()){ // loop through the list
        if (it.ptr->data.key == key) { // if the data is found
            
            if (count == choice) { // if the count is equal to the choice
                buckets[index].erase(it); // delete the record
                size--; // decrement size
                break;
                
            }
            ++it; // increment iterator
            count++; // increment count
        }

    }

    cout << "Record at position " << choice << " has been deleted successfully" << endl; // print record not found
    

}	

//====================================================================================================
void FlightHASHTABLE::find(string companyName, int flightNumber){

    string key = companyName +","+ to_string(flightNumber); // create key as per the requirement
    int index = hashCode(key); // get the index of the key to search for the entry in the hash table

    int result = 0; // variable for no. of records found

    if (hasharraycode[index] == -1) { // if the index is empty
        cout << "No records found" << endl; // print no records found
    }
    else { // if the index is not empty
        MyList::Iterator it = buckets[index].begin(); // create an iterator to iterate through the list
        while (it != buckets[index].end()) { // loop through the list
            if (it.ptr->data.key == key) { // if the data is found
                
                result++; // increment result
                //cout << "Record found " << endl; // print record found
                cout << result << ". " << endl; // print result
                it.ptr->data.value.printFlightTicket(); // print the data
                cout<<"---------------------------------"<<endl;

            }
            ++it; // increment iterator
        }
        if (result == 0) { // if no records are found
            cout << "No records found" << endl; // print no records found
        }
    }
    cout << result << " records found" << endl; // print no. of records found

}		

//====================================================================================================
void FlightHASHTABLE::allinday(string date){



    int result = 0; // variable for no. of records found

    for (int i = 0; i < hasharrylength; i++) { // loop through the hash table
        if (hasharraycode[i] != -1) { // if the index is not empty
            int index = hasharraycode[i];
            MyList::Iterator it = buckets[index].begin(); // create an iterator to iterate through the list
            while (it != buckets[index].end()) { // loop through the list
                if (it.ptr->data.value.date == date) { // if the data is found
                    
                    result++; // increment result
                    // cout << "Record found: " << endl; // print record found
                    // cout << result << ". " << endl; // print result
                    it.ptr->data.value.printFlightTicket2(); // print the data
                    // cout<<"---------------------------------"<<endl;

                }
                ++it; // increment iterator
            }
        }
    }
    if (result == 0) { // if no records are found
        cout << "No records found" << endl; // print no records found
    }
    
    cout << result << " records found" << endl; // print no. of records found

}

//====================================================================================================

// function to print the records in ascending order based on the destination country
void FlightHASHTABLE::printASC(string companyName, int flightNumber) {
    string key = companyName + "," + to_string(flightNumber);
    int index = hashCode(key);
    int result = 0;

    Flight_Ticket *temp = new Flight_Ticket[buckets[index].getSize()]; // create a temporary array to store the records
    int tempSize = 0; // variable for the size of the temporary array

    if (hasharraycode[index] == -1) { 
        cout << "No records found" << endl;
    } else {
        MyList::Iterator it = buckets[index].begin(); // create an iterator to iterate through the list
        while (it != buckets[index].end()) { // loop through the list
            if (it.ptr->data.key == key) { // if the data is found
                result++; // increment result
                temp[tempSize++] = it.ptr->data.value; // store the record in the temporary array
            }
            ++it; // increment iterator
        }
        if (result == 0) {
            cout << "No records found" << endl;
        }
    }
    // sort the temporary array using bubble sort
    for (int i = 0; i < tempSize; i++) { // loop through the array
        for (int j = i + 1; j < tempSize; j++) { // loop through the array at the next index
            if (temp[i].country_of_destination > temp[j].country_of_destination) { // if the country of destination at index i is greater than the country of destination at index j
                Flight_Ticket t = temp[i]; // create a temporary variable to store the record at index i
                temp[i] = temp[j]; // set the record at index i to the record at index j
                temp[j] = t; // set the record at index j to the temporary variable
            }
        }
    }

    for (int i = 0; i < tempSize; i++) { // loop through the temporary array in order to print the records
        //cout << i + 1 << ". " << endl;
        temp[i].printFlightTicket2();
        //cout << "---------------------------------" << endl;
    }

    delete[] temp; // free the memory allocated to the temporary array
}

//====================================================================================================

// another alternative function that uses STL vectors and STL sort function to print the records in ascending order based on the destination country
// this function is not used in the program as it uses STL vectors and STL sort function
/*void FlightHASHTABLE::printASC(string companyName, int flightNumber){

    string key = companyName +","+ to_string(flightNumber); // create key as per the requirement

    int index = hashCode(key); // get the index of the key to search for the entry in the hash table
    int result = 0; // variable for no. of records found


    vector<Flight_Ticket> temp; // create a vector to store the data

    if (hasharraycode[index] == -1) { // if the index is empty
        cout << "No records found" << endl; // print no records found
    }
    else { // if the index is not empty
        MyList::Iterator it = buckets[index].begin(); // create an iterator to iterate through the list
        while (it != buckets[index].end()) { // loop through the list
            if (it.ptr->data.key == key) { // if the data is found
                
                result++; // increment result
                temp.push_back(it.ptr->data.value); // add the data to the vector
            }
            ++it; // increment iterator
        }
        if (result == 0) { // if no records are found
            cout << "No records found" << endl; // print no records found
        }
    }
    sort(temp.begin(), temp.end(), [](Flight_Ticket &a, Flight_Ticket &b){return a.country_of_destination<b.country_of_destination;}); // sort the vector

    for (int i = 0; i < temp.size(); i++) { // loop through the vector
        cout << i+1 << ". " << endl; // print the result
        temp[i].printFlightTicket(); // print the data
        cout<<"---------------------------------"<<endl;

    }
    

}
*/