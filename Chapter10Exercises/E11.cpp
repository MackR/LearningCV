#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>


int main(int argc, char** argv){
    std::string path = "../Resources/PeanutButter.jpg";
    cv::Mat img, mod;

    if (argc >1){
        cv::Mat img = cv::imread(argv[1],-1);
}

    cv::namedWindow("img", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("proc", cv::WINDOW_AUTOSIZE);
    if( img.empty()) {
        img = cv::imread(path, cv::IMREAD_COLOR);
        if( img.empty()) {
            std::cout << "No image provided";
            return -1;
        }
    }
    // Format image here

    cv::Mat fImg = img.clone();
    while(fImg.rows > 800 || fImg.cols > 1600){
        cv::pyrDown(fImg,fImg);
    }
    cv::Mat copy = fImg.clone();
    cv::cvtColor(fImg,fImg,cv::COLOR_BGR2GRAY);

    // Do image processing here

    cv::Mat proc(fImg.rows,fImg.cols, CV_8U);
    cv::morphologyEx(fImg,proc,cv::MORPH_BLACKHAT,cv::Mat());
    cv::imshow("proc",proc);
    cv::waitKey(0);

    cv::compare(proc,10,proc,cv::CMP_GT);
    cv::imshow("proc",proc);
    cv::waitKey(0);
    std::cout << proc.size << std::endl;
    std::cout << fImg.size << std::endl;
    cv::Mat gray(fImg.rows,fImg.cols,CV_8U);
    gray.setTo(250);
    cv::copyTo(gray,fImg,proc);

    cv::imshow("img",fImg);
    cv::imshow("proc",copy);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;

}