// main.cpp
#include <opencv2/opencv.hpp>
#include <opencv2/core/ocl.hpp>
#include <iostream>
#include <vector>

int main() {
    if (!cv::ocl::haveOpenCL()) {
        std::cerr << "OpenCL is not available..." << std::endl;
        return -1;
    }
    cv::ocl::setUseOpenCL(true);
    std::cout << "OpenCL is available. Proceeding with GPU acceleration via T-API." << std::endl;

    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "ERROR: Could not open camera." << std::endl;
        return -1;
    }

    cv::namedWindow("Live Camera Feed - Red Filter (OpenCL)", cv::WINDOW_AUTOSIZE);

    cv::Mat frame_cpu;
    cv::UMat u_frame, u_result;
    std::vector<cv::UMat> u_bgr_channels;
    cv::UMat u_zero; // Will be initialized on the first frame

    while (true) {
        if (!cap.read(frame_cpu) || frame_cpu.empty()) {
            std::cout << "Video stream ended." << std::endl;
            break;
        }

        // --- GPU Processing Starts Here ---

        frame_cpu.copyTo(u_frame);

        // Initialize the 'zero' UMat only once
        if (u_zero.empty()) {
            u_zero = cv::UMat::zeros(u_frame.size(), CV_8UC1);
        }

        cv::split(u_frame, u_bgr_channels);

        std::vector<cv::UMat> u_merged_channels = {
            u_zero,
            u_zero,
            u_bgr_channels[2]
        };

        cv::merge(u_merged_channels, u_result);

        // Get the result back to the CPU Mat for display
        u_result.copyTo(frame_cpu); // Use copyTo for safety
        
        // --- GPU Processing Ends Here ---

        cv::imshow("Live Camera Feed - Red Filter (OpenCL)", frame_cpu);

        if (cv::waitKey(1) == 27) {
            std::cout << "ESC key pressed. Exiting." << std::endl;
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}
