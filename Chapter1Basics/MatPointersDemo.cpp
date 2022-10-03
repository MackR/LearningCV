#include "opencv2/highgui/highgui.hpp"
#include <stdio.h>
#include <iostream>
int main(int argc, char** argv)
{
    std::string path = "Resources/Homer.png";

    cv::Mat img = cv::imread(path);
    cv::Mat oldImg = img.clone();
    cv::Point2i p(100,100);
    std::cout << "The first pixel channel value at (100,100) of img is: " << (int)img.at<cv::Vec3b>(100,100)[0] << std::endl;
    std::cout << "The first pixel channel value before changes is: " << (int)oldImg.at<cv::Vec3b>(100,100)[0] << std::endl;
    oldImg.at<cv::Vec3b>(100,100)[0] = 0;
    std::cout << "The first pixel channel value after changes of img is: " << (int)img.at<cv::Vec3b>(100,100)[0] << std::endl;
    std::cout << "The first pixel channel value after changes of old is: " << (int)oldImg.at<cv::Vec3b>(100,100)[0] << std::endl << std::endl;

    std::cout << "The original mem location is: " << &img << std::endl;
    std::cout << "The old image copy mem location is: " << &oldImg << std::endl << std::endl;
    


    oldImg = img; 

    std::cout << "The first pixel after reassigned is: " << (int)oldImg.at<cv::Vec3b>(100,100)[0] << std::endl;

    //std::cout << "The pointers should point to the original: " << &img << std::endl;
    //std::cout << "The pointers should point to the original: " << &oldImg << std::endl;

    return 0;
}