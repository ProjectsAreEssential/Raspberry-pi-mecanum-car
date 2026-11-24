/*
 * Project: Drone Fleet Management System
 * Course: TCES 203 Autumn 2026
 * Instructor: Dr. Damiano Torre
 * Team #: ???
 * Student 1 full name: Gavin Gray
 * Student 2 full name: Seth Campbell
 * Variation 1: 1B
 * Variation 2: 2B, 2C
 */

#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <math.h>

// Macros for fleet config
#define MAX_DRONES 5 // Using 5 drones for Variation 1B
#define MAX_LEN 40 // Maximum length for drone model names

// Function prototypes
void addDrone(int ids[], char models[][MAX_LEN], float batteries[], float positions[][2], int *count);
void displayDrones(const int ids[], const char models[][MAX_LEN], const float batteries[], const float positions[][2], int count);
int searchDroneByID(const int ids[], const int count, const int targetID);
int calculateAverageBattery(const float batteries[], int count, float *average);
void displaySingleDrone(const int ids[], const char models[][MAX_LEN], const float positions[][2], int id);
void mainMenu();
int findNearestDrone(const int ids[], const char models[][MAX_LEN], const float batteries[], const float positions[][2], int count);
void batteryWarningCheck(const int ids[], const float batteries[], int count);
void clearInputBuffer();

// Main function
int main() {
    // Storing drone data
    int ids[MAX_DRONES]; // Drone IDs
    char models[MAX_DRONES][MAX_LEN]; // Drone model names
    float batteries[MAX_DRONES]; // Battery levels
    float positions[MAX_DRONES][2]; // Drone'x X and Y coordinates
    float avgBattery = 0.0;

    int count = 0; // Current number of drones in the fleet
    bool display = true;
    int cmd;

    do{
        mainMenu();
        if (scanf("%d", &cmd) == 1) {
            switch (cmd) {
                case 1: {
                    addDrone(ids, models, batteries, positions, &count);
                    break;
                }
                case 2: {
                    displayDrones(ids, models, batteries, positions, count);
                    break;
                }
                case 3: {
                    int id;
                    printf("Enter Drone ID: ");
                    if (scanf("%d", &id) < 1) {
                        printf("Invalid Input!");
                        clearInputBuffer();
                        break;
                    }
                    clearInputBuffer();
                    displaySingleDrone(ids, models, positions, searchDroneByID(ids, count, id));
                    break;
                }
                case 4: {
                    calculateAverageBattery(batteries, count, &avgBattery) ? 
                        printf("Average fleet battery level: %.2f%%\n", avgBattery) :
                        printf("No drones available.");
                    avgBattery = 0;
                    break;
                }
                case 5: {
                    findNearestDrone(ids, models, batteries, positions, count);
                    break;
                }
                case 6: {
                    display = false;
                    break;
                }
                default: 
                    printf("Invalid choice!\n");
            } 
        }else {
            printf("Invalid choice! Must enter an integer 1-6.\n");
        }
        
    } while(display);

    return 0;
}

// Function to add a new drone to the fleet
void addDrone(int ids[], char models[][MAX_LEN], float batteries[], float positions[][2], int *count) {
    // Check if the fleet is full
    if (*count >= MAX_DRONES) {
        printf("Fleet is full. Cannot add more drones.\n");
        return;
    }
    
    // Validate that the user actually entered a valid ID
    printf("Enter Drone ID: ");
    if (scanf("%d", &ids[*count]) != 1) {
        printf("Invalid input. Please enter a valid number.\n");
        clearInputBuffer();    
        return;
    }

    // Check for non-negative IDs
    if (ids[*count] <= 0) {
        printf("Invalid ID. Must be a non-negative integer.\n");
        clearInputBuffer();
        return;
    }
    
    // Check for duplicate IDs
    for (int i = 0; i < *count; i++) {
        if (ids[i] == ids[*count]) {
            printf("Duplicate ID. Drone with this ID already exists.\n");
            clearInputBuffer();
            return;
        }
    }

    // Validate that the user actually entered a valid model name
    printf("Enter Drone Model (max %d chars): ", MAX_LEN - 1);
    if (scanf(" %39[^\n]", models[*count]) != 1 || models[*count][0] == '\0') { //adapted scanf() to only stop at new line character. This allows for spaces in char[].
        printf("Invalid input. Model name cannot be empty.\n");
        clearInputBuffer();
        return;
    }

    // Validate that the user actually entered a valid battery level
    printf("Enter Battery Level (0.0 - 100.0): ");
    if (scanf("%f", &batteries[*count]) != 1 || batteries[*count] < 0.0 || batteries[*count] > 100.0) {
        printf("Invalid input. Please enter a valid battery level between 0.0 and 100.0.\n");
        clearInputBuffer();
        return;
    }

    // Validate that the user actually entered valid position coordinates
    printf("Enter Position (X, Y): ");
    if (scanf("%f, %f", &positions[*count][0], &positions[*count][1]) != 2) {
        printf("Invalid input. Please enter valid position coordinates.\n");
        clearInputBuffer();
        return;
    }

    // Clear the input buffer after successful input
    clearInputBuffer();
    
    // Successfully passed all checks. Increment the count of drones
    (*count)++;

    // Occupied fleet slots
    printf("\nDrone added successfully. Occupied slots: %d / %d\n", *count, MAX_DRONES);

    batteryWarningCheck(ids, batteries, *count);
}

// Function to display all drones in the fleet
void displayDrones(const int ids[], const char models[][MAX_LEN], const float batteries[], const float positions[][2], int count) {
    // Check if there are any drones to display
    if (count == 0) {
        printf("No drones available.\n");
        return;
    }

    // Table header
    printf("--------------------------------------------------------\n");
    printf("%-5s  %-14s  %8s  %10s  %10s\n", "ID", "Model", "Battery", "X", "Y");
    printf("--------------------------------------------------------\n");

    // Each drone's details
    for (int i = 0; i < count; i++) {
        printf("%-5d  %-14.14s  %7.2f%%  %10.2f  %10.2f\n", ids[i], models[i], batteries[i], positions[i][0], positions[i][1]);
    }

    // Table footer and total count
    printf("--------------------------------------------------------\n");
    printf("Total drones: %d\n\n", count);
}

// Function to clear input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Function to search for drone in database
int searchDroneByID(const int ids[], const int count, const int targetID) {
    for(int i = 0; i < count; i++) {
        if (ids[i] == targetID) return i;
    }
    return -1;
}

// Function calculates the average battery percentage across the fleet and stores the value
int calculateAverageBattery(const float batteries[], int count, float *average) {
    if (count < 1) return 0;
    for (int i = 0; i < count; i++) 
        *average += batteries[i];
    *average /= count;
    return 1;
}

// Function handles main menu display
void mainMenu() {
    for(int i = 0; i < 40; i++) printf("=");
    printf("\n     DRONE FLEET MANAGEMENT SYSTEM\n");
    for(int i = 0; i < 40; i++) printf("=");

    printf("\n\n1. Add a Drone"
             "\n2. Display All Drones"
             "\n3. Search for a Drone by ID"
             "\n4. Show Average Battery Level"
             "\n5. Show Nearest Drone"
             "\n6. Exit\n"
             "\nEnter your choice: ");
}

// Function displays Single Drone information 
void displaySingleDrone(const int ids[], const char models[][MAX_LEN], const float positions[][2], int id) {

    if (id < 0) {
        printf("Drone not found.\n");
        return;
    }
    // Header
    printf("-----------------------------------------------------\n");
    printf("%-5s  %-14s  %10s  %10s\n", "ID", "Model", "X", "Y");
    printf("-----------------------------------------------------\n");

    // Drone's details
    printf("%-5d  %-14.14s %10.2f  %10.2f\n", ids[id], 
        models[id], positions[id][0], positions[id][1]);
}

// Fucntion finds the nearest drone to the user input coordinates and outputs the closest drones' index.
int findNearestDrone(const int ids[], const char models[][MAX_LEN], const float batteries[], const float positions[][2], int count) {

    int nearestIndex;
    float x, y, dx, dy, distance, current, previous = INT_MAX;
    char end = 0;

    // Checks if any drones exist in system
    if (count == 0) {
        printf("No drones in the fleet.\n");
        return -1;
    }

    // Validates the user input for any x, y coordinates (fails all but exact formatting 'float, float')
    printf("Enter coordinates (X, Y): ");
    if (scanf("%f ,%f%c", &x, &y, &end) != 3 || end != '\n') {
        printf("Invalid input. Use the format: x, y\n");
        if (end != '\n') {
            clearInputBuffer();
        }
        return -1;
    }

    // Calculates all distance of drones to input point
    for (int i = 0; i < count; i++) {
        dx = positions[i][0] - x;
        dy = positions[i][1] - y;
        current = sqrt((dx*dx)+(dy*dy));
        if (current < previous) {
            previous = current;
            nearestIndex = i;
        }
    }

    printf("--------------------------------------------------------------------\n");
    printf("%-5s  %-14s  %8s  %10s  %10s  %10s\n", "ID", "Model", "Battery", "X", "Y", "Distance");
    printf("--------------------------------------------------------------------\n");

    printf("%-5d  %-14.14s  %7.2f%%  %10.2f  %10.2f %10.2f\n\n", ids[nearestIndex], 
        models[nearestIndex], batteries[nearestIndex], positions[nearestIndex][0], positions[nearestIndex][1], current);

    return nearestIndex;
}

void batteryWarningCheck(const int ids[], const float batteries[], int count) {
    if (batteries[count - 1] < 20.0)
        printf("Warning!: Drone %d has low battery (%.2f%%)\n", ids[count - 1], batteries[count - 1]);
}