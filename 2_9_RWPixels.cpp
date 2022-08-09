#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include <cmath>

int main(int argc, char** argv){
    
    cv::VideoCapture cap;
    cap.open(std::string(argv[1]), 0);
    cv::namedWindow("Gray",cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Canny", cv::WINDOW_AUTOSIZE);

    cv::Mat img_rgb;
    cv::Mat img_gry, img_cny;

    int x = 100, y = 100;
    
int counter = 0;
int shift = 1;
    for(;;){
        
        cap >> img_rgb;

        if(img_rgb.empty()) break;

        cv::Vec3b intensity = img_rgb.at< cv::Vec3b >(y,x);
        uchar blue = intensity[0];
        uchar green = intensity[1];
        uchar red = intensity[2];
        
        //cv::GaussianBlur(inputFrame,outputFrame, cv::Size(5,5),3,3);        
        //cv::GaussianBlur(outputFrame,outputFrame, cv::Size(5,5),3,3);
        cv::pyrDown(img_rgb,img_rgb);
        cv::cvtColor(img_rgb,img_gry, cv::COLOR_BGR2GRAY);
        cv::Canny( img_gry, img_cny, 100, 115, 5, true);
        for (int i = -10; i <10; i++){
            int directionx = 1, directiony =1;
            int xa = i+directionx*counter;
            int ya = -0.25*pow(i,2) + directiony*counter;
        img_cny.at<uchar>(x+ya+counter,y+xa+counter) = 255;
        img_rgb.at<uchar>(x+ya+counter,y+xa+counter) = [255,0,50];
        }
        
        cv::imshow("RGB", img_rgb);
        cv::imshow("Gray", img_gry);
        cv::imshow("Canny", img_cny);

        if(cv::waitKey(30) > 0) break;
        if(counter >100 || counter < 0){
            shift *= -1;
        }

         counter += shift;
    }

    cv::destroyWindow("Input");
    cv::destroyWindow("Output");
    
    
    return 0;
}