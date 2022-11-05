#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>

int main(int argc, char** argv){

    cv::namedWindow("Example3", cv::WINDOW_AUTOSIZE);
    cv::VideoCapture cap;
    cap.open(0); //open a video camera?

    cv::Mat frame;
    for(;;){
        cap >> frame; // take what's in capture and output it to the frame
        if(frame.empty()) break;
        cv::pyrDown(frame,frame);
        cv::imshow("Example3",frame);
        if(cv::waitKey(10) >= 0) break;
    }
    
    
    return 0;
}