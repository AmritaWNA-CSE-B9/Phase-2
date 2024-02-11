#include <opencv2/opencv.hpp>
#include "./headers/cylendricalWarper.h"
#include "./headers/homographer.h"
#include <cmath>

int main() {
    // Read the input image
    cv::Mat input1 = cv::imread("./images/input/1.png");
    cv::Mat input2 = cv::imread("./images/input/2.png");
    cv::Mat input3 = cv::imread("./images/input/3.png");
	cv::Mat input1_cyl;
	cv::Mat input2_cyl;
    cv::Mat input3_cyl;
	std::vector<int> inp1_dummy1, inp1_dummy2;
	std::vector<int> inp2_dummy1, inp2_dummy2;
	std::vector<int> inp3_dummy1, inp3_dummy2;
    CylendricalWarper Cwarper;
    Cwarper.ProjectOntoCylinder(input1, input1_cyl, inp1_dummy1, inp1_dummy2);
    Cwarper.ProjectOntoCylinder(input2, input2_cyl, inp2_dummy1, inp2_dummy2);
    Cwarper.ProjectOntoCylinder(input3, input3_cyl, inp3_dummy1, inp3_dummy2);
    cv::Size_<int> maskSize = cv::Size_<int>(input1_cyl.size().width * 3, input1_cyl.size().height);
    Homography hestimator;
    cv::Mat H_1 = hestimator.inputFrame(input2_cyl, input1_cyl);

    cv::Mat right_side;
    cv::Mat left_side = cv::Mat::zeros(maskSize, input1_cyl.type());
    cv::Mat roi(left_side, cv::Rect(0, 0, input1_cyl.cols, input1_cyl.rows));
    input1_cyl.copyTo(roi);
    cv::warpPerspective(input2_cyl, right_side, H_1, maskSize);
    cv::Mat result_1;
    cv::subtract(right_side, left_side, right_side);
    cv::add(right_side, left_side, result_1);

    cv::Mat result_2;
    cv::Mat right_side_1;
    cv::imwrite("result1.png", result_1);
    cv::Mat H_2 = hestimator.inputFrame(input3_cyl, result_1);
    cv::warpPerspective(input3_cyl, right_side_1, H_2, maskSize);
    cv::subtract(result_1, right_side_1, result_1);
    cv::add(result_1, right_side_1, result_2);

    cv::imwrite("result_two.png", result_2);
    cv::Mat result_2_sperical_warp;
    sphericalWarp(result_2, result_2_sperical_warp);
    cv::imwrite("SphericalWarping.png", result_2_sperical_warp);
    // cv::Mat stitched_image;
    // cv::add(left_side, right_side, stitched_image);
    // cv::imwrite("right_side.png", right_side);
    // cv::Mat stitched_image;
    // cv::warpPerspective(input2_cyl, stitched_image, H, input1_cyl.size() * 2);

    // cv::Mat roi(stitched_image, cv::Rect(0, 0, input1_cyl.cols, input1_cyl.rows));
    // input1_cyl.copyTo(roi);
    // Perform spherical warping
    // sphericalWarp(input2, output);
    // sphericalWarp(input3, output);
    // cv::imwrite("output.png", stitched_image);
    // Display the input and output images
    cv::waitKey(0);

    return 0;
}