// mecanum_sim.cpp
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

// ===== Function Prototypes =====
void displayMenu();
int getUserChoice();
void moveForward(ofstream &);
void moveBackward(ofstream &);
void turnLeft(ofstream &);
void turnRight(ofstream &);
void activateCamera(ofstream &);
void logAction(ofstream &, const string &);
void readConfigFile(string &speed, string &cameraMode); // pass-by-reference for outputs

int main() {
    string speed = "50";       // default if config missing
    string cameraMode = "OFF"; // default if config missing
    ofstream logFile;

    // TODO 1: Read configuration data from file using readConfigFile(speed, cameraMode)
    // Hint: open "config.txt", parse lines like "key=value" and set the variables.
    readConfigFile(speed, cameraMode);    

    // TODO 2: Open "car_log.txt" for writing and verify it opened successfully
    // If open fails, print an error and exit gracefully.
    logFile.open("car_log.txt");
    if (!logFile) {
        cout << "Error: Could not open car_log.txt for writing.\n";
        return 1; // Exit with error code
    }

    logFile << "=== MECANUM CAR LOG ===\n";
    logFile << "Configuration: loaded: speed=" << speed
            << ", camera_mode=" << cameraMode << "\n";
    logFile << "---------------------------------------------\n";

    cout << "Loaded config: speed=" << speed
         << ", camera_mode=" << cameraMode << "\n";

    int choice;
    do {
        displayMenu();
        choice = getUserChoice();

        // TODO 3: Use a switch statement to handle user choice
        switch (choice) {
            case 1: // Case 1: moveForward(logFile)
                moveForward(logFile);
                break;
            case 2: // Case 2: moveBackward(logFile)
                moveBackward(logFile);
                break;
            case 3: // Case 3: turnLeft(logFile)
                turnLeft(logFile);
                break;
            case 4: // Case 4: turnRight(logFile)
                turnRight(logFile);
                break;
            case 5: // Case 5: activateCamera(logFile)
                activateCamera(logFile);
                break;
            case 6: // Case 6: print "Exiting..." and break loop
                cout << "Exiting...\n";
                break;
            default:  // Default: print "Invalid choice"
                cout << "Invalid choice. Please enter a number between 1 and 6.\n";
        }
    } while (choice != 6); // Exit when user selects 6
    
    // TODO 4: Close logFile before ending the program
    logFile << "---------------------------------------------\n";
    logFile << "Session ended successfully.\n";
    logFile.close();
    return 0;
}

// ===== Function Definitions =====
void displayMenu() {
    cout << "\n--- MECANUM CAR MENU ---\n";
    cout << "1. Move Forward\n";
    cout << "2. Move Backward\n";
    cout << "3. Turn Left\n";
    cout << "4. Turn Right\n";
    cout << "5. Activate Camera\n";
    cout << "6. Exit\n";
}

int getUserChoice() {
    int choice;
    cout << "Enter your choice: ";
    if (!(cin >> choice)) {
        // simple recovery
        cin.clear();
        cin.ignore(10000, '\n');
        return -1;
    }
    return choice;
}

void moveForward(ofstream &logFile) {
    cout << "Moving forward...\n";
    logAction(logFile, "Move Forward");
}

void moveBackward(ofstream &logFile) {
    // TODO 5: Print a message and log "Move Backward"
    cout << "Moving backward...\n";
    // Example: cout << "Moving backward...\n"; logAction(logFile, "Move Backward");
    logAction(logFile, "Move Backward");
}

void turnLeft(ofstream &logFile) {
    // TODO 6: Print a message and log "Turn Left"
    cout << "Turning left...\n";
    logAction(logFile, "Turn Left");
}

void turnRight(ofstream &logFile) {
    // TODO 7: Print a message and log "Turn Right"
    cout << "Turning right...\n";
    logAction(logFile, "Turn Right");
}

void activateCamera(ofstream &logFile) {
    // TODO 8: Print a message and log "Activate Camera"
    cout << "Activating camera...\n";
    logAction(logFile, "Activate Camera");
}

void logAction(ofstream &logFile, const string &action) {
    // TODO 9: Write the action string to the log file, one action per line
    // Example: logFile << action << std::endl;
    time_t now = time(0);
    tm *ltm = localtime(&now);

    logFile << "[" 
            << 1900 + ltm->tm_year << "-"
            << (1 + ltm->tm_mon < 10 ? "0" : "") << 1 + ltm->tm_mon << "-"
            << (ltm->tm_mday < 10 ? "0" : "") << ltm->tm_mday << " "
            << (ltm->tm_hour < 10 ? "0" : "") << ltm->tm_hour << ":"
            << (ltm->tm_min < 10 ? "0" : "") << ltm->tm_min << ":"
            << (ltm->tm_sec < 10 ? "0" : "") << ltm->tm_sec 
            << "] " << action << "\n";
}

void readConfigFile(string &speed, string &cameraMode) {
    ifstream config("config.txt");
    if (!config) {
        cout << "No configuration file found; using defaults.\n";
        return;
    }
    string line;
    while (getline(config, line)) {
        // Very simple parsing: expect lines like "key=value"
        size_t eq = line.find('=');
        if (eq == string::npos) continue;
        string key = line.substr(0, eq);
        string value = line.substr(eq + 1);
        if (key == "speed") speed = value;
        else if (key == "camera_mode") cameraMode = value;
    }
    // Files (i.e., file stream objects) should be passed by reference per the slides.
    // This function uses pass-by-reference to return multiple values.  :contentReference[oaicite:10]{index=10}
}