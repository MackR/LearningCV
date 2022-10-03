#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>

int main(int argc, char** argv){
    
    cv::VideoCapture cap;
    cap.open(std::string(argv[1]), 0);
    cv::namedWindow("Input",cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Output", cv::WINDOW_AUTOSIZE);

    cv::Mat inputFrame;
    cv::Mat outputFrame;

    for(;;){
        cap >> inputFrame;
        if(inputFrame.empty()) break;
        cv::imshow("Input", inputFrame);
        //cv::GaussianBlur(inputFrame,outputFrame, cv::Size(5,5),3,3);        
        //cv::GaussianBlur(outputFrame,outputFrame, cv::Size(5,5),3,3);
        cv::pyrDown(inputFrame, outputFrame);
        cv::imshow("Output", outputFrame);

        if(cv::waitKey(1) > 0) break;
        
    }

    cv::destroyWindow("Input");
    cv::destroyWindow("Output");
    
    
    return 0;
}