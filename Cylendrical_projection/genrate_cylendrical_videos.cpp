#include <bits/stdc++.h>
#include <opencv2/core/cuda.hpp>
#include <opencv2/cudafeatures2d.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/cudawarping.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/stitching/detail/warpers.hpp>
#include <string>
#include <time.h>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/features2d.hpp>
#include "../headers/homographer.h"
#include "../headers/cylendricalWarper.h"


cv::Mat shiftFrame(cv::Mat image, int x, int y, cv::Size_<int> maskSize) {
    cv::Mat shift = (cv::Mat_<double>(3, 3) << 1, 0, x, 0, 1, y, 0, 0, 1);
    cv::warpPerspective(image, image, shift, maskSize);
    return image;
  }

int main(){
    // cv::VideoCapture video1("Cylendrically_projected_videos/front_videos/Left_cyl.mp4");
    // cv::VideoCapture video2("Cylendrically_projected_videos/front_videos/Mid_cyl.mp4");
    // cv::VideoCapture video3("Cylendrically_projected_videos/front_videos/Right_cyl.mp4");
     
    /* cv::VideoCapture video1("/home/karthik/workspace/Phase-2/input_videos_new/front_videos/F.mp4"); */
    /* cv::VideoCapture video2("/home/karthik/workspace/Phase-2/input_videos_new/front_videos/FL.mp4"); */
    /* cv::VideoCapture video3("/home/karthik/workspace/Phase-2/input_videos_new/front_videos/FR.mp4"); */

    /* cv::VideoCapture video1("/home/karthik/workspace/Phase-2/input_videos_new/back_videos/B.mp4"); */
    /* cv::VideoCapture video2("/home/karthik/workspace/Phase-2/input_videos_new/back_videos/BL.mp4"); */
    /* cv::VideoCapture video3("/home/karthik/workspace/Phase-2/input_videos_new/back_videos/BR.mp4"); */

    cv::VideoCapture video1("/home/karthik/workspace/Phase-2/input_videos_new/side_videos/L.mp4");
    cv::VideoCapture video2("/home/karthik/workspace/Phase-2/input_videos_new/side_videos/R.mp4");

    // cv::VideoCapture video1("/home/karthik/workspace/Phase-1/sift_video_stitch/Three_Video_feeds/sift_cpu/fingvideos/center.mp4");
    // cv::VideoCapture video2("/home/karthik/workspace/Phase-1/sift_video_stitch/Three_Video_feeds/sift_cpu/fingvideos/left.mp4");
    // cv::VideoCapture video3("/home/karthik/workspace/Phase-1/sift_video_stitch/Three_Video_feeds/sift_cpu/fingvideos/right.mp4");

    cv::Mat input1, input2, input3;

    std::vector<int> inp1_dummy1, inp1_dummy2;
    std::vector<int> inp2_dummy1, inp2_dummy2;
    std::vector<int> inp3_dummy1, inp3_dummy2;

    CylendricalWarper Cwarper;
    cv::Mat input1_cyl;
    cv::Mat input2_cyl;
    cv::Mat input3_cyl;

    bool running = true;
    int i = 0;
    while (running)
    {
      video1 >> input1;
      video2 >> input2;
      /* video3 >> input3; */

      Cwarper.ProjectOntoCylinder(input1, input1_cyl, inp1_dummy1, inp1_dummy2, 1500);
      Cwarper.ProjectOntoCylinder(input2, input2_cyl, inp2_dummy1, inp2_dummy2, 1500);
      /* Cwarper.ProjectOntoCylinder(input3, input3_cyl, inp3_dummy1, inp3_dummy2, 1500); */
      cv::Size_<int> maskSize = cv::Size_<int>(input1_cyl.size().width * 3, input1_cyl.size().height);
      // Homography hestimator;
      // cv::Mat H_1 = hestimator.inputFrame(input2_cyl, input1_cyl);
      // cv::Mat H_1 = hestimator.inputFrame(input1_cyl, input2_cyl);
      std::cout << "frame_" << std::to_string(i) << " processed\n";
      cv::imwrite("output_frames/side/Left/Left_" + std::to_string(i) + ".png", input1_cyl);
      cv::imwrite("output_frames/side/Right/Right_" + std::to_string(i) + ".png", input2_cyl);
      /* cv::imwrite("output_frames/back/Mid/Mid_" + std::to_string(i) + ".png", input1_cyl); */
      /* cv::imwrite("output_frames/back/Left/Left_" + std::to_string(i) + ".png", input2_cyl); */
      /* cv::imwrite("output_frames/back/Right/Right_" + std::to_string(i) + ".png", input3_cyl); */
      i++;
    }
}
