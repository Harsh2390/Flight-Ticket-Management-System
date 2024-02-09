#include<iostream>
#include<cstdlib>
#include<ctime> // for claculating time used by a function
#include<sstream>
#include "flightticket.h"
#include "flighthashtable.h"

//==========================================================
void listCommands()
{
	cout<<"\n----------------------------------"<<endl;
	cout<<"import <path>      	:Import flight-tickets from a CSV file"<<endl
		<<"export <path>      	:Export flight-tickets to a CSV file"<<endl
		<<"count_collisions   	:Print number of collisions"<<endl
		<<"add                	:Add a new flight-ticket"<<endl
		<<"delete <key>       	:Delete a flight-ticket"<<endl
		<<"find <key>         	:Find a flight-ticket's details"<<endl
		<<"allinday <date>    	:Display all flight-tickets in a day"<<endl
		<<"printASC <key>     	:Print flight-tickets in ascending order"<<endl
		<<"exit               	:Exit the program"<<endl;
}

int main(void)
{
	FlightHASHTABLE myFlightHASHTABLE;
	string command;
	string key;
	string input;
	listCommands();

	while(true)
	{
	
		cout << "===================================="<<endl;
		cout<<">";
		getline(cin >> ws, input);

		stringstream sstr(input);
		getline(sstr, command, ' ');
		getline(sstr, key);

		cout<< "===================================="<<endl;

		if (command == "exit"|| command == "Exit"){
			cout<<"Exiting..."<<endl;
			exit(0);
		}
		else if (command == "add"){
			cout << "Please enter the flight ticket details:" << endl;
			string comname, country, destination, stop, price, date, timeD, timeA;
			int flightnum;

			do {
        		cout << "Company Name: ";
        		getline(cin, comname);
    		} while (comname.empty());
			

			cout << "Flight Number: ";
			while (!(cin >> flightnum)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "Invalid input. Please enter an integer for the flight number: ";
			}				
			// cin >> flightnum;
			cin.ignore();

			do {
        		cout << "Country of Origin: ";
        		getline(cin, country);
    		} while (country.empty());

			

			do {
        		cout << "Country of Destination: ";
        		getline(cin, destination);
    		} while (destination.empty());

			
			do {
        		cout << "Stop Over: ";
        		getline(cin, stop);
				if (stop.find_first_not_of("0123456789") != string::npos) {
					cout << "Invalid stop over. Please try again." << endl;
				}
    		} while (stop.empty()|| stop.find_first_not_of("0123456789") != string::npos);

			do {
        		cout << "Price: ";
        		getline(cin, price);
				if (price.find_first_not_of("0123456789") != string::npos) {
					cout << "Invalid price. Please try again." << endl;
				}
    		} while (price.empty() || price.find_first_not_of("0123456789") != string::npos);

			do {
        		cout << "Time of Departure ";
        		getline(cin, timeD);
				if (timeD.find_first_not_of("0123456789:") != string::npos) {
					cout << "Invalid time. Please try again." << endl;
				}
    		} while (timeD.empty() || timeD.find_first_not_of("0123456789:") != string::npos);

			do {
        		cout << "Time of Arrival: ";
        		getline(cin, timeA);
				if (timeA.find_first_not_of("0123456789:") != string::npos) {
					cout << "Invalid time. Please try again." << endl;
				}
    		} while (timeA.empty() || timeA.find_first_not_of("0123456789:") != string::npos);

			do {
        		cout << "Date: ";
        		getline(cin, date);
    		} while (date.empty());


			Flight_Ticket* newTicket = new Flight_Ticket(comname, flightnum, country, destination, stop, price, timeD, timeA, date);

			int temp = myFlightHASHTABLE.add(newTicket);
			if (temp == 1){
				cout << "Flight Ticket added successfully!" << endl;
			}
			else if (temp == -1){
				cout << "Flight Ticket already exists!" << endl;
			}
			else{
				cout << "Error!" << endl;
			}
		}
		else if (command == "import"){
			
			int start_time = clock();
			int result = myFlightHASHTABLE.importCSV(key);
			int end_time = clock();

			if (result == -1){
				cout << "Error... No records are imported" << endl;
			}
			else{
				cout << result << " records are imported" << endl;
				cout << "Time taken: " << (end_time - start_time) / double(CLOCKS_PER_SEC) * 1000 << " ms" << endl;
			}


		}
		else if (command == "allinday"){
			
			int start_time = clock();
			myFlightHASHTABLE.allinday(key);
			int end_time = clock();

			cout << "Time taken: " << (end_time - start_time) / double(CLOCKS_PER_SEC) * 1000 << " ms" << endl;

		}
		else if (command == "count_collisions"){

			int temp = myFlightHASHTABLE.count_collisions();
			cout << "Number of collisions: " << temp << endl;
		}
		else if (command == "find"){

			istringstream sstr(key);
			string companyName, flightnumstr;

			getline(sstr, companyName, ',');
			getline(sstr, flightnumstr);

			int flightnum = stoi(flightnumstr);

			int start_time = clock();
			myFlightHASHTABLE.find(companyName, flightnum);
			int end_time = clock();

			cout << "Time taken: " << (end_time - start_time) / double(CLOCKS_PER_SEC) * 1000 << " ms" << endl;

		}
		else if (command == "printASC"){

			istringstream sstr(key);
			string companyName, flightnumstr;

			getline(sstr, companyName, ',');
			getline(sstr, flightnumstr);

			int flightnum = stoi(flightnumstr);
			
			int start_time = clock();
			myFlightHASHTABLE.printASC(companyName, flightnum);
			int end_time = clock();

			cout << "Time taken: " << (end_time - start_time) / double(CLOCKS_PER_SEC) * 1000 << " ms" << endl;
		}
		else if (command == "export"){

			int result = myFlightHASHTABLE.exportCSV(key);
			if (result == -1){
				cout << "Error... No records are exported" << endl;
			}
			else{
				cout << result << " records are exported" << endl;
			}
		}
		else if (command == "delete"){

			istringstream sstr(key);
			string companyName, flightnumstr;

			getline(sstr, companyName, ',');
			getline(sstr, flightnumstr);

			int flightnum = stoi(flightnumstr);

			myFlightHASHTABLE.removeRecord(companyName, flightnum);

			
		}
		else if (command == "help"){
			listCommands();
		}
		else{
			cout << "Invalid Command!" << endl;
		}
	}
	return 0;
}

