#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <cctype>


using namespace std;

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
string readLineFromFile(ifstream& file) {
    string line;
    getline(file, line);
    // remove whitespace
    line.erase(line.begin(), std::find_if(line.begin(), line.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    line.erase(std::find_if(line.rbegin(), line.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), line.end());
    return line;
}

void boardingImport(passenger* passengerArray, int& passengerIndex, const string& filename, int& firstClassNum, int& secondClassNum) {
    ifstream boardingPassFile(filename);
    if (!boardingPassFile) {
        cout << "No boarding pass data." << endl;
        return;
    }

    string line;
    while (getline(boardingPassFile, line)) {
        // remove whitespace
        line.erase(line.begin(), std::find_if(line.begin(), line.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        }));
        line.erase(std::find_if(line.rbegin(), line.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base(), line.end());

        cout << "Read line: " << line << endl; // Debug output

        // Store the line in the record
        vector<string> record;
        record.push_back(line);

        // Read the next 4 lines for the current passenger
        for (int i = 0; i < 4; i++) {
            if (!getline(boardingPassFile, line)) {
                // The file has ended, so break out of the loop
                break;
            }
            cout << "Read line: " << line << endl; // Debug output
            record.push_back(line);
        }

        if (record.size() != 5) {
            cout << "Invalid record format. Skipping this record." << endl;
            continue;
        }

        // Store the passenger details
        passengerArray[passengerIndex].firstName = record[0];
        passengerArray[passengerIndex].lastName = record[1];
        passengerArray[passengerIndex].birthDate = record[2];
        try {
            passengerArray[passengerIndex].seatNumber = std::stoi(record[3]);
        } catch (std::invalid_argument const &e) {
            cout << "Bad input: std::invalid_argument thrown" << '\n';
            continue;
        } catch (std::out_of_range const &e) {
            cout << "Integer overflow: std::out_of_range thrown" << '\n';
            continue;
        }
        passengerArray[passengerIndex].seatLevel = record[4] == "1" ? "First class" : "Economy";

        // Update seat counters
        if (passengerArray[passengerIndex].seatLevel == "First class") {
            firstClassNum++;
        }
        else {
            secondClassNum++;
        }

        passengerIndex++;
    }

    boardingPassFile.close();
}

set<int> assignedSeats;

// assignSeat function to assign seat to the passenger based on the seat level for the passenger and up the seat counters for the respective class
bool assignSeat(passenger* passengerArray, int& size, string seatLevel, passenger& newPassenger, int& passengerIndex, int& counter, int& Fseat, int& ESeat, int& firstClassNum, int& secondClassNum) {
    if (seatLevel == "1") {
        if (firstClassNum < 5) {
            passengerArray[counter] = newPassenger;
            counter++;
            return true;
        }
        else {
            cout << "No seats are available at the given level." << endl;
            return false;
        }
    }
    else if (seatLevel == "2") {
        if (secondClassNum < 5) {
            passengerArray[counter] = newPassenger;
            counter++;
            return true;
        }
        else {
            cout << "No seats are available at the given level." << endl;
            return false;
        }
    }
    else if (seatLevel == "3") {
        if (firstClassNum < 5) {
            passengerArray[counter] = newPassenger;
            counter++;
            return true;
        }
        else if (secondClassNum < 5) {
            passengerArray[counter] = newPassenger;
            counter++;
            return true;
        }
        else {
            cout << "No seats are available at the given level." << endl;
            return false;
        }
    }
    return false;
}
// Function to print out the entire boarding pass into the file
void printBoardPass(passenger* passengerArray, int counter) {
    ofstream outFile("BoardingPass.txt", std::ios::app); // Truncate mode
    if (outFile.fail()) {
        cout << "Error opening BoardingPass.txt file." << endl;
        return;
    }

    for (int i = 0; i < counter; i++) {
        outFile << passengerArray[i].firstName << "\n"
            << passengerArray[i].lastName << "\n"
            << passengerArray[i].birthDate << "\n"
            << passengerArray[i].seatNumber << "\n"
            << passengerArray[i].seatLevel << "\n\n";
    }

    outFile.close();
}


// Function to display the boarding pass for the all added  passenger
void DisplayBoardPass(passenger* passengerArray, int counter) {
    cout << "Boarding Pass" << endl;
    for (int i = 0; i < counter; i++) {
        cout << "Name: " << passengerArray[i].firstName << " " << passengerArray[i].lastName << endl;
        cout << "Birth Date: " << passengerArray[i].birthDate << endl;
        cout << "Seat Number: " << passengerArray[i].seatNumber << endl;
        cout << "Seat Level: " << passengerArray[i].seatLevel << endl;
        cout << endl;
    }
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

        if (passengerIndex >= 10) {
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
    ofstream outFile("waitlist.txt"); // Append mode
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
    passenger passengerArray[10] = {};
    int passengerIndex = 0;
    int firstClassNum = 0;
    int secondClassNum = 0;
    int counter = 0;
    int size = 10;
    string choice;

    // Initialize seat numbers
    int Fseat = 1;
    int ESeat = 6;

    // Populate from waitlist before accepting new passengers
    populateFromWaitlist(passengerArray, passengerIndex, "waitlist.txt", "BoardingPass.txt");

    // Import existing boarding pass data
    boardingImport(passengerArray, passengerIndex, "BoardingPass.txt", firstClassNum, secondClassNum);

    int classLevel;
    // remove("BoardingPass.txt");
    // Displays menu and asks user for seat level
    cout << "Welcome to Interesting name Airline" << endl;
    cout << "We aim to give you a better Flight Experience" << endl;

    bool addPassenger = true;
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
                newPassenger.seatNumber = (classLevel == 1) ? Fseat : ESeat;
                newPassenger.seatLevel = to_string(classLevel);

                string seatLevel = (classLevel == 1) ? "1" : "2"; // Ensure seat level is either "1" or "2"

                bool seatAssigned = assignSeat(passengerArray, size, seatLevel, newPassenger, passengerIndex, counter, Fseat, ESeat, firstClassNum, secondClassNum);

                if (classLevel == 1) {
                    firstClassNum++;
                    Fseat++;
                }
                else if (classLevel == 2) {
                    secondClassNum++;
                    ESeat++;
                }
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
            DisplayBoardPass(passengerArray, counter);
        }
        else {
            cout << "That is not a valid seat level" << endl;
        }
        
    } while (addPassenger);
    // Update the boarding pass file immediately after assigning a seat
    printBoardPass(passengerArray, counter);

    cout << "First class seats remaining: " << 5 - firstClassNum << endl;
    cout << "Economy seats remaining: " << 5 - secondClassNum << endl;

    DisplayBoardPass(passengerArray, counter);

    return 0;
}

