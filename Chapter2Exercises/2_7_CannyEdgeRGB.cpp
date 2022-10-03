#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>

int main(int argc, char** argv){
    
    cv::VideoCapture cap;
    cap.open(std::string(argv[1]), 0);
    cv::namedWindow("Gray",cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Canny", cv::WINDOW_AUTOSIZE);

    cv::Mat img_rgb;
    cv::Mat img_gry, img_cny;

    for(;;){
        cap >> img_rgb;
        if(img_rgb.empty()) break;
        
        //cv::GaussianBlur(inputFrame,outputFrame, cv::Size(5,5),3,3);        
        //cv::GaussianBlur(outputFrame,outputFrame, cv::Size(5,5),3,3);
        cv::pyrDown(img_rgb,img_rgb);
        cv::cvtColor(img_rgb,img_gry, cv::COLOR_BGR2GRAY);
        cv::Canny( img_gry, img_cny, 100, 115, 5, true);
        cv::imshow("RGB", img_rgb);
        cv::imshow("Gray", img_gry);
        cv::imshow("Canny", img_cny);

        if(cv::waitKey(30) > 0) break;
        
    }

    cv::destroyWindow("Input");
    cv::destroyWindow("Output");
    
    
    return 0;
}