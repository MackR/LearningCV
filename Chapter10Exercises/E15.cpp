#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>


int main(int argc, char** argv){
    std::string path = "../Resources/NoPeanutButter.jpg";
    //std::string path2 = "../Resources/img2.jpg";
    cv::Mat img;
    //cv::Mat img2;

    if (argc >1){
        cv::Mat img = cv::imread(argv[1],-1);
        //cv::Mat img2 = cv::imread(argv[2],-1);
}

    cv::namedWindow("img", cv::WINDOW_AUTOSIZE);
    //cv::namedWindow("img2", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("proc", cv::WINDOW_AUTOSIZE);
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
    //cv::cvtColor(fImg,fImgBW,cv::COLOR_BGR2GRAY);
    //cv::Mat fImg2 = img2.clone();

    // Process image here
    cv::Mat proc = fImg.clone();
    cv::Mat1f k = (cv::Mat1f(5,5)<< 0,1,0,0,0, 0,0,0,0,0, 0,0,-2,0,0, 0,0,0,0,0, 0,0,0,1,0);
    cv::Matx33d kernel1 = 
    {2,0,0,
    1,-6,1,
    0,0,2};
    // cv::Mat kernel2 = {0,0,1,  0,-1,0,  0,0,0};
    cv::filter2D(proc,proc,CV_8U,k);
    // cv::filter2D(proc,proc,CV_8U,kernel2);

    cv::imshow("img",fImg);
    //cv::imshow("img2",img2);
    cv::imshow("proc",proc);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;

}