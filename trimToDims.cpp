#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#include "CustomTools.cpp"


int main(int argc, char** argv){
    std::string paths[5] = {};
    cv::Mat imgs[5];
    std::string baseImageName = "HuLetter";
    int minRows = 10000, minCols = 10000;

    for (auto& img: imgs){
        int index = (&img-imgs);
        std::string path = "Resources/" + baseImageName + std::to_string(index+1) + ".png";
        std::cout << "Path is called: " << path << std::endl;
        img = cv::imread(path,cv::IMREAD_GRAYSCALE);
        if ( img.rows < minRows) minRows = img.rows;
        if (img.cols < minCols) minCols = img.cols;
    }

    for (auto& img: imgs){
        int index = (&img-imgs);
        if(img.empty()){std::cout << "Error! Image " << index +1 << " is empty" << std::endl; return 0;}
        //img = img(cv::Rect2i((img.cols-minCols)/2,(img.rows/minRows)/2,minCols,minRows));
        std::string outPath = "Resources/" + baseImageName + std::to_string(index+1) + "Clean" + ".png";
        cv::imwrite(outPath,img);
        DISPLAYIMAGE(img);
    }
    return 0;

}