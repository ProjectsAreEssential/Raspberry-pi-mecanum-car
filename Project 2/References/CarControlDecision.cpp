#include <iostream>
using namespace std;

int main() {
    int choice = 0;

    int distanceToObstacleCm = 0;
    int batteryPercent = 0;
    char driveMode = 'S';   // F, B, L, R, S

    // 5. (Optional) Menu Loop for extra credit
    do {
        cout << "\n=== Car Control Menu ===" << endl;
        cout << "1. Enter sensor data" << endl;
        cout << "2. Run decision" << endl;
        cout << "3. Quit" << endl;
        cout << "Enter your choice (1-3): ";
        cin >> choice;

        switch (choice) {
            case 1: {
                // 2. Read input from user
                cout << "Enter distance to obstacle (cm 0-200): ";
                cin >> distanceToObstacleCm;

                cout << "Enter battery level (% 0-100): ";
                cin >> batteryPercent;

                cout << "Enter drive command (F/B/L/R/S): ";
                cin >> driveMode;

                // 3. Validate input
                if (distanceToObstacleCm < 0 || distanceToObstacleCm > 200) {
                    cout << "Error: distance out of range." << endl;
                    break;
                }
                if (batteryPercent < 0 || batteryPercent > 100) {
                    cout << "Error: battery level out of range." << endl;
                    break;
                }
                if (driveMode != 'F' && driveMode != 'B' && driveMode != 'L' && 
                    driveMode != 'R' && driveMode != 'S' && driveMode != 'f' && 
                    driveMode != 'b' && driveMode != 'l' && driveMode != 'r' && driveMode != 's') {
                    cout << "Error: invalid drive command." << endl;
                    break;
                }
                break;
            }
            case 2: {
                // 4. Safety flags
                bool isPathClear = (distanceToObstacleCm >= 25);
                bool isBatteryOK = (batteryPercent >= 20);
                bool canMove = (isPathClear && isBatteryOK);

                cout << "Path clear: " << isPathClear << endl;
                cout << "Battery OK: " << isBatteryOK << endl;

                // 5. Decision logic (if/else)
                if (!canMove) {
                    cout << "EMERGENCY STOP: unsafe to move!" << endl;
                    driveMode = 'S';   // force stop
                } else if (driveMode == 'F' || driveMode == 'f' || driveMode == 'B' || driveMode == 'b') {
                    cout << "Moving ";
                    if (driveMode == 'F' || driveMode == 'f') {
                        cout << "forward" << endl;
                    } else {
                        cout << "backward" << endl;
                    }
                } else if (driveMode == 'L' || driveMode == 'l' || driveMode == 'R' || driveMode == 'r') {
                    cout << "Strafing ";
                    if (driveMode == 'L' || driveMode == 'l') {
                        cout << "left" << endl;
                    } else {
                        cout << "right" << endl;
                    }
                } else {
                    cout << "Unknown command." << endl;
                }

                // 6. Motor mapping (switch)
                switch (driveMode) {
                    case 'F':
                    case 'f':
                        cout << "All wheels: FORWARD" << endl;
                        break;
                    case 'B':
                    case 'b':
                        cout << "All wheels: BACKWARD" << endl;
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
                        cout << "All wheels: STOP" << endl;
                        break;
                    default:
                        cout << "No mapping for this command." << endl;
                        break;
                }
                break;
            }
            case 3:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid menu choice. Please choose 1, 2, or 3." << endl;
                break;
        }
    } while (choice != 3);

    cout << "Program finished." << endl;
    return 0;
}