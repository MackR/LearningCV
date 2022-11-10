#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#include "../CustomTools.cpp"


int main(int argc, char** argv){
    std::string path = "../Resources/Aruco1.png";
    cv::Mat img;

    if (argc >1){
        img = cv::imread(argv[1],-1);
        //img2 = cv::imread(argv[2],-1);
}


    if( img.empty()) {
        img = cv::imread(path, cv::IMREAD_GRAYSCALE);
        //img2 = cv::imread(path2, cv::IMREAD_COLOR);
        if( img.empty()) {
            std::cout << "No image provided";
            return -1;
        }
    }

    // Format image here
    cv::Mat fImg = img.clone();
    cv::Mat fImgBW = fImg.clone();
    //cv::threshold(fImgBW,fImgBW,128,255,cv::THRESH_BINARY);
    cv::Mat fImgBWRot, fImgBWScale, fImgBWBoth;

    cv::warpAffine(fImgBW,fImgBWRot,cv::getRotationMatrix2D(cv::Point2f(fImgBW.cols/2,fImgBW.rows/2),20,1.0),cv::Size(fImgBW.cols*1.2,fImgBW.rows*1.2),cv::WARP_FILL_OUTLIERS,cv::BORDER_REPLICATE);
    fImgBWScale = fImgBW.clone();
    cv::copyMakeBorder(fImgBWScale,fImgBWScale,50,50,50,50,cv::BORDER_CONSTANT, cv::Scalar(0,0,0));
    DISPLAYIMAGE(fImgBWScale);
    cv::Mat rotation = cv::getRotationMatrix2D(cv::Point2f(fImgBWScale.cols/2,fImgBWScale.rows/2),0,1.5);
    cv::warpAffine(fImgBWScale,fImgBWScale,rotation,cv::Size(fImgBWScale.cols,fImgBWScale.rows),cv::WARP_FILL_OUTLIERS,cv::BORDER_REPLICATE);
    DISPLAYIMAGE(fImgBWRot);
    DISPLAYIMAGE(fImgBWScale);
    // Process image here

    cv::Moments mom = cv::moments(fImgBW,false);
    cv::Moments momRot = cv::moments(fImgBWRot,false);
    cv::Moments momScale = cv::moments(fImgBWScale,false);

    double huMoments[3][7] = {};
    cv::HuMoments(mom,huMoments[0]);
    cv::HuMoments(mom,huMoments[1]);
    cv::HuMoments(mom,huMoments[2]);

    for (auto moms: huMoments){
        std::cout << moms[0] << std::endl;
        std::cout << moms[1] << std::endl;
        std::cout << moms[2] << std::endl;
        std::cout << moms[3] << std::endl;
        std::cout << moms[4] << std::endl;
        std::cout << moms[5] << std::endl;
        std::cout << moms[6] << std::endl;
        std::cout << "Next set" << std::endl;
    }
    cv::Mat img2 = cv::imread("../Resources/Aruco2.png",cv::IMREAD_GRAYSCALE);
    cv::threshold(img2,img2,128,255,cv::THRESH_BINARY);

    double closeness = cv::matchShapes(fImgBWScale,fImgBWScale,cv::CONTOURS_MATCH_I1,1);
    double closenessAlt = cv::matchShapes(fImgBWRot,img2,cv::CONTOURS_MATCH_I1,1);

    std::cout << "Closeness match is: " << closeness << std::endl;
    std::cout << "Closeness non-match is: " << closenessAlt << std::endl;

    return 0;

}