#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <fstream>

int g_slider_position = 0; // tracks slider bar position
int g_run = 1, g_dontset = 0; //start out in single step mode
cv::VideoCapture g_cap; // Video capture stream


void onTrackbarSlide(int pos, void *){ // When we slide the trackbar,
    g_cap.set(cv::CAP_PROP_POS_FRAMES, pos); // Set the capture stream position
    if(!g_dontset) // If dontset is turned off
        g_run = 1; // set variable to run video
    g_dontset = 0; // 
}

int main(int argc, char** argv){

    cv::namedWindow("Example2_4",cv::WINDOW_AUTOSIZE); //create window
    g_cap.open(std::string(argv[1]),0); // open video file
    int frames = (int) g_cap.get(cv::CAP_PROP_FRAME_COUNT); // count number of frames in video
    int tmpw = (int) g_cap.get(cv::CAP_PROP_FRAME_WIDTH); // get the frame width
    int tmph = (int) g_cap.get(cv::CAP_PROP_FRAME_HEIGHT); // get the frame height

    std::cout << "Video has " << frames << " frames of dimensions(" << tmpw <<","<<tmph<<")."<<std::endl;

    cv::createTrackbar("Position", "Example2_4",&g_slider_position,frames,onTrackbarSlide);
    cv::Mat frame;

    for (;;){
        if(g_run != 0){
            g_cap >> frame; if(frame.empty()) break;
            int current_pos = (int)g_cap.get(cv::CAP_PROP_POS_FRAMES); // get the current frame from the video stream
            g_dontset = 1;

            cv::setTrackbarPos("Position", "Example2_4", current_pos);
            cv::imshow("Example2_4", frame);

            g_run-=1;
        }

        char c = (char) cv::waitKey(10);
        if(c == 's') // single step button
            {g_run = 1; std::cout << "single step, run = "<< g_run << std::endl;}
        if(c=='r')
            {g_run = -1; std::cout << "Run mode, run = " << g_run << std::endl;}
        if(c==27) break;
    }

    
    return 0;
}