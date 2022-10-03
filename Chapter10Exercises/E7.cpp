#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>


int main(int argc, char** argv){
    std::string path = "../Resources/GreenDetail.jpg";
    cv::Mat img, mod;

    if (argc >1){
        cv::Mat img = cv::imread(argv[1],-1);
}

    cv::namedWindow("img", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("mod", cv::WINDOW_AUTOSIZE);
    if( img.empty()) {
        img = cv::imread(path, cv::IMREAD_ANYCOLOR);
        if( img.empty()) {
            std::cout << "No image provided";
            return -1;
        }
    }
    // Format the image 
    cv::Mat fImg = img.clone();
    cv::cvtColor(fImg,fImg,cv::COLOR_BGR2HSV);
    while(fImg.rows > 750 || fImg.cols > 1000){
        cv::pyrDown(fImg,fImg);
    }

    // Do image processing here

    cv::Mat blueMask, saturationMask;
    cv::Mat copy1 = fImg.clone(), copy2 = copy1.clone();
    
    cv::Mat splice[3];
    cv::split(copy1, splice);
    cv::Mat hue = splice[0];
    cv::Mat saturation = splice[1];
    cv::Mat vibrance = splice[2];


    // cv::threshold(hue, blueMask,300, 300, cv::THRESH_TOZERO_INV);
    // cv::threshold(blueMask, blueMask,241, 241, cv::THRESH_TOZERO);

    cv::compare(splice[0],135,blueMask,cv::CMP_GE); // blue is generally within the 180-270 range of color
    cv::compare(hue,90,blueMask,cv::CMP_LE);
    cv::compare(blueMask,cv::Scalar(0,0,0), blueMask,cv::CMP_EQ); // Invert the mask, if an element isn't equal to zero, make it zero, and vice versa
    std::cout << "Showing the blue mask Inverted to get correct masking" << std::endl;
    cv::imshow("blueMask", blueMask);
    cv::waitKey(0);

    cv::compare(saturation,100,saturationMask,cv::CMP_GE);
    cv::bitwise_and(blueMask,saturationMask, blueMask,blueMask);
    std::cout << "Filtered the blue mask  using saturation" << std::endl;
    cv::imshow("blueMask", blueMask);
    cv::waitKey(0);

    cv::Mat inverseMask = blueMask.clone();
    cv::compare(blueMask,cv::Scalar(0,0,0), inverseMask,cv::CMP_EQ); // Invert the mask, if an element isn't equal to zero, make it zero, and vice versa
    cv::morphologyEx(blueMask,blueMask,cv::MORPH_CLOSE,cv::Mat(),cv::Point(-1,-1),2);
    // cv::morphologyEx(blueMask,blueMask,cv::MORPH_OPEN,cv::Mat());
    // cv::morphologyEx(blueMask,blueMask,cv::MORPH_CLOSE,cv::Mat());
    std::cout << "Blue Mask: Morphological opening" << std::endl;
    cv::imshow("blueMask", blueMask);
    cv::waitKey(0);

    // cv::Mat expandedBlueMask;
    // cv::dilate(blueMask,expandedBlueMask,cv::Mat());
    cv::subtract(copy1,copy1,copy1,blueMask); // delete all the areas that are within the blueMask
    // cv::subtract(copy2,copy2,copy2,inverseMask); // delete all the areas outside the blueMask
    cv::boxFilter(copy2,copy2,-1,cv::Size(5,5)); // blurr the areas remaining in the copy2, which is the blueMask
    cv::add(copy2,copy1,copy1,blueMask); // Combine the undeleted regions in each image to reassemble the original but with blurring

    cv::cvtColor(copy1,copy1,cv::COLOR_HSV2BGR);
    cv::cvtColor(fImg,fImg,cv::COLOR_HSV2BGR);
    cv::namedWindow("blueMask", cv::WINDOW_AUTOSIZE);
    cv::imshow("blueMask", blueMask);
    cv::namedWindow("result", cv::WINDOW_AUTOSIZE);
    cv::imshow("result", copy1);

    cv::imshow("img",fImg);
    // cv::imshow("mod",mod);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;

}