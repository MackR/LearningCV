#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>
#include <iostream>
int main(int argc, char** argv)
{
    std::string path = "Resources/Simpsons.png";

    cv::Mat img = cv::imread(argv[1],-1);
    //std::printf("test print\n");
    if( img.empty()) return -1;
    cv::namedWindow("Example1", cv::WINDOW_AUTOSIZE);
    cv::imshow("Example1",img);
    //std::printf("test print2\n");
    cv::waitKey(0);
    cv::destroyWindow("Example1");
    //std::printf("test print3\n");
    return 0;
}