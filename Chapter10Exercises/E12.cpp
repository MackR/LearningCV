#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>


int main(int argc, char** argv){
    std::string path = "../Resources/GreenDetail.jpg";
    cv::Mat img, proc;

    if (argc >1){
        cv::Mat img = cv::imread(argv[1],-1);
}

    cv::namedWindow("img", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("fImgPyr", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("fImgResize", cv::WINDOW_AUTOSIZE);
    if( img.empty()) {
        img = cv::imread(path, cv::IMREAD_COLOR);
        if( img.empty()) {
            std::cout << "No image provided";
            return -1;
        }
    }

    // Format image here
    cv::Mat fImgPyr, fImgResize;
    fImgPyr = img.clone();
    fImgResize = img.clone();

    cv::pyrDown(fImgPyr,fImgPyr);
    cv::pyrDown(fImgPyr,fImgPyr);
    cv::resize(fImgResize,fImgResize,cv::Size(700,450));


    // Process image here



    cv::imshow("img",img);
    cv::imshow("fImgPyr",fImgPyr);
    cv::imshow("fImgResize",fImgResize);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;

}

// Question response 
// The two images look different, one of them is grainy and has harder details, the pyrDown has smoothed out feature more, and seemingly less detail. 