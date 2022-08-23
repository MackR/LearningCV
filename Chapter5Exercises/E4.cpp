#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv){

    cv::namedWindow("src", cv::WINDOW_AUTOSIZE);
    // cv::namedWindow("src2", cv::WINDOW_AUTOSIZE);
    

    
    cv::Mat src = cv::Mat::zeros(210,210,CV_8U) ;
    cv::Mat mask = cv::Mat::zeros(src.size(),CV_8U);
    
    for(int i = 0; i <= 100; i +=10){
        // the mask is the same size as the image, 
        // but it has 1's where you want stuff to happen, and 0's where you don't
        mask.setTo(0);
        mask(cv::Rect(cv::Point(i,i),cv::Point(210-i,210-i))) = 1;

        src.setTo(i*2,mask); 
    
    }


    cv::imshow("src", src);
    
    cv::waitKey();

    cv::destroyWindow("src");




    return 0;
}