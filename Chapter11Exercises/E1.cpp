#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>


int main(int argc, char** argv){
    std::string path = "../Resources/BlueChairOutside.jpg";
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
    cv::Mat fImg = img.clone(), fImgBW;
    cv::resize(fImg,fImg,cv::Size(600,600));
    cv::cvtColor(fImg,fImgBW,cv::COLOR_BGR2GRAY);
    //cv::Mat fImg2 = img2.clone();

    // Process image here
    cv::Mat proc, proc2;
    cv::imshow("proc",fImgBW);
    cv::waitKey(0);

    cv::Mat1f k5 = (cv::Mat1f(5,5) << 
    1,1,1,1,1,
    1,1,1,1,1,
    1,1,1,1,1,
    1,1,1,1,1,
    1,1,1,1,1);
    cv::Mat1f k3 = (cv::Mat1f(3,3) << 
    1,1,1,
    1,1,1,
    1,1,1);

    proc2 = fImgBW.clone();
    // cv::bitwise_not(fImgBW,proc);
    // cv::imshow("proc",proc);
    // cv::waitKey(0);
    cv::Laplacian(fImgBW,proc,CV_8U,3);
    cv::dilate(proc,proc,cv::Mat());
    cv::Laplacian(fImgBW,proc2,CV_8U,5);

    // cv::bitwise_or(proc,proc2,proc2);
    cv::erode(proc2,proc2,cv::Mat());
    
    // cv::dilate(proc,proc,cv::Mat());
    // cv::morphologyEx(proc,proc,cv::MORPH_OPEN,k3);


    cv::imshow("img",img);
    //cv::imshow("img2",img2);
    cv::imshow("proc",proc2);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;

}