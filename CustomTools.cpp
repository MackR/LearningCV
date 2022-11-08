#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>

#define GET_VARIABLE_NAME(Variable) #Variable
#define DISPLAYIMAGE(img) displayImages(img, #img)

void displayImages(std::vector<cv::Mat> imgs, std::vector<std::string> names = {}, int displayTime = 0){ // CustomTools.cpp function for easy display
    
    int nameNum = names.size();
    int imgNum = imgs.size();
    if (imgNum == 0){std::cout << "No images given" << std::endl; return;}
    if (imgNum != nameNum && nameNum != 0) {std::cout << "ERROR: " << nameNum << " names given for " << imgNum << " images" << std::endl; return;}
    std::string name;
    for (int num = 0; num < imgNum; ++num){
        if (nameNum == 0) {name = "img" + std::to_string(num+1);}
        else {name = names[num];}
        cv::namedWindow(name,cv::WINDOW_AUTOSIZE);
        cv::imshow(name, imgs[num]);
    }
    std::cout << "displayImages()" << std::endl;
    cv::waitKey(displayTime);
    cv::destroyAllWindows();
}

void displayImages( cv::Mat img, std::string name = "img",  int displayTime = 0){ // CustomTools.cpp function for easy display
    
        cv::namedWindow(name,cv::WINDOW_AUTOSIZE);
        cv::imshow(name, img);

    std::cout << "displayImages() SingleImg" << std::endl;
    cv::waitKey(displayTime);
    cv::destroyAllWindows();
}

void floodFillLargestRegion(cv::Mat src, cv::Mat dst)
{ // Could modify this function to do largest 2, 3, 4 or 5 sections
    cv::threshold(src,dst,110,255,cv::THRESH_BINARY);
    uchar pixel = 0; // every pixel is a uchar because image is a mask 0-255
    int areaPrime = 0, area = 0;
    std::pair<int, int> location(0, 0), locationPrime(0, 0);
    for (int row = 0; row < dst.rows; ++row)
    {
        for (int col = 0; col < dst.cols; ++col)
        {
            pixel = dst.at<uchar>(row, col);
            if (pixel >= 200)
            {
                area = cv::floodFill(dst, cv::Point(col, row), 100);

                if (area < areaPrime)
                {
                    cv::floodFill(dst, cv::Point(col, row), 0);
                    std::cout << "Not a larger zone, moving on" << std::endl;
                }
                else if (area > areaPrime)
                {
                    std::cout << "New area found, reassigning. Old area, new area: " << areaPrime << ", " << area << std::endl;
                    areaPrime = area;
                    cv::floodFill(dst, cv::Point(locationPrime.first, locationPrime.second), 0);
                    locationPrime.first = col;
                    locationPrime.second = row;
                }
                else if (area == areaPrime)
                {
                    std::cout << "Areas are equal, do nothing" << std::endl;
                }
                else
                    std::cout << "Error, else condition reached, previously thought impossible" << std::endl;
                // std::cout << "Working on it, row, col, val: " << row << ", " << col << ", " << (int)pixel << std::endl;

                // cv::imshow("img2",backProject);
                // cv::waitKey(0);
            }
        }
    }
    cv::floodFill(dst, cv::Point(locationPrime.first, locationPrime.second), 255);

    std::cout << "Flood fill image processing complete" << std::endl;

    return;
}