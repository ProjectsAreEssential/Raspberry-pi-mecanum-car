#ifndef CAR_H
#define CAR_H

#include "Motor.h"
#include "Camera.h"

/*
 * Car
 * ---
 * Represents a simulated four-wheel mecanum car combining drive motors
 * and a camera module for terminal-based movement and inspection testing.
 * In this simplified model we track:
 *  - individual mecanum wheel motor states (front-left, front-right, rear-left, rear-right)
 *  - simulated position (x, y) and heading angle
 *  - attached camera module state
 */
class Car {
private:
    Motor frontLeft;  // Front-left mecanum wheel motor
    Motor frontRight; // Front-right mecanum wheel motor
    Motor rearLeft;   // Rear-left mecanum wheel motor
    Motor rearRight;  // Rear-right mecanum wheel motor
    Camera camera;    // camera module
    double posX;      // X position
    double posY;      // Y position
    double heading;   // Heading angle in degrees

public:
    // Default constructor
    Car();

    // Move forward or backward at the given speed
    void moveForward(int speed);
    void moveBackward(int speed);

    // Strafe left or right
    void strafeLeft(int speed);
    void strafeRight(int speed);

    // Rotate in place clockwise or counter-clockwise
    void rotateClockwise(int speed);
    void rotateCounterClockwise(int speed);

    // Stop all four wheel motors
    void stop();

    // Start / stop camera
    void startCamera();
    void stopCamera();

    // Capture's a frame at the car's current position
    void captureCameraFrame();

    // Get x / y coordinate
    double getX() const;
    double getY() const;

    // Get heading
    double getHeading() const;

    // Camera module (Read only)
    const Camera& getCamera() const;
};

#endif // CAR_H