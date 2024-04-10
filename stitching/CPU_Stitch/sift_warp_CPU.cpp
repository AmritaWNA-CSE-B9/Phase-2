#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>
#include <opencv2/stitching/detail/warpers.hpp>
#include <time.h>
#include <opencv4/opencv2/opencv.hpp>
#include <opencv4/opencv2/features2d.hpp>
#include "../../headers/homographer.h"
//function declarations

// shift frame
cv::Mat shiftFrame(cv::Mat, int x, int y, cv::Size_<int> maskSize);

// stitching function
cv::Mat Stitcher(std::vector<cv::Mat> Frames, std::vector<cv::Mat> H_Mats, cv::Size_<int> maskSize);

int main(){
    // cv::VideoCapture video1("../video_panaroma/front_panoroma.mp4");
    // /* cv::VideoCapture video2("./back_videos/Mid_cyl.mp4"); */
    // cv::VideoCapture video2("../side_videos/Left_cyl.mp4");
    // /* cv::VideoCapture video3("./back_videos/Right_cyl.mp4"); */
    // cv::VideoCapture video3("../video_panaroma/back_panorma.mp4");
     
    cv::VideoCapture video1("/home/karthik/workspace/Phase-2/stitching/back_videos/Left_cyl.mp4");
    cv::VideoCapture video2("/home/karthik/workspace/Phase-2/stitching/back_videos/Mid_cyl.mp4");
    cv::VideoCapture video3("/home/karthik/workspace/Phase-2/stitching/back_videos/Right_cyl.mp4");
    cv::Mat Frame1;
    cv::Mat Frame2;
    cv::Mat Frame3; 
     
    bool isFrame1Active = video1.read(Frame1);
    bool isFrame2Active = video2.read(Frame2);
    bool ifFrame3Active = video3.read(Frame3);

    cv::Size_<int> maskSize = cv::Size_<int>(Frame2.size() * 3);
    // Frame2 = shiftFrame(Frame2, Frame2.size().width * 3, 0, cv::Size_<int>(maskSize.width, Frame1.size().height + (Frame1.size().height / 2)));
    Frame2 = shiftFrame(Frame2, Frame2.size().width, 0, cv::Size_<int>(maskSize.width, Frame1.size().height + (Frame1.size().height / 2)));
    auto t1 = std::chrono::high_resolution_clock::now();
    Homography hestimator;
    std::cout << "caliberation and estimating homography ... \n";
    cv::Mat h1 = hestimator.inputFrame(Frame1, Frame2);
    cv::Mat h2 = hestimator.inputFrame(Frame3, Frame2);

    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() / (float)1000; double fps = 1000 / (double)duration;
    std::cout << "Homography computation time : " << duration << " milliseconds\n";

    bool running = true;

    int frameCount = 0, windowSize = 1000;
    std::vector<float> frameTimeList;
    bool rendering = true;
    float fps_sma = 0.0f, frameTime_sma = 0.0f;
    float fps_wma = 0.0f, frameTime_wma = 0.0f, totalWeight = 0.0f;

    // recording FPS data
    std::ofstream myfile;
    myfile.open("./FPS_CPU_FINAL.csv");
    myfile << "Frame," << "SMA,"  << "WMA" << std::endl;
    try{
        while(running){
            // online phase start
            frameTime_sma = 0.0f;
            frameTime_wma = 0.0f;
            totalWeight = 0.0f;
            auto t1 = std::chrono::high_resolution_clock::now();
            video1 >> Frame1;
            video2 >> Frame2;
            video3 >> Frame3;

            // looping result for 5000 frames
            if (frameCount <= 5000) {
              if (Frame1.empty() || Frame2.empty() || Frame3.empty()) {
                  std::cout << "Loop back\n";
                  video1.set(cv::CAP_PROP_POS_FRAMES, 0);
                  video2.set(cv::CAP_PROP_POS_FRAMES, 0);
                  video3.set(cv::CAP_PROP_POS_FRAMES, 0);
                  continue;
              }
            }

            cv::Mat result = Stitcher({Frame1, Frame2, Frame3}, {h1, h2}, maskSize);
            auto t2 = std::chrono::high_resolution_clock::now();
            cv::imshow("result", result);
            // cv::imwrite("./pano_res/pano_" + std::to_string(frameCount) + ".png", result);

            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() / (float)1000; double fps = 1000 / (double)duration; // Optional
            frameCount++; //Optional
            frameTimeList.push_back((float)duration);
            if(frameTimeList.size() > windowSize){frameTimeList.erase(frameTimeList.begin());} // Can also use a better method.
            
            for(int k = 0;k < frameTimeList.size();k++)
            {
              frameTime_sma += frameTimeList[k]; // There are better ways of doing this but for simplicity I am going with this.
            }
            
            for(int k = 0;k < frameTimeList.size();k++)
            {
              float w = (k + 1) / (float)frameTimeList.size();
              totalWeight += w;
              frameTime_wma += frameTimeList[k] * w; // There are better ways of doing this but for simplicity I am going with this.
            }

            fps_wma = 1000 / (float)(frameTime_wma / totalWeight);
            fps_sma = frameTimeList.size() / (frameTime_sma / (float)1000);
            std::cout << "FrameCount: " << frameCount << "\n";
            std::cout << "SMA: " << fps_sma << std::endl; 
            std::cout << "WMA: " << fps_wma << std::endl;
            myfile << frameCount << "," << fps_sma << "," << fps_wma << std::endl;
            // removing excess mask
            int key = cv::waitKey(10);
            if (key == 'q' || key == 27) { // 'q' key or Esc key (27) to exit
                running = false;
            }
        }
    }catch (const std::exception &e){
    }

    video1.release();
    video2.release();
    cv::destroyAllWindows();
}

// function expansions
cv::Mat shiftFrame(cv::Mat image, int x, int y, cv::Size_<int> maskSize) {
  cv::Mat shift = (cv::Mat_<double>(3, 3) << 1, 0, x, 0, 1, y, 0, 0, 1);
  cv::warpPerspective(image, image, shift, maskSize);
  return image;
}

cv::Mat Stitcher(std::vector<cv::Mat> Frames, std::vector<cv::Mat> H_Mats, cv::Size_<int> maskSize){ // Frames : {nonreference, reference, nonreference} , H_Mats : {homography Matrix 1, homography Matrix 2}
  cv::Mat transformedFrameLeft;
  cv::Mat transformedFrameRight;

  // shifting refernce
  // Frames[1] = shiftFrame(Frames[1], Frames[1].size().width * 3, 0, cv::Size_<int>(maskSize.width, Frames[0].size().height + (Frames[0].size().height / 2)));

  Frames[1] = shiftFrame(Frames[1], Frames[1].size().width, 0, cv::Size_<int>(maskSize.width, Frames[0].size().height + (Frames[0].size().height / 2)));
  // warping non reference to reference
  cv::warpPerspective(Frames[0], transformedFrameLeft, H_Mats[0], Frames[1].size());
  cv::warpPerspective(Frames[2], transformedFrameRight, H_Mats[1], Frames[1].size());
  
  // image additon and subtraction
  cv::Mat LeftFrame;
  cv::Mat RightFrame;
  cv::Mat ReferenceFrame = Frames[1];
  cv::subtract(transformedFrameLeft, ReferenceFrame, LeftFrame);
  cv::subtract(transformedFrameRight, ReferenceFrame, RightFrame);
  cv::Mat result;
  cv::add(LeftFrame, ReferenceFrame, result);
  cv::add(result, RightFrame, result);
  return result;
}