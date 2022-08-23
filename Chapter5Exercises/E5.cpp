#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>

int main(int argc, char** argv){

    cv::namedWindow("img");
    cv::namedWindow("img2");
    std::string path = "../Resources/Homer.png";
    cv::Mat img = cv::imread(path,cv::WINDOW_AUTOSIZE);
    cv::Mat orig = cv::imread(path,cv::WINDOW_AUTOSIZE);
    cv::Rect roi(cv::Point(50,150),cv::Point(300,300));

    cv::Mat mask = cv::Mat::zeros(img.size(),CV_8U);
    // mask(roi) = 1;
    std::vector<cv::Mat> colors;
    cv::split(img,colors);
    for (int row = 0; row < img.rows; row++){
        for( int col = 0; col < img.cols; col++){
            if(((int)colors[0].at<uint8_t>(row,col)-10 > (int)colors[1].at<uint8_t>(row,col)) 
            && ((int)colors[0].at<uint8_t>(row,col)-10 > (int)colors[2].at<uint8_t>(row,col))){
                mask.at<uint8_t>(row,col) = 1;
                // std::cout << "The color comparison Blue, Green, Red: " << (int)colors[0].at<uchar>(row,col) << ", " << (int)colors[1].at<uchar>(row,col) << ", " << (int)colors[2].at<uchar>(row,col) << "\n";
            }
            else {
                mask.at<uint8_t>(row, col) = 0;
                // std::cout << "skipped because: " << (int)colors[0].at<uchar>(row,col) << ", " << (int)colors[1].at<uchar>(row,col) << ", " << (int)colors[2].at<uchar>(row,col) << "\n";
        }
    }
    }
    cv::bitwise_and(img,cv::Scalar(0,0,0),img,mask);
    // cv::bitwise_not(img,img,mask);

    cv::imshow("img",img);
    cv::imshow("img2",orig);
    cv::waitKey(0);
    cv::destroyWindow("img");
    cv::destroyWindow("img2");

    return 0;
}