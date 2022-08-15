#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>

int main(int argc, char** argv){
    //I need a way of gathering the video file
    cv::VideoCapture cap;
    cap.open(std::string(argv[1]),0);
    cv::namedWindow("Vid1", cv::WINDOW_AUTOSIZE);

    // A way to contain the image
    cv::Mat frame;

    // A way to loop through the image
    for(;;){
        cap >> frame;
        if(frame.empty()) break;
        imshow("Vid1", frame);
        if(cv::waitKey(33) >= 0) break;

    }
    
    cv::destroyWindow("Vid1");
    

    
    return 0;
}