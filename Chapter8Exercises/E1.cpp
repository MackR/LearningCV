#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>


int main(int argc, char** argv){
    
    cv::VideoCapture cap;
    cv::namedWindow("RGB",cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Gray",cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Canny Edge",cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Combo",cv::WINDOW_AUTOSIZE);
    cap.open("../Resources/Avatar.mp4");
    
    cv::Mat img_rgb, img_gray, img_cny, img_combo, holder;
    cv::Mat grayrgb, cnyrgb;

    
    // Format the image to be the right dimensions without actually modifying the original file
    // holder = cv::Mat::zeros(cap.get(cv::CAP_PROP_FRAME_HEIGHT),cap.get(cv::CAP_PROP_FRAME_WIDTH), cap.get(cv::CAP_PROP_CODEC_PIXEL_FORMAT));
    cap >> img_rgb;
    cv::pyrDown(img_rgb,img_rgb);

    // Make the combo the same dimensions as the holder after pyramid down compression
    img_combo = cv::Mat::zeros(img_rgb.rows,img_rgb.cols*3,img_rgb.type());
    cv::Mat combo1 = img_combo.colRange(0,img_combo.cols/3);
    cv::Mat combo2 = img_combo.colRange(img_combo.cols/3,2*img_combo.cols/3);
    cv::Mat combo3 = img_combo.colRange(2*img_combo.cols/3,img_combo.cols);

    while(1){
        
        cap >> img_rgb;
        if(img_rgb.empty()) break;
        

        cv::pyrDown(img_rgb,img_rgb);
        cv::cvtColor(img_rgb, img_gray,cv::COLOR_RGB2GRAY);
        cv::Canny(img_gray,img_cny,30.0, 60, 3);

        cv::cvtColor(img_gray,grayrgb,cv::COLOR_GRAY2RGB);
        cv::cvtColor(img_cny,cnyrgb,cv::COLOR_GRAY2RGB);
        img_rgb.copyTo(combo1);
        grayrgb.copyTo(combo2);
        cnyrgb.copyTo(combo3);

        cv::imshow("RGB",img_rgb);
        cv::imshow("Gray",img_gray);
        cv::imshow("Canny Edge",img_cny);
        cv::imshow("Combo",img_combo);

        if(cv::waitKey(33) == 27) break;

    }
    cap.release();
    cv::destroyAllWindows();
    
    return 0;

}