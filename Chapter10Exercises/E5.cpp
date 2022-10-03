#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>


int main(int argc, char** argv){
    std::string path1 = "../Resources/NoPeanutButter.jpg";
    std::string path2 = "../Resources/PeanutButter.jpg";
    std::string path3 = "../Resources/PeanutButter2.jpg";
    cv::Mat img1, img2, result;

    if (argc >1){
        cv::Mat img1 = cv::imread(argv[1],-1);
        cv::Mat img2 = cv::imread(argv[2],-1);
}

    cv::namedWindow("img1", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("img2", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("result", cv::WINDOW_AUTOSIZE);
    if( img1.empty() || img2.empty()) {
        img1 = cv::imread(path1, cv::IMREAD_COLOR);
        img2 = cv::imread(path2, cv::IMREAD_COLOR);
        if( img1.empty() || img2.empty()) {
            std::cout << "One image missing";
            return -1;
        }
    }

    // Format the images here
    cv::Mat fImg1 = img1.clone(), fImg2 = img2.clone();
    while(fImg1.rows > 700 || fImg1.cols > 1200){
        cv::pyrDown(fImg1,fImg1);
        cv::pyrDown(fImg2,fImg2);
    }

    cv::cvtColor(fImg1,fImg1,cv::COLOR_BGR2GRAY);
    cv::cvtColor(fImg2,fImg2,cv::COLOR_BGR2GRAY);


    // Do image processing here

    cv::Mat diff1, diff2;
    cv::absdiff(fImg1,fImg2,diff1);

    cv::threshold(diff1,diff1,50,255, cv::THRESH_BINARY);

    cv::imshow("result",diff1);
    cv::waitKey(0);

    cv::boxFilter(diff1,diff1,-1,cv::Size(5,5));
    cv::dilate(diff1,diff1,cv::Mat());
    cv::morphologyEx(diff1,diff1,cv::MORPH_OPEN, cv::Mat(), cv::Point(-1,-1),1);

    cv::erode(diff1,diff2,cv::Mat());
    cv::bitwise_xor(diff1,diff2, diff1);

    result = diff1;

    cv::imshow("img1",img1);
    cv::imshow("img2",img2);
    cv::imshow("result",result);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;

}