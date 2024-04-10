#include <iostream>
#include <opencv2/opencv.hpp>
#include <filesystem>

using namespace cv;
using namespace std;
// namespace fs = std::filesystem;

int main() {
    // Create a VideoCapture object to access the camera
    cv::VideoCapture cap(3);  // Use 0 for the default camera

    // Loop to capture frames
    int frameIndex = 0;
    int itr = 0;
    bool flag = true;
    while (true) {
        cv::Mat frame;
        // Capture frame-by-frame
        cap >> frame;

        // Check if the frame is empty
        if (frame.empty()) {
            cerr << "Error: Unable to capture frame!" << endl;
            break;
        }


        // Save the frame to the folder
        if(itr % 10 == 0) {
            
            flag = flag && (frameIndex <= 10);

            if(!flag){
                break;
            }

            std::string filename = "../caliberationpics/frame_" + to_string(frameIndex++) + ".png";
            cv::imwrite(filename, frame);
            std::cout << "Frame saved as " << filename << endl;

        }

        // Display the captured frame

        cv::namedWindow("frame", cv::WINDOW_NORMAL);
        cv::resizeWindow("frame", 600, 400);
        cv::imshow("frame", frame);
        itr ++;
        // Wait for a key press
        int key = waitKey(1);
        
        // Press 'q' to quit the loop
        if (key == 'q') {
            break;
        }
    }

    // Release the VideoCapture object
    cap.release();

    // Close all OpenCV windows
    cv::destroyAllWindows();

    return 0;
}
