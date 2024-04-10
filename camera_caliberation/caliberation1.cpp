#include <bits/stdc++.h>
#include <opencv2/calib3d.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

cv::Mat CalibrateCamera(const std::string &imagesPath, int cornersPerCol, int cornersPerRow, float squareSize) {

    int G_ROWS;
    int G_COLS;
    std::vector<std::vector<cv::Point2f>> corners_2d;
    std::vector<cv::Point2f> corners;
    std::vector < std::string > images;
    cv::Mat gray_img;
    std::vector<std::vector<cv::Point3f>> corners_3d;
    cv::glob(imagesPath, images);
   
    for (int i = 0; i <  images.size(); ++i) {
        std::vector<cv::Point3f> temp_vec;
        for (int c = 0; c < cornersPerRow; ++c) {
            for (int r = 0; r < cornersPerCol; ++r) {
                cv::Point3f temp_sub_vec{ c * squareSize, r * squareSize, 0.0f };
                temp_vec.push_back(temp_sub_vec);
            }

        }
        corners_3d.push_back(temp_vec);
    }
   
    for (int i = 0; i < images.size(); i++) {
        cv::Mat image = cv::imread(images[i]);
        if (image.empty()) {
            std::cout << "ERROR cannot read the image" << std::endl;
        }
        // image dimensions
        G_ROWS = image.rows;
        G_COLS = image.cols;

        cv::cvtColor(image, gray_img, cv::COLOR_RGB2GRAY);

        bool is_found = cv::findChessboardCorners(gray_img, cv::Size(cornersPerCol, cornersPerRow), corners, cv::CALIB_CB_FAST_CHECK);

        if (is_found) {

            //sub pixel refinment
            cv::TermCriteria criteria(cv::TermCriteria::Type::EPS + cv::TermCriteria::Type::MAX_ITER, 30, 0.0001);
            cv::cornerSubPix(gray_img, corners, cv::Size(5, 5), cv::Size(-1, -1), criteria);
            corners_2d.push_back(corners);
            
           
        }
        else {
            std::cout << "ERROR could not find corners" << std::endl;
            std::cout << i << "\n";
        }
        
    }
    cv::Mat cameraMatrix, distCoeffs, R, T;
    std::cout << "Calibrating camera... Please wait, it might take few minutes." << std::endl;
    double reprojection_error = cv::calibrateCamera(corners_3d,corners_2d, cv::Size(G_COLS, G_ROWS),
                                            cameraMatrix,distCoeffs, R, T);
    std::cout << "Reprojection_error: " << reprojection_error << std::endl;
    return cameraMatrix;
}

int main(int argc, char const *argv[])
{
    std::string filePath = "/home/karthik/workspace/Phase-2/camera_caliberation/caliberationpics/frame_*.png";
    auto res = CalibrateCamera(filePath, 7, 6, 21);
    std::cout << res << "\n";
    return 0;
}
