#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#include "../CustomTools.cpp"


int main(int argc, char** argv){
    std::string path = "../Resources/circle.png";
    //std::string path2 = "../Resources/img2.jpg";
    cv::Mat img;
    //cv::Mat img2;

    if (argc >1){
        img = cv::imread(argv[1],-1);
        //img2 = cv::imread(argv[2],-1);
}

    if( img.empty()) {
        img = cv::imread(path, cv::IMREAD_COLOR);
        //img2 = cv::imread(path2, cv::IMREAD_COLOR);
        if( img.empty()) {
            std::cout << "No image provided";
            return -1;
        }
    }

    // Format image here
    cv::Mat fImg = img.clone();
    cv::resize(fImg,fImg,cv::Size(600,600));
    cv::Mat fImgBW = fImg.clone();
    cv::cvtColor(fImg,fImgBW,cv::COLOR_BGR2GRAY);
    //cv::Mat fImg2 = img2.clone();

    // Process image here
    cv::Mat proc = fImgBW.clone();
    cv::threshold(proc,proc,128,255,cv::THRESH_BINARY);
    cv::bitwise_not(proc,proc); // convert the black circle with white background to white circle with black background

    std::vector<std::vector<cv::Point>> contours;
    cv::Mat colorImg;
    cv::findContours(proc,contours,cv::RETR_CCOMP, cv::CHAIN_APPROX_NONE);
    cv::merge(std::vector<cv::Mat>{proc,proc,proc},colorImg);
    cv::drawContours(colorImg,contours,0, cv::Scalar(255,0,255),1);
    double length = cv::arcLength(contours[0],true);;
    std::vector<std::vector<cv::Point>> appContour;
    appContour.push_back(std::vector<cv::Point> {cv::Point(30,30)}); // put in a placeholder vector for the approxPolyDP to modify later
    cv::putText(colorImg,std::to_string(length)+ " pixels long", contours[0][0],cv::FONT_HERSHEY_COMPLEX,0.5,cv::Scalar(255,0,0));
    cv::rectangle(colorImg,cv::boundingRect(contours[0]),cv::Scalar(0,255,0));
    cv::approxPolyDP(contours[1],appContour[0],20,true); // The epsilon value is in terms of pixels
    cv::drawContours(colorImg,appContour,0, cv::Scalar(255,0,0),1);
    double appLen = cv::arcLength(appContour[0],true);
    cv::putText(colorImg,std::to_string(appLen)+" app curve length",appContour[0][0],cv::FONT_HERSHEY_COMPLEX,0.3,cv::Scalar(255,0,0));
    DISPLAYIMAGE(colorImg);
    return 0;

}