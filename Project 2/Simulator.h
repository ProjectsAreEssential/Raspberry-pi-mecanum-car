#ifndef SIMULATOR_H
#define SIMULATOR_H

#include "Car.h"

/*
 * Simulator
 * ---------
 * Manages the terminal-based simulation loop and user interaction for the
 * four-wheel mecanum car model.
 * In this simplified model we track:
 *  - the simulated Car instance (motors, camera, position, and heading)
 *  - whether the simulation loop is currently running
 */
class Simulator {
private:
    Car car;      // Mecanum car
    bool running; // True while the simulation loop is active

public:
    // Default constructor
    Simulator();

    // Starts and runs the interactive simulation loop
    void run();

    // Displays available commands/menu options
    void printMenu() const;

    // Processes a single user command/choice
    void handleCommand(int choice);

    // Displays current car telemetry and camera status
    void printStatus() const;

    // Stops the simulation loop
    void stop();
};

#endif // SIMULATOR_H