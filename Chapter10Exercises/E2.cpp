#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>


int main(int argc, char** argv){
    //std::string path = "../Resources/Greenery.jpg";
    cv::Mat img(100,100,CV_8U,cv::Scalar(0.0,0.0,0.0)), smooth;
    cv::Size three(3,3), five(5,5), nine(9,9), eleven(11,11);

    img.at<uchar>(img.rows/2, img.cols/2) = 255;

    if (argc >1){
        cv::Mat img = cv::imread(argv[1],-1);
}

    cv::namedWindow("img", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("smooth", cv::WINDOW_AUTOSIZE);
    if( img.empty()) {
        //img = cv::imread(path, cv::IMREAD_COLOR);
        if( img.empty()) {
            std::cout << "No image provided";
            return -1;
        }
    }

    // Do image processing here
    cv::GaussianBlur(img,smooth,five,1.0,1.0);
    cv::GaussianBlur(smooth,smooth,five,1.0,1.0);


    cv::imshow("img",img);
    cv::imshow("smooth",smooth);
    cv::waitKey(0);
    cv::destroyWindow("img");
    return 0;

}