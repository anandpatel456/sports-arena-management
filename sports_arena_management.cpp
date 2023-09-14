#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Stadium {
protected:
    string name;
    string location;
    int capacity;

public:
    Stadium(const string& name, const string& location, int capacity)
        : name(name), location(location), capacity(capacity) {}

    void displayInfo() {
        cout << "Stadium: " << name << endl;
        cout << "Location: " << location << endl;
        cout << "Capacity: " << capacity << " people" << endl;
    }
};

class SportStadium : public Stadium {
protected:
    string sport;

public:
    SportStadium(const string& name, const string& location, int capacity, const string& sport)
        : Stadium(name, location, capacity), sport(sport) {}

    void displayInfo() {
        Stadium::displayInfo();
        cout << "Sport: " << sport << endl;
    }
};

class SwimmingPoolStadium : public SportStadium {
public:
    SwimmingPoolStadium(const string& name, const string& location, int capacity)
        : SportStadium(name, location, capacity, "Swimming") {}
};

class TableTennisStadium : public SportStadium {
protected:
    string team;

public:
    TableTennisStadium(const string& name, const string& location, int capacity, const string& team)
        : SportStadium(name, location, capacity, "Table Tennis"), team(team) {}

    void displayInfo() {
        SportStadium::displayInfo();
        cout << "Home team:" << team << endl;
    }
};

class BadmintonStadium : public SportStadium {
protected:
    string team;

public:
    BadmintonStadium(const string& name, const string& location, int capacity, const string& team)
        : SportStadium(name, location, capacity, "Badminton"), team(team) {}

    void displayInfo() {
        SportStadium::displayInfo();
        cout << "Home Team:"  << team << endl;
    }
};

class Player {
protected:
    string name;
    int age;
    string sport;

public:
    Player(const string& name, int age, const string& sport)
        : name(name), age(age), sport(sport) {}

    void displayInfo() {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Sport: " << sport << endl;
    }

    void saveToFile(ofstream& outFile) {
        outFile << "Name: " << name << endl;
        outFile << "Age: " << age << endl;
        outFile << "Sport: " << sport << endl;
        outFile << "-------------------" << endl;
    }
};

int main() {
    SwimmingPoolStadium swimmingPoolStadium("Swimming pool Arena", "Lekoda", 200);
    TableTennisStadium tableTennisStadium("Table Tennis Ground", "Potlod", 300, "Jahrila club");
    BadmintonStadium badmintonStadium("Badminton court", "Rananbad", 350, "Dhhumdhhaka");

    swimmingPoolStadium.displayInfo();
    cout << endl;
    tableTennisStadium.displayInfo();
    cout << endl;
    badmintonStadium.displayInfo();

    const int maxSwimmingPlayers = 20; // Maximum number of swimming players
    const int maxTableTennisPlayers = 20;  // Maximum number of table tennis players
    const int maxBadmintonPlayers = 4;   // Maximum number of badminton players

    int swimmingPlayerCount = 0;
    int tableTennisPlayerCount = 0;
    int badmintonPlayerCount = 0;

    Player* swimmingPlayers[maxSwimmingPlayers]; // Array to store swimming players
    Player* tableTennisPlayers[maxTableTennisPlayers];   // Array to store table tennis players
    Player* badmintonPlayers[maxBadmintonPlayers];     // Array to store badminton players

    cout << "Player Registration:" << endl;
    while (true) {
        string name, sport;
        int age;
        char choice;

        cout << "Enter player's name: ";
        cin >> name;
        cout << "Enter player's age: ";
        cin >> age;
        cout << "Enter the sport to register for (Swimming/TableTennis/Badminton): ";
        cin >> sport;

        Player* player = new Player(name, age, sport);

        if (sport == "Swimming") {
            if (swimmingPlayerCount < maxSwimmingPlayers) {
                swimmingPlayers[swimmingPlayerCount] = player;
                swimmingPlayerCount++;
            } else {
                cout << "Maximum number of Swimming players reached." << endl;
                delete player; // Free the memory allocated for the player
            }
        } else if (sport == "TableTennis") {
            if (tableTennisPlayerCount < maxTableTennisPlayers) {
                tableTennisPlayers[tableTennisPlayerCount] = player;
                tableTennisPlayerCount++;
            } else {
                cout << "Maximum number of Table Tennis players reached." << endl;
                delete player; // Free the memory allocated for the player
            }
        } else if (sport == "Badminton") {
            if (badmintonPlayerCount < maxBadmintonPlayers) {
                badmintonPlayers[badmintonPlayerCount] = player;
                badmintonPlayerCount++;
            } else {
                cout << "Maximum number of Badminton players reached." << endl;
                delete player; // Free the memory allocated for the player
            }
        } else {
            cout << "Invalid sport entered. Please enter Swimming, TableTennis, or Badminton." << endl;
            delete player; // Free the memory allocated for the player
        }

        cout << "Do you want to register another player? (y/n): ";
        cin >> choice;

        if (choice != 'y' && choice != 'Y') {
            break;
        }
    }

    // Save registered players to a file
    ofstream fout("C:/Users/anand/OneDrive/Documents/Project.txt", ios::app);
    if (fout.is_open()) {
        fout << "Registered Players:" << endl;
        fout << "-------------------" << endl;

        for (int i = 0; i < swimmingPlayerCount; i++) {
            swimmingPlayers[i]->saveToFile(fout);
            delete swimmingPlayers[i]; // Free the memory allocated for the player
        }

        for (int i = 0; i < tableTennisPlayerCount; i++) {
            tableTennisPlayers[i]->saveToFile(fout);
            delete tableTennisPlayers[i]; // Free the memory allocated for the player
        }

        for (int i = 0; i < badmintonPlayerCount; i++) {
            badmintonPlayers[i]->saveToFile(fout);
            delete badmintonPlayers[i]; // Free the memory allocated for the player
        }

        fout.close();
        cout << "Player registration data has been saved to 'Project.txt'." << endl;
    } else {
        cerr << "Error: Unable to open the file for writing." << endl;
    }

    return 0;
}
