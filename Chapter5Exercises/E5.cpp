#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv){

    cv::namedWindow("src", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("src2", cv::WINDOW_AUTOSIZE);
    
    cv::Mat src = cv::Mat::zeros(100,100,CV_8UC3) ;


    cv::Scalar color(100,50,50);

    cv::imshow("src", src);
    
    cv::waitKey();

    cv::destroyWindow("src");




    return 0;
}