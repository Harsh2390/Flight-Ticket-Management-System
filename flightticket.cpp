#include "flightticket.h"

#include<fstream>
using namespace std;

// constructor
Flight_Ticket::Flight_Ticket(string companyName, int flightNumber, string country_of_origin, string country_of_destination, string stopOver, string price, string time_of_departure, string time_of_arrival, string date){
    this->companyName = companyName;
    this->flightNumber = flightNumber;
    this->country_of_origin = country_of_origin;
    this->country_of_destination = country_of_destination;
    this->stopOver = stopOver;
    this->price = price;
    this->time_of_departure = time_of_departure;
    this->time_of_arrival = time_of_arrival;
    this->date = date;
}

// this function is helpful for printing the flight ticket from the hash table and used by many functions such as find, allinday, printASC
void Flight_Ticket::printFlightTicket(){ //print the flight ticket in table format
    cout << "Company Name: " << this->companyName << endl;
    cout << "Flight Number: " << this->flightNumber << endl;
    cout << "Country of Origin: " << this->country_of_origin << endl;
    cout << "Country of Destination: " << this->country_of_destination << endl;
    cout << "Stop Over: " << this->stopOver << endl;
    cout << "Price: " << this->price << endl;
    cout << "Time of Departure: " << this->time_of_departure << endl;
    cout << "Time of Arrival: " << this->time_of_arrival << endl;
    cout << "Date: " << this->date << endl;
}

// this function is helpful for printing the flight ticket from the linked list and used by many functions such as find, allinday, printASC
void Flight_Ticket::printFlightTicket2(){
    
    cout << this->companyName << "," << this->flightNumber << "," << this->country_of_origin << "," << this->country_of_destination << "," << this->stopOver << "," << this->price << "," << this->time_of_departure << "," << this->time_of_arrival << "," << this->date << endl;
    //cout << "Company Name: " << this->companyName << " flight number: " << this->flightNumber << " from " << this->country_of_origin << " to " << this->country_of_destination << " with stop over in " << this->stopOver << " costs " << this->price << " and departs at " << this->time_of_departure << " and arrives at " << this->time_of_arrival << " on " << this->date << endl;
}

// this function is helpful for the Finding the flight ticket in the hash table and also for the function allinday that prints all the flight tickets in a specific date
bool Flight_Ticket::operator==(Flight_Ticket* data){ //overload == operator in order to compare two Flight_Ticket objects and check if they are the same
    if(this->companyName == data->companyName && this->flightNumber == data->flightNumber && this->country_of_origin == data->country_of_origin && this->country_of_destination == data->country_of_destination && this->stopOver == data->stopOver && this->price == data->price && this->time_of_departure == data->time_of_departure && this->time_of_arrival == data->time_of_arrival && this->date == data->date){
        return true;
    }
    else{
        return false;
    }
}