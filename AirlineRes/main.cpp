//airline reservation system capacity 10 seats 

#include <iostream>
#include <string>
#include <fstream>

using namespace std;



//struct for passenger seat level, economy or first class, first, birthdate, last name , seat number - jacob
struct passenger
{
	string firstName;
	string lastName;
	string birthDate;
	string seatNumber;
	string seatLevel;
};

//passenger array - jacob
passenger passengerArray[10];

//function prototypes - jacob
static int printBoardPass(passenger* passengerArray, int size);


//functions

//menu function - logan
//add new passenger check for seat availability if not print message saying flight is full add to waitlist if user want to be added to second class instead if seat avalible  - danny
//waitlist function - logan

//print boarding pass to txt file BoardingPass.txt  boarding pass contains full name birthdate assign seat 1-5 for first class 6-10 economy for - jacob
static int printBoardPass(passenger* passengerArray, int size)
{
	ofstream outFile;
	outFile.open("BoardingPass.txt");
	if (outFile.fail())
	{
		cout << "Error opening file" << endl;
		exit(1);
	}
	for (int i = 0; i < size; i++)
	{
		outFile << "Name: " << passengerArray[i].firstName << " " << passengerArray[i].lastName << endl;
		outFile << "Birthdate: " << passengerArray[i].birthDate << endl;
		outFile << "Seat Number: " << passengerArray[i].seatNumber << endl;
		outFile << "Seat Level: " << passengerArray[i].seatLevel << endl;
		outFile << endl;
	}
	outFile.close();
	return 0;
}



//function to make sure seat is not taken - danny


