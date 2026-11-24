#ifndef MOTOR_H
#define MOTOR_H

#include <string>

// Direction state for single DC motor driven by an L298N driver
enum class MotorDirection {
    STOP,
    FORWARD,
    BACKWARD
};

/*
 * Motor
 * 
 * Represents a single DC motor driven by an L298N driver.
 * In this simplified model we track:
 *  - a human-readable name (e.g., "front-left")
 *  - current speed as a percentage in the range [-100, 100]
 *  - motor direction (STOP, FORWARD, BACKWARD)
 *  - whether the motor is enabled
 */
class Motor {
private:
    std::string name;
    int speedPercent; // From -100 to +100
    MotorDirection direction; // Current rotation direction
    bool enabled; 

public:
    // Default constructor
    Motor();

    // Paramterized constructor
    Motor(const std::string& motorName);

    // Set the motor speed
    void setSpeed(int newSpeedPercent);

    // Set the motor direction
    void setDirection(MotorDirection newDirection);

    // Stop the motor
    void stop();

    // Get the current speed
    int getSpeed() const;

    // Get the current direction
    MotorDirection getDirection() const;

    // Enable / Disable the motor
    void enable();
    void disable();

    // Checks if the motor is enabled
    bool isEnabled() const;

    // Gets the motor name
    std::string getName() const;
};

#endif // MOTOR_H