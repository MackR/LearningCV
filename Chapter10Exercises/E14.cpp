// // Approximate a bilateral (edge preserving) smoothing filter. Find the major edges
// in an image and hold these aside. Then use cv::pyrMeanShiftFiltering() to
// segment the image into regions. Smooth each of these regions separately and
// then alpha-blend these smooth regions together with the edge image into one
// whole image that smooths regions but preserves the edges.

// Methods to find major edges: erosion and bitwise xor, two similar images and subtraction, morphological gradient, sobel filter, scharr, and laplacian

#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>


int main(int argc, char** argv){
    std::string path = "../Resources/NoPeanutButter.jpg";
    //std::string path2 = "../Resources/img2.jpg";
    cv::Mat img;
    //cv::Mat img2;

    if (argc >1){
        cv::Mat img = cv::imread(argv[1],-1);
        //cv::Mat img2 = cv::imread(argv[2],-1);
}

    cv::namedWindow("original", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("interiors", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("edges", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("result", cv::WINDOW_AUTOSIZE);
    if( img.empty()) {
        img = cv::imread(path, cv::IMREAD_COLOR);
        //img2 = cv::imread(path2, cv::IMREAD_COLOR);
        if( img.empty()) {
            std::cout << "No image provided";
            return -1;
        }
    }

    // Format image here
    cv::Mat fImg = img.clone();
    cv::resize(fImg,fImg,cv::Size(600,600));
    cv::cvtColor(fImg,fImg,cv::COLOR_BGR2GRAY);


    // Process image here
    cv::Mat proc1 = fImg.clone(), proc2 = fImg.clone();
    cv::Mat edgeMask,interiorMask, result;
    // cv::boxFilter(fImg,proc2,-1,cv::Size(5,5));
    // cv::imshow("proc1", proc1);
    // cv::waitKey(0);


    // cv::edgePreservingFilter(proc1,proc1);
    // cv::Laplacian(proc1,proc1,CV_8U);
    // cv::Scharr(proc1,proc1,CV_8U,0,1);
    //cv::boxFilter(proc1,proc1,-1,cv::Size(3,3));
    // cv::morphologyEx(proc1,proc1,cv::MORPH_CLOSE,cv::Mat());
    // cv::dilate(proc1,proc1,cv::Mat());
    cv::Canny(proc1,proc1,50,55);
    // cv::Sobel(proc1,proc1,CV_8U,1,0);
    // cv::Sobel(proc2,proc2,CV_8U,0,1);
    cv::compare(proc1,0,edgeMask,cv::CMP_NE); // create a mask by finding where edges are
    cv::threshold(edgeMask,edgeMask,1,255,cv::THRESH_BINARY);
    cv::dilate(edgeMask,edgeMask, cv::Mat());
    cv::dilate(edgeMask,edgeMask, cv::Mat());
    cv::compare(edgeMask,0,interiorMask,cv::CMP_EQ); // get the inverse of the edge mask

    cv::imshow("interiors",edgeMask);
    cv::imshow("edges",interiorMask);
    cv::waitKey(0);

    cv::Mat interiors = fImg.clone();
    cv::boxFilter(interiors,interiors,CV_8U,cv::Size(9,9)); // blur an image
    cv::imshow("interiors",interiors);
    cv::waitKey(0);

    interiors.setTo(0,edgeMask);

    cv::Mat edges = fImg.clone();
    edges.setTo(0,interiorMask); 

    std::cout << "Showing the image with the edges set to 0" << std::endl;
    cv::imshow("interiors",interiors);
    cv::imshow("edges",edges);
    cv::waitKey(0);

    // cv::threshold(proc1,proc1,50,255,cv::THRESH_TOZERO);
    // cv::threshold(proc2,proc2,50,255,cv::THRESH_TOZERO);

    // cv::bitwise_or(proc1,proc2,proc1);
    // cv::threshold(proc1,proc1,100,255,cv::THRESH_TOZERO);

    // cv::erode(proc1,proc2,cv::Mat()); // Erode and xor is not very good if the edges aren't already sharp
    // cv::bitwise_xor(proc1,proc2,proc1);
    // cv::imshow("proc1",proc1);
    // cv::waitKey(0);
    // cv::boxFilter(proc2,proc2,-1,cv::Size(5,5));
    cv::add(interiors,edges,result);
    std::cout << "Showing the images combined with good edges" << std::endl;
    cv::imshow("interiors",interiors);
    cv::imshow("original",fImg);
    cv::imshow("edges",edges);
    cv::imshow("result",result);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;

}