#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>
#include <string>

using namespace cv;

int main() {
    // Read the image
    /* Mat image = imread("image.jpg"); */
    VideoCapture cap1("../stitching/video_panaroma/360_panaroma.mp4");
    Mat image; 
    bool running = true;
    int frame = 0;
    while(running){
        cap1 >> image;
        // Create a blank black mask (all zeros)
        Mat mask = Mat::zeros(Size_<int> (image.size().width, image.size().height), CV_8UC1); // Blank black mask

        // Get the dimensions of the image
        int imageHeight = image.rows;
        int imageWidth = image.cols;

        // Get the dimensions of the mask
        /* int maskHeight = mask.rows; */

        int maskHeight = 4000;
        int maskWidth = mask.cols;

        // Calculate the center position
        int centerX = (maskWidth - imageWidth) / 2;
        int centerY = (maskHeight - imageHeight) / 2;

        /* int centerY = (maskHeight * 4 - imageHeight) / 2; */
        // Create a black canvas four times the size of the mask
        Mat canvas = Mat::zeros(maskHeight, maskWidth, image.type());

        // Place the image onto the canvas at the center
        image.copyTo(canvas(Rect(centerX, centerY, imageWidth, imageHeight)));

        Rect reducedRoi(0, 0, canvas.size().width - 1000, canvas.size().height);
        if(frame > 600){
            break;
        }
        // Save the result
        imwrite("./mask_output/output_image_"  + std::to_string(frame) + ".png", canvas(reducedRoi));
        frame++;
        std::cout << "frame " << frame << " processed\n";
    }
    /* // Save the result */
    /* imwrite("output_image.jpg", canvas); */

    return 0;
}
