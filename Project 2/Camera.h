#ifndef CAMERA_H
#define CAMERA_H

#include <string>

/*
 * Camera
 * ---
 * Represents a simulated Pi Camera module for terminal testing.
 * In this simplified model we track:
 *  - whether video streaming is currently active
 *  - how many simulated frames have been captured
 */
class Camera {
private:
    bool streaming; // True if camera stream is active
    int frameCount; // Total number of frames captured

public:
    // Default constructor
    Camera();

    // Start streaming
    void startStreaming();

    // Stop streaming
    void stopStreaming();

    // Capture a frame at coordinates (x, y)
    void captureFrame(int x, int y);

    // Checks if the camera is currently streaming
    bool isStreaming() const;

    // Gets the total frames captured so far
    int getFrameCount() const;
};

#endif // CAMERA_H
