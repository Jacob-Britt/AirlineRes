//airline reservation system capacity 10 seats
// 2024-01-09
// Version 1.0
// Author's: Danny, Logan and Jacob


#include <iostream>
#include <string>
#include <fstream>

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


// Function Prototypes
void countSeatLevels(passenger* passengerArray, int size, int& firstClassCount, int& economyCount);
static int printBoardPass(passenger* passengerArray, int size);
static int waitlist(passenger* passengerArray, int size);

// Function to assign seat to passenger
bool assignSeat(passenger* passengerArray, int size, string seatLevel, passenger newPassenger) {
    for (int i = 0; i < size; i++) {
        if (passengerArray[i].seatLevel.empty()) {
            passengerArray[i] = newPassenger;
            passengerArray[i].seatLevel = seatLevel;
            return true;
        }
    }
    return false;
}

// Function to print out the boarding pass into the file
int main() {
	int classLevel;
	// Diplays menu and asks user for seat level
	cout << "Welcome to Interesting name Airline" << endl;
	cout << "We aim to give you a better Flight Experience" << endl;
	cout << "Please input 1 for First class or 2 for Economy: " << endl;
	cin >> classLevel;
	// Checks what level the user inputs
    if (classLevel == 1 || classLevel == 2) {
    passenger newPassenger;
    cout << "Enter first name: ";
    cin >> newPassenger.firstName;
    cout << "Enter last name: ";
    cin >> newPassenger.lastName;
    cout << "Enter birth date: ";
    cin >> newPassenger.birthDate;
    // Seat number will be assigned when the seat is assigned
    newPassenger.seatNumber = "";

    bool seatAssigned = assignSeat(passengerArray, 10, to_string(classLevel), newPassenger);
    if (seatAssigned) {
        cout << "Seat has been assigned." << endl;
    } else {
        cout << "No seats are available at the given level." << endl;
    }
} else {
    cout << "That is not a valid seat level";
}
	int firstClassCount;
	int economyCount;
	countSeatLevels(passengerArray, 10, firstClassCount, economyCount);
	cout << "First class seats remaining: " << 5 - firstClassCount << endl;
	cout << "Economy seats remaining: " << 5 - economyCount << endl;

	printBoardPass(passengerArray, 10);
	waitlist(passengerArray, 10);
	return 0;
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


void countSeatLevels(passenger* passengerArray, int size, int& firstClassCount, int& economyCount) {
	firstClassCount = 0;
	economyCount = 0;

	for (int i = 0; i < size; i++) {
		if (passengerArray[i].seatLevel == "1") {
			firstClassCount++;
		}
		else if (passengerArray[i].seatLevel == "2") {
			economyCount++;
		}
	}
}

