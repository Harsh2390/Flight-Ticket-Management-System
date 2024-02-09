#ifndef FLIGHT_TICKET_H
#define FLIGHT_TICKET_H
#include<iostream>
using namespace std;

class Flight_Ticket
{
	private:
		string companyName;
		int flightNumber;
		string country_of_origin;
		string country_of_destination;
		string stopOver;
		string price;
		string time_of_departure;
		string time_of_arrival;
		string date;

	public:
		Flight_Ticket(){} //default constructor
		Flight_Ticket(string companyName, int flightNumber, string country_of_origin, string country_of_destination, string stopOver, string price, string time_of_departure, string time_of_arrival, string date);
		bool operator==(Flight_Ticket* data); //overload == operator in order to compare two Flight_Ticket objects and check if they are the same
		void printFlightTicket(); //print the flight ticket in table format
		void printFlightTicket2(); //print the flight ticket in table format

		friend class FlightHASHTABLE;
		friend class HashNode;
		friend class Node;
		friend class MyList;
};

#endif

