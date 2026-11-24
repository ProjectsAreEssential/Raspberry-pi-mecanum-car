// CarPollingLoop.cpp
// TCES 203 – Looping practice (completed version)
// Apply Chapter 5: while loops, input validation, counters, running totals, sentinels

#include <iostream>
using namespace std;

int main() {
    // 1. Declare counters and variables
    int totalCycles = 0;
    int safeCycles = 0;
    int emergencyStops = 0;

    int distanceToObstacleCm = 0;
    int batteryPercent = 0;
    char driveMode = 'S';

    cout << "=== Car Polling Loop Simulation ===" << endl;

    // 2. Main polling loop
    while (distanceToObstacleCm != -1) {

        cout << "\nEnter distance (0-200 cm, -1 to quit): ";
        cin >> distanceToObstacleCm;

        while ((distanceToObstacleCm < 0 || distanceToObstacleCm > 200) && distanceToObstacleCm != -1) {
            cout << "Invalid input. Please enter a distance between 0 and 200 cm, or -1 to quit: ";
            cin >> distanceToObstacleCm;
        }

        // Sentinel check: if user entered -1, exit the loop immediately
        if (distanceToObstacleCm == -1) {
            break;
        }

        cout << "Enter battery level (%): ";
        cin >> batteryPercent;
        
        while (batteryPercent < 0 || batteryPercent > 100) {
            cout << "Invalid input. Please enter a battery level between 0 and 100: ";
            cin >> batteryPercent;
        }

        cout << "Enter drive command (F/B/L/R/S): ";
        cin >> driveMode;

        while (driveMode != 'F' && driveMode != 'B' && driveMode != 'L'&& 
               driveMode != 'R' && driveMode != 'S' && driveMode != 'f' && 
               driveMode != 'b' && driveMode != 'l' &&
               driveMode != 'r' && driveMode != 's') {
            cout << "Invalid command. Enter drive command (F/B/L/R/S): ";
            cin >> driveMode;
        }

        // Once data is valid, increment totalCycles
        totalCycles++;

        // 3. Compute safety flags
        bool isPathClear = (distanceToObstacleCm >= 25);
        bool isBatteryOK = (batteryPercent >= 20);
        bool canMove = (isPathClear && isBatteryOK);

        // 4. Decision logic
        if (!canMove) {
            cout << "Emergency Stop - unsafe cycle." << endl;
            
            // 5. Update counters
            emergencyStops++;
        } else {
            safeCycles++;

            switch (driveMode) {
                case 'F':
                case 'f':
                    cout << "Decision: DRIVE FORWARD" << endl;
                    break;
                case 'B':
                case 'b':
                    cout << "Decision: DRIVE BACKWARD" << endl;
                    break;
                case 'L':
                case 'l':
                    cout << "Decision: STRAFE LEFT" << endl;
                    break;
                case 'R':
                case 'r':
                    cout << "Decision: STRAFE RIGHT" << endl;
                    break;
                case 'S':
                case 's':
                    cout << "Decision: STOP" << endl;
                    break;
            }

            // 6. Motor mapping
            cout << "Motor mapping:" << endl;
            switch (driveMode) {
                case 'F':
                case 'f':
                    cout << "Left side: FORWARD" << endl;
                    cout << "Right side: FORWARD" << endl;
                    break;
                case 'B':
                case 'b':
                    cout << "Left side: BACKWARD" << endl;
                    cout << "Right side: BACKWARD" << endl;
                    break;
                case 'L':
                case 'l':
                    cout << "Left side: BACKWARD" << endl;
                    cout << "Right side: FORWARD" << endl;
                    break;
                case 'R':
                case 'r':
                    cout << "Left side: FORWARD" << endl;
                    cout << "Right side: BACKWARD" << endl;
                    break;
                case 'S':
                case 's':
                    cout << "Left side: STOP" << endl;
                    cout << "Right side: STOP" << endl;
                    break;
            }
        }
    }

    // 7. After loop ends, print final report
    cout << "\n=== Final Report ===" << endl;
    cout << "Total cycles processed: " << totalCycles << endl;
    cout << "Safe cycles: " << safeCycles << endl;
    cout << "Emergency stops: " << emergencyStops << endl;
    
    double safePercentage = 0.0;
    if (totalCycles > 0) {
        safePercentage = (static_cast<double>(safeCycles) / totalCycles) * 100.0;
    }
    cout << "Safe cycle percentage: " << safePercentage << " % " << endl;
    cout << "=== End of Simulation ===" << endl;
    
    return 0;
}