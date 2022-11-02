#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>


int main(int argc, char** argv){
    std::string path = "../Resources/HistogramEqualization.png";
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
    // cv::resize(fImg,fImg,cv::Size(600,600));
    cv::Mat fImgBW = fImg.clone();
    cv::cvtColor(fImg,fImgBW,cv::COLOR_BGR2GRAY);
    //cv::Mat fImg2 = img2.clone();

    // Process image here
    cv::Mat proc;

    cv::equalizeHist(fImgBW,proc);


    cv::imshow("img",img);
    //cv::imshow("img2",img2);
    cv::imshow("proc",proc);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;

}