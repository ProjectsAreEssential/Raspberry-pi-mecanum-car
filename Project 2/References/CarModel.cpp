#include "CarModel.h"
#include <cmath>   // std::fmod (optional)

// --------------------
// Motor implementation
// --------------------

Motor::Motor()
    : name("unnamed"), speedPercent(0), enabled(false)
{
    // Nothing else to do.
}

Motor::Motor(const std::string& motorName)
    : name(motorName), speedPercent(0), enabled(false)
{
    // Optional: you may add debug prints while testing, but not required.
}

void Motor::setSpeed(int newSpeedPercent)
{
    if (newSpeedPercent > 100) {
        speedPercent = 100;
    } else if (newSpeedPercent < -100) {
        speedPercent = -100;
    } else {
        speedPercent = newSpeedPercent;
    }
}

int Motor::getSpeed() const
{
    return speedPercent;
}

void Motor::enable()
{
    enabled = true;
}

void Motor::disable()
{
    enabled = false;
    speedPercent = 0;
}

bool Motor::isEnabled() const
{
    return enabled; 
}

std::string Motor::getName() const
{
    return name; 
}


// -----------------------
// PiCamera implementation
// -----------------------

PiCamera::PiCamera()
    : streaming(false)
{
    // Nothing else to do.
}

void PiCamera::startStream()
{
    streaming = true;
}

void PiCamera::stopStream()
{
    streaming = false; 
}

bool PiCamera::isStreaming() const
{
    return streaming; 
}


// ------------------------
// MecanumCar implementation
// ------------------------

MecanumCar::MecanumCar()
    : frontLeft("front-left"),
    frontRight("front-right"),
    rearLeft("rear-left"),
    rearRight("rear-right"),
    camera(),
    x(0.0), y(0.0), headingDeg(0.0)

{
    // Constructor body can be empty once the member-initialization list is complete.
}

void MecanumCar::updatePose(double dx, double dy, double dThetaDeg)
{
    x += dx;
    y += dy;
    headingDeg += dThetaDeg;
    
    while (headingDeg >= 360.0) headingDeg -= 360.0;
    while (headingDeg < 0.0)    headingDeg += 360.0;
}

void MecanumCar::moveForward(double distance)
{
    updatePose(0.0, distance, 0.0);

    frontLeft.setSpeed(50);
    frontLeft.enable();
    frontRight.setSpeed(50);
    frontRight.enable();
    rearLeft.setSpeed(50);
    rearLeft.enable();
    rearRight.setSpeed(50);
    rearRight.enable();
}

void MecanumCar::moveBackward(double distance)
{
    updatePose(0.0, -distance, 0.0);

    frontLeft.setSpeed(-50);
    frontLeft.enable();
    frontRight.setSpeed(-50);
    frontRight.enable();
    rearLeft.setSpeed(-50);
    rearLeft.enable();
    rearRight.setSpeed(-50);
    rearRight.enable();
}

void MecanumCar::strafeLeft(double distance)
{
    updatePose(-distance, 0.0, 0.0);
    frontLeft.setSpeed(-50);
    frontLeft.enable();
    frontRight.setSpeed(50);
    frontRight.enable();
    rearLeft.setSpeed(50);
    rearLeft.enable();
    rearRight.setSpeed(-50);
    rearRight.enable();
}

void MecanumCar::strafeRight(double distance)
{
    updatePose(distance, 0.0, 0.0);
    frontLeft.setSpeed(50);
    frontLeft.enable();
    frontRight.setSpeed(-50);
    frontRight.enable();
    rearLeft.setSpeed(-50);
    rearLeft.enable();
    rearRight.setSpeed(50);
    rearRight.enable();
}

void MecanumCar::rotateLeft(double angleDeg)
{
    updatePose(0.0, 0.0, angleDeg);
    frontLeft.setSpeed(-50);
    frontLeft.enable();
    frontRight.setSpeed(50);
    frontRight.enable();
    rearLeft.setSpeed(-50);
    rearLeft.enable();
    rearRight.setSpeed(50);
    rearRight.enable();
}

void MecanumCar::rotateRight(double angleDeg)
{
    updatePose(0.0, 0.0, -angleDeg);
    frontLeft.setSpeed(50);
    frontLeft.enable();
    frontRight.setSpeed(-50);
    frontRight.enable();
    rearLeft.setSpeed(50);
    rearLeft.enable();
    rearRight.setSpeed(-50);
    rearRight.enable();
}  

void MecanumCar::stopAllMotors()
{
    frontLeft.setSpeed(0);
    frontLeft.disable();
    frontRight.setSpeed(0);
    frontRight.disable();
    rearLeft.setSpeed(0);
    rearLeft.disable();
    rearRight.setSpeed(0);
    rearRight.disable();
}

void MecanumCar::cameraOn()
{
    camera.startStream();
}

void MecanumCar::cameraOff()
{
    camera.stopStream();
}

double MecanumCar::getX() const
{
    return x; 
}

double MecanumCar::getY() const
{
    return y; 
}

double MecanumCar::getHeadingDeg() const
{
    return headingDeg;
}

Motor MecanumCar::getFrontLeftMotor() const
{
    return Motor(frontLeft); 
}

Motor MecanumCar::getFrontRightMotor() const
{
    return Motor(frontRight); 
}

Motor MecanumCar::getRearLeftMotor() const
{
    return Motor(rearLeft); 
}

Motor MecanumCar::getRearRightMotor() const
{
    return Motor(rearRight); 
}