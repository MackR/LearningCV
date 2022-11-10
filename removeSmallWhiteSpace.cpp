#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#include "../CustomTools.cpp"


int main(int argc, char** argv){
    std::string paths[5];
    cv::Mat imgs[5];

    for (auto& img: imgs){
        int index = (&img-imgs);
        std::cout << "The index of image is: " << index << std::endl;
        std::string path = "../Resources/HuLetter" + std::to_string(index+1) + ".png";
        std::cout << "Path is called: " << path << std::endl;
        img = cv::imread(path,cv::IMREAD_GRAYSCALE);
        if(img.empty()){std::cout << "Error! Image " << index +1 << " is empty" << std::endl; return 0;}
        floodFillLargestRegion(img,img);
        std::string outPath = "../Resources/HuLetter" + std::to_string(index+1) + "Clean" + ".png";
        cv::imwrite(outPath,img);
        DISPLAYIMAGE(img);
    }


    // Format image here
    // cv::Mat fImg = img.clone();
    // cv::resize(fImg,fImg,cv::Size(600,600));
    //cv::Mat fImgBW = fImg.clone();
    //cv::cvtColor(fImg,fImgBW,cv::COLOR_BGR2GRAY);
    //cv::Mat fImg2 = img2.clone();

    // // Process image here
    // cv::Mat proc;



    // DISPLAYIMAGE(img);
    // DISPLAYIMAGE(proc);
    return 0;

    
}