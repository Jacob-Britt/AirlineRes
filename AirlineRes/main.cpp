

#include <iostream>
#include <string>
#include <fstream>

//menu function - logan
//add new passenger check for seat availability if not print message saying flight is full add to waitlist if user want to be added to second class instead if seat avalible  - danny
//waitlist function - logan
//print boarding pass to txt file BoardingPass.txt - jacob
//function to make sure seat is not taken - danny

using namespace std;

struct passenger
{
	string firstName;
	string lastName;
	string birthDate;
	string seatNumber;
	string seatLevel;
};

passenger passengerArray[10];


int main() {
	int classLevel;
	// Diplays menu and asks user for seat level
	cout << "Welcome to Interesting name Airline" << endl;
	cout << "We aim to give you a better Flight Experience" << endl;
	cout << "Please input 1 for First class or 2 for Economy: " << endl;
	cin >> classLevel;
	// Checks what level the user inputs
	if (classLevel == 1) {
		// Head to function that deals with assigning seats for First Class
	}
	else if (classLevel == 2) {
		// Head to function that deals with assigning seats for Economy
	}
	else {
		cout << "That is not a valid seat level";
	}

}

// Function to print out the boarding pass into the file
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

// Print out the boarding pass into a waitlist file if the user would like to be added to waitlist
static int waitlist(passenger* passengerArray, int size) {
	ofstream outFile;
	outFile.open("waitlist.txt");
	if (outFile.fail())
	{
		cout << "Error opening file" << endl;
		exit(1);
	}
	for (int i = 0; i < size; i++)
	{
		outFile << "Name: " << passengerArray[i].firstName << " " << passengerArray[i].lastName << endl;
		outFile << "Birthdate: " << passengerArray[i].birthDate << endl;
		outFile << "Seat Level: " << passengerArray[i].seatLevel << endl;
		outFile << endl;
	}
	outFile.close();
	cout << "Next flight leaves in 3 hours";
	return 0;
}