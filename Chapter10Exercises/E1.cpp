#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>


int main(int argc, char** argv){
    std::string path = "../Resources/Greenery.jpg";
    cv::Mat img, smooth;
    cv::Size three(3,3), five(5,5), nine(9,9), eleven(11,11);

    if (argc >1){
        cv::Mat img = cv::imread(argv[1],-1);
}

    cv::namedWindow("img", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("smooth", cv::WINDOW_AUTOSIZE);
    if( img.empty()) {
        img = cv::imread(path, cv::IMREAD_COLOR);
        if( img.empty()) {
            std::cout << "No image provided";
            return -1;
        }
    }

    // Do image processing here
    //cv::GaussianBlur(img,smooth,eleven,1.0,1.0);
    cv::blur(img,smooth, five);

    cv::imshow("smooth", smooth);
    cv::imshow("img",img);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;

}