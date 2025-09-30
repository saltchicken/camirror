// main.cpp
#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // 1. Create a VideoCapture object to connect to the default camera (index 0)
    cv::VideoCapture cap(0);

    // 2. Check if the camera was opened successfully
    if (!cap.isOpened()) {
        std::cerr << "ERROR: Could not open camera." << std::endl;
        return -1;
    }

    // 3. Create a window to display the video
    cv::namedWindow("Live Camera Feed", cv::WINDOW_AUTOSIZE);

    // 4. Create a Mat object to store each frame from the camera
    cv::Mat frame;

    // 5. Loop to continuously capture and display frames
    while (true) {
        // Read a new frame from the camera
        bool frameReadSuccess = cap.read(frame);

        // If a frame was not read successfully (e.g., camera disconnected), break the loop
        if (!frameReadSuccess || frame.empty()) {
            std::cout << "Video stream ended." << std::endl;
            break;
        }

        // Display the frame in the created window
        cv::imshow("Live Camera Feed", frame);

        // Wait for 30ms. If the 'ESC' key (ASCII 27) is pressed, break the loop.
        if (cv::waitKey(30) == 27) {
            std::cout << "ESC key pressed. Exiting." << std::endl;
            break;
        }
    }

    // 6. Release the camera and destroy the window
    cap.release();
    cv::destroyAllWindows();

    return 0;
}
