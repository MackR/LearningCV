#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>


int main(int argc, char** argv){
    
    cv::RNG myRNG = cv::theRNG();
    cv::Mat1f fThree(1,3);
    myRNG.fill(fThree,cv::RNG::UNIFORM,0.f,1.f);
    std::cout << "fThree is: " << fThree << "\n";

    cv::Mat1d dThree = cv::Mat::zeros(1,3,CV_32FC1);
    myRNG.fill(dThree,cv::RNG::NORMAL,0.0,1.0);
    std::cout << "dThree is: " << dThree << "\n";

    cv::Mat1b bThree = cv::Mat::zeros(1,3,CV_8U);
    myRNG.fill(bThree,cv::RNG::UNIFORM,0,256); // Fills with ints of 0-255 inclusive
    std::cout << "bThree is: " << bThree << "\n";

    cv::Mat bThree20 = cv::Mat::zeros(1,20,CV_8UC3);
    myRNG.fill(bThree20,cv::RNG::UNIFORM,0,256); // Fills with ints of 0-255 inclusive
    std::cout << "bThree20 triplets is: " << bThree20 << "\n";
    
    
    return 0;

}