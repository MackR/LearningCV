#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>

int main(int argc, char** argv){

    cv::namedWindow("Vid1", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Vid2", cv::WINDOW_AUTOSIZE);
    //cv::namedWindow("Vid1", cv::WINDOW_AUTOSIZE);
    cv::VideoCapture cap;
    cap.open( std::string(argv[1])); //open a video camera?

    cv::Mat frame;
    cap >> frame;
    cv::Mat oldFrame=frame.clone();
    cv::Mat changesFrame = cv::Mat::zeros((int)cap.get(cv::CAP_PROP_FRAME_WIDTH), (int)cap.get(cv::CAP_PROP_FRAME_HEIGHT), CV_8U);
    int h = frame.rows/2; // frames will be pyramid downsampled later
    int w = frame.cols/2;
    cv::Point2i p(50, 30);
    cv::Point2i p2(20*h/100, 20*w/100);

    for(;;){
        cap >> frame; // take what's in capture and output it to the frame
        if(frame.empty()) break;
        cv::compare(frame, oldFrame,changesFrame, cv::CMP_EQ);
        cv::pyrDown(frame,frame);
        cv::circle(frame, p, 20,150, 2);
        cv::circle(frame, p, 30,{50,200,255}, 2);
        cv:: putText(frame,"Hello there", p2,cv::FONT_HERSHEY_PLAIN,5,{0,0,255});
        //cv::pyrDown(changesFrame,changesFrame);
        cv::imshow("Vid1",frame);
        //cv::imshow("Vid2",changesFrame);


        if(cv::waitKey(33) >= 0) break;
    }
    
    
    return 0;
}