#include <iostream>
#include <fstream>
#include <string>

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

    int getSeatNum() {
        return seatNumber;
    }

    void setSeatNum(int newSeatNum) {
        seatNumber = newSeatNum;
    }

    string getLevel() {
        return seatLevel;
    }

    void setLevel(string newLevel) {
        seatLevel = newLevel;
    }
};

// Function to import boarding pass data from a file
void boardingImport(passenger* passengerArray, int& passengerIndex, const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        // create boardingpass.txt if it does not exist
        cout << "Error, " << filename << " does not exist. Creating file now..." << endl;
        ofstream outFile(filename);
        return;
    }

    string line;
    while (getline(inFile, line)) {
        // Assuming each passenger's details are in order and on separate lines check if information is empty and exclude it
        passengerArray[passengerIndex].firstName = line;
        getline(inFile, passengerArray[passengerIndex].lastName);
        getline(inFile, passengerArray[passengerIndex].birthDate);

        string seatNumberStr;
        getline(inFile, seatNumberStr);
        passengerArray[passengerIndex].seatNumber = stoi(seatNumberStr); // Convert string to integer

        getline(inFile, passengerArray[passengerIndex].seatLevel);

        //display the boarding pass
        cout << "Name: " << passengerArray[passengerIndex].firstName << " " << passengerArray[passengerIndex].lastName << endl;
        cout << "Birthdate: " << passengerArray[passengerIndex].birthDate << endl;
        cout << "Seat Number: " << passengerArray[passengerIndex].seatNumber << endl;
        cout << "Seat Level: " << passengerArray[passengerIndex].seatLevel << endl;
        cout << endl;

        passengerIndex++;
        if (passengerIndex >= MAX_SEATS) { // Assuming a maximum of 10 passengers
            break;
        }
    }
    inFile.close();
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
        cout << passengerArray[i].firstName << " " << passengerArray[i].lastName << endl;
        cout << passengerArray[i].birthDate << endl;
        cout << passengerArray[i].seatNumber << endl;
        cout << passengerArray[i].seatLevel << endl;
        cout << "+====+====+====+====+====+====+====+" << endl;
        cout << endl;
        outFile << passengerArray[i].firstName << " " << passengerArray[i].lastName << endl;
        outFile << passengerArray[i].birthDate << endl;
        outFile << passengerArray[i].seatNumber << endl;
        outFile << passengerArray[i].seatLevel << endl;
        outFile << endl;
    }
    outFile.close();
    return 0;
}

// Once the boarding pass has reached 5 first class passengers, and 5 economy passengers, add users to this waitlist. On application start up, move as many passengers from the waitlist to the boardingpass as can be fit.

void waitlist(passenger* passengerArray, int& size) {
    ofstream outFile("waitlist.txt", ios::app); // Append mode
    if (outFile.fail()) {
        cout << "Error opening waitlist.txt file." << endl;
        return;
    }

    for (int i = 0; i < size; i++) {
        outFile << passengerArray[i].firstName << " " << passengerArray[i].lastName << "\n"
            << passengerArray[i].birthDate << "\n"
            << passengerArray[i].seatNumber << "\n"
            << passengerArray[i].seatLevel << "\n";
    }

    outFile.close();
    size = 0; // Reset the size as the passengers are moved to waitlist
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

void populateFromWaitlist(passenger* passengerArray, int& passengerIndex, const string& waitlistFilename, const string& boardingPassFilename) {
    ifstream waitlistFile(waitlistFilename);
    if (!waitlistFile) {
        cout << "No waitlisted passengers." << endl;
        return;
    }

    string line;
    while (getline(waitlistFile, line)) {
        passengerArray[passengerIndex].firstName = line;
        getline(waitlistFile, passengerArray[passengerIndex].lastName);
        getline(waitlistFile, passengerArray[passengerIndex].birthDate);
        getline(waitlistFile, passengerArray[passengerIndex].seatLevel);
        passengerIndex++;

        if (passengerIndex >= MAX_SEATS) {
            break;
        }
    }

    waitlistFile.close();

    // Update boarding pass file with waitlisted passengers
    printBoardPass(passengerArray, passengerIndex);

    // Clear waitlist file after moving passengers
    ofstream clearWaitlist(waitlistFilename, ofstream::trunc);
    clearWaitlist.close();
}

void addToWaitlist(passenger& newPassenger) {
    ofstream outFile("waitlist.txt", ios::app); // Append mode
    if (outFile.fail()) {
        cout << "Error opening waitlist.txt file." << endl;
        return;
    }

    outFile << newPassenger.firstName << "\n"
        << newPassenger.lastName << "\n"
        << newPassenger.birthDate << "\n"
        << newPassenger.seatLevel << "\n\n";

    outFile.close();
}

int main() {
    passenger passengerArray[MAX_SEATS];
    int passengerIndex = 0;
    int firstClassNum = 0;
    int secondClassNum = 0;
    int counter = 0;
    string choice;

    // Populate from waitlist before accepting new passengers
    populateFromWaitlist(passengerArray, passengerIndex, "waitlist.txt", "BoardingPass.txt");

    //Import existing boarding pass data
    boardingImport(passengerArray, passengerIndex, "BoardingPass.txt");

    int classLevel;
    // remove("BoardingPass.txt");
    // Displays menu and asks user for seat level
    cout << "Welcome to Interesting name Airline" << endl;
    cout << "We aim to give you a better Flight Experience" << endl;

    bool addPassenger = true;
    int Fseat = 1;
    int ESeat = 6;
    do {
        cout << "Please input 1 for First class or 2 for Economy (0 to stop or 3 to print pass): ";
        cin >> classLevel;

        // Check if seats are available
        bool seatsAvailable = (classLevel == 1 && firstClassNum < 5) || (classLevel == 2 && secondClassNum < 5);

        if (classLevel == 1 || classLevel == 2) {
            if (seatsAvailable) {
                passenger newPassenger;
                cout << "Enter first name: ";
                cin >> newPassenger.firstName;
                cout << "Enter last name: ";
                cin >> newPassenger.lastName;
                cout << "Enter birth date: ";
                cin >> newPassenger.birthDate;

                // Assign seat number based on class
                newPassenger.seatNumber = (classLevel == 1) ? Fseat++ : ESeat++;
                newPassenger.seatLevel = to_string(classLevel);

                bool seatAssigned = assignSeat(passengerArray, MAX_SEATS, to_string(classLevel), newPassenger);
                if (seatAssigned) {
                    cout << "Seat has been assigned." << endl;
                    if (classLevel == 1) firstClassNum++;
                    else secondClassNum++;
                }
                // Update the boarding pass file immediately after assigning a seat
                printBoardPass(passengerArray, passengerIndex);
            }
            else {
                cout << "No seats are available at the given level." << endl;
                cout << "Would you like to be put on a waitlist? (Y/N)" << endl;
                cin >> choice;
                if (choice == "Y" || choice == "y") {
                    passenger newPassenger;
                    cout << "Enter first name: ";
                    cin >> newPassenger.firstName;
                    cout << "Enter last name: ";
                    cin >> newPassenger.lastName;
                    cout << "Enter birth date: ";
                    cin >> newPassenger.birthDate;
                    newPassenger.seatLevel = to_string(classLevel);
                    addToWaitlist(newPassenger);
                }
                else if (choice == "N" || choice == "n") {
                    cout << "Not added to waitlist." << endl;
                }
                else {
                    cout << "Invalid choice." << endl;
                }
            }
        }
        else if (classLevel == 0) {
            addPassenger = false;
        }
        else if (classLevel == 3) {
            printBoardPass(passengerArray, counter);
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
