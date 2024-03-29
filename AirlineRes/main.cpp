#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

const int MAX_SEATS = 10;

class passenger {
public:
    string firstName;
    string lastName;
    string birthDate;
    int seatNumber;
    string seatLevel;

    string getFirName() {
        return firstName;
    }

    void setFirName(string newFirName) {
        firstName = newFirName;
    }

    string getLasName() {
        return lastName;
    }

    void setLasName(string newLasName) {
        lastName = newLasName;
    }

    string getBirth() {
        return birthDate;
    }

    void setBirth(string newBirth) {
        birthDate = newBirth;
    }

    string getLevel() {
        return seatLevel;
    }

    void setLevel(string newLevel) {
        seatLevel = newLevel;
    }
};


class BoardingPassenger : public passenger {
public:
    string boardingTime;

    string getBoardingTime() {
        return boardingTime;
    }

    void setBoardingTime(string newBoardingTime) {
        boardingTime = newBoardingTime;
    }
};

class WaitlistPassenger : public passenger {
public:
    int waitlistPosition;

    int getWaitlistPosition() {
        return waitlistPosition;
    }

    void setWaitlistPosition(int newPosition) {
        waitlistPosition = newPosition;
    }
};

// Function to import boarding pass data from a file
void boardingImport(BoardingPassenger* boardingPassengerArray, WaitlistPassenger* waitlistPassengerArray, int& passengerIndex, const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        // create boardingpass.txt if it does not exist
        cout << "Error, " << filename << " does not exist. Creating file now..." << endl;
        ofstream outFile(filename);
        return;
    }

    // Read data from file and store in boardingPassengerArray and waitlistPassengerArray
    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string firstName, lastName, boardingTime;
        int waitlistPosition;

        // Assuming the file format is: firstName, lastName, boardingTime, waitlistPosition
        getline(ss, firstName, ',');
        getline(ss, lastName, ',');
        getline(ss, boardingTime, ',');
        ss >> waitlistPosition;

        // Create a BoardingPassenger or WaitlistPassenger based on the data
        if (!boardingTime.empty()) {
            BoardingPassenger bp;
            bp.setFirName(firstName);
            bp.setLasName(lastName);
            bp.setBoardingTime(boardingTime); // Fix: Change the access specifier of setBoardingTime to public
            boardingPassengerArray[passengerIndex++] = bp;
        } else if (waitlistPosition != 0) {
            WaitlistPassenger wp;
            wp.setFirName(firstName);
            wp.setLasName(lastName);
            wp.setWaitlistPosition(waitlistPosition);
            waitlistPassengerArray[passengerIndex++] = wp;
        }
    }
}

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
int printBoardPass(passenger* passengerArray, int counter) {
    ofstream outFile("BoardingPass.txt", ios::app);
    if (outFile.fail()) {
        cout << "Error opening file" << endl;
        exit(1);
    }

    for (int i = 0; i < counter - 1; i++) {
        cout << endl;
        cout << "+====+====+====+====+====+====+====+" << endl;
        cout << "Name: " << passengerArray[i].firstName << " " << passengerArray[i].lastName << endl;
        cout << "Birthdate: " << passengerArray[i].birthDate << endl;
        cout << "Seat Number: " << passengerArray[i].seatNumber << endl;
        cout << "Seat Level: " << passengerArray[i].seatLevel << endl;
        cout << "+====+====+====+====+====+====+====+" << endl;
        cout << endl;
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
int waitlist(passenger* passengerArray, int size) {
    ofstream outFile("waitlist.txt");
    if (outFile.fail()) {
        cout << "Error, waitlist.txt does not exist. Creating file now.." << endl;
        ofstream outFile("waitlist.txt");
    }

    for (int i = 0; i < size; i++) {
        outFile << "Name: " << passengerArray[i].firstName << " " << passengerArray[i].lastName << endl;
        outFile << "Birthdate: " << passengerArray[i].birthDate << endl;
        outFile << "Seat Level: " << passengerArray[i].seatLevel << endl;
        outFile << endl;
    }

    outFile.close();
    cout << "Next flight leaves in 3 hours" << endl;
    return 0;
}

// Function to count the number of seats in each class
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

int main() {
    passenger passengerArray[MAX_SEATS];
    int passengerIndex = 0;
    int firstClassNum = 0;
    int secondClassNum = 0;
    int counter = 0;
    string choice;

    // Import existing boarding pass data
    //boardingImport(passengerArray, passengerIndex, "BoardingPass.txt");

    int classLevel;
    remove("BoardingPass.txt");
    // Displays menu and asks user for seat level
    cout << "Welcome to Interesting name Airline" << endl;
    cout << "We aim to give you a better Flight Experience" << endl;

    bool addPassenger = true;
    int Fseat = 1;
    int ESeat = 6;
    do {
        cout << "Please input 1 for First class or 2 for Economy (0 to stop): ";
        cin >> classLevel;

        if (classLevel == 1) {
            firstClassNum++;
            if (firstClassNum <= 5) {
                passenger newPassenger;
                cout << "Enter first name: ";
                cin >> newPassenger.firstName;
                cout << "Enter last name: ";
                cin >> newPassenger.lastName;
                cout << "Enter birth date: ";
                cin >> newPassenger.birthDate;
                // Seat number will be assigned when the seat is assigned
                newPassenger.seatNumber = Fseat;
                Fseat++;

                bool seatAssigned = assignSeat(passengerArray, MAX_SEATS, to_string(classLevel), newPassenger);
                if (seatAssigned) {
                    cout << "Seat has been assigned." << endl;
                }
            }
            else {
                cout << "No seats are available at the given level." << endl;
                cout << "Would you like to be put on a waitlist? (Y/N)" << endl;
                cin >> choice;
                if (choice == "Y" || choice ==  "y") {
                    waitlist(passengerArray, counter);
                }
                else if (choice == "N" || choice == "n") {
                    cout << "Well, GET OUT OF MY AIRPORT!";
                }
                else {
                    cout << "Not A Choice";
                    exit(1);
                }
            }
        }
        else if (classLevel == 2) {
            secondClassNum++;
            if (secondClassNum <= 5) {
                passenger newPassenger;
                cout << "Enter first name: ";
                cin >> newPassenger.firstName;
                cout << "Enter last name: ";
                cin >> newPassenger.lastName;
                cout << "Enter birth date: ";
                cin >> newPassenger.birthDate;
                // Seat number will be assigned when the seat is assigned
                newPassenger.seatNumber = ESeat;
                ESeat++;

                bool seatAssigned = assignSeat(passengerArray, MAX_SEATS, to_string(classLevel), newPassenger);
                if (seatAssigned) {
                    cout << "Seat has been assigned." << endl;
                }
            }
            else {
                cout << "No seats are available at the given level." << endl;
                cout << "Would you like to be pput on a waitlist? (Y/N)" << endl;
                cin >> choice;
                if (choice == "Y" || "y") {
                    waitlist(passengerArray, counter);
                }
                else if (choice == "N" || choice == "n") {
                    cout << "Well, GET OUT OF MY AIRPORT!";
                    // Need a exit statement here
                }
                else {
                    cout << "Not A Choice";
                    exit(1);
                }
            }
        }
        else if (classLevel == 0) {
            addPassenger = false;
        }
        else {
            cout << "That is not a valid seat level" << endl;
        }
        counter++;
    } while (addPassenger);

    cout << "First class seats remaining: " << 5 - firstClassNum << endl;
    cout << "Economy seats remaining: " << 5 - secondClassNum << endl;

    printBoardPass(passengerArray, counter);

    return 0;
}