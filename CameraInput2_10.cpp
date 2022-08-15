#include <iostream>
#include <fstream>
#include <stdio.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main(int argc, char** argv){

    cv::VideoCapture cap;
    cv::namedWindow("Vid", cv::WINDOW_AUTOSIZE);
    if(argc == 1){
        cap.open(0);
    }
    else{
        cap.open(std::string(argv[1]));
    }
    if (!cap.isOpened()){
        std::cerr << "Couldn't open capture." << std::endl;
        return -1;
    }

    cv::Mat frame;

    for(;;){
        cap >> frame;
        if(frame.empty()){
            break;
        }
        cv::imshow("Vid",frame);

        if(cv::waitKey(37) == 0) break;
    }

cv::destroyWindow("Vid");

    return 0;
}