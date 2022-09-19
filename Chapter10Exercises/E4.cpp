#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>


int main(int argc, char** argv){
    std::string path = "../Resources/Image1.jpg";
    std::string path2 = "../Resources/Image1Repeat.jpg";
    cv::Mat src1, src2, diff12, cleandiff, dirtydiff;
    cv::Size three(3,3), five(5,5), nine(9,9), eleven(11,11);


    if (argc >1){
        cv::Mat src1 = cv::imread(argv[1],-1);
}

    cv::namedWindow("src1", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("diff12", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("cleandiff", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("dirtydiff", cv::WINDOW_AUTOSIZE);
    if( src1.empty()) {
        src1 = cv::imread(path, cv::IMREAD_COLOR);
        src2 = cv::imread(path2, cv::IMREAD_COLOR);
        
        cv::pyrDown(src1,src1);
        cv::pyrDown(src1,src1);
        // cv::pyrDown(src1,src1);
        src1.adjustROI(-200,0,0,0);
        cv::pyrDown(src2,src2);
        cv::pyrDown(src2,src2);
        // cv::pyrDown(src2,src2);
        src2.adjustROI(-200,0,0,0);
        if( src1.empty()) {
            std::cout << "No image provided";
            return -1;
        }
    }

    // Do image processing here
    cv::absdiff(src1, src2, diff12);

    cv::erode(diff12,cleandiff,cv::Mat());
    cv::dilate(cleandiff,cleandiff,cv::Mat());

    cv::dilate(diff12,dirtydiff,cv::Mat());
    cv::erode(dirtydiff,dirtydiff,cv::Mat());

    cv::imshow("src1",src1);
    cv::imshow("diff12",diff12);
    cv::imshow("cleandiff",cleandiff);
    cv::imshow("dirtydiff",dirtydiff);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;

}