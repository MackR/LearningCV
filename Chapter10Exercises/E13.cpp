#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>


int main(int argc, char** argv){
    std::string path = "../Resources/GreenDetail.jpg";
    cv::Mat img;

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
    cv::resize(fImg,fImg,cv::Size(800,600));
    cv::cvtColor(fImg,fImg,cv::COLOR_BGR2GRAY);

    // Process image here
    cv::Mat proc;
    // cv::threshold(fImg,proc,128,255,cv::THRESH_BINARY);
    // cv::imshow("proc",proc);
    // cv::waitKey(0);

    // cv::threshold(fImg,proc,128,255,cv::THRESH_BINARY_INV);
    // cv::imshow("proc",proc);
    // cv::waitKey(0);

    // cv::threshold(fImg,proc,128,255,cv::THRESH_MASK);
    // cv::imshow("proc",proc);
    // cv::waitKey(0);

    // cv::threshold(fImg,proc,128,255,cv::THRESH_TOZERO);
    // cv::imshow("proc",proc);
    // cv::waitKey(0);

    // cv::threshold(fImg,proc,128,255,cv::THRESH_TOZERO_INV);
    // cv::imshow("proc",proc);
    // cv::waitKey(0);

    // cv::threshold(fImg,proc,128,255,cv::THRESH_TRUNC);
    // cv::imshow("proc",proc);
    // cv::waitKey(0);

    cv::adaptiveThreshold(fImg,proc,128,cv::ADAPTIVE_THRESH_GAUSSIAN_C,cv::THRESH_BINARY,3,0);
    cv::imshow("proc",proc);
    cv::waitKey(0);

    cv::adaptiveThreshold(fImg,proc,128,cv::ADAPTIVE_THRESH_MEAN_C,cv::THRESH_BINARY_INV,7,0);
    cv::imshow("proc",proc);
    cv::waitKey(0);

    cv::imshow("img",img);
    cv::imshow("proc",proc);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;

}