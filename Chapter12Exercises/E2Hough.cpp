#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>


int main(int argc, char** argv){
    std::string path = "../Resources/BicycleHighContrast.jpg";
    //std::string path2 = "../Resources/img2.jpg";
    cv::Mat img;
    //cv::Mat img2;

    if (argc >1){
        cv::Mat img = cv::imread(argv[1],-1);
        //cv::Mat img2 = cv::imread(argv[2],-1);
}

    cv::namedWindow("img", cv::WINDOW_AUTOSIZE);
    //cv::namedWindow("img2", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("proc", cv::WINDOW_AUTOSIZE);
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
    cv::Mat fImgBW = fImg.clone();
    cv::cvtColor(fImg,fImgBW,cv::COLOR_BGR2GRAY);
    //cv::Mat fImg2 = img2.clone();

    // Process image here
    std::vector<cv::Point2f> lines;
    std::vector<cv::Point3f> circles;
    cv::Mat proc = fImgBW.clone();
    cv::GaussianBlur(proc,proc,cv::Size(7,7),1);
    cv::Canny(proc,proc,10,300);
    cv::imshow("proc", proc);
    cv::waitKey(0);

    cv::HoughLines(proc,lines,600,3.14,10);
    cv::HoughCircles(proc,circles,cv::HOUGH_GRADIENT,2,100); // This function is really tricky and can be confused easily depending on the parameters.

    for( size_t i = 0; i < circles.size(); ++i ) {
        cv::circle(fImg,cv::Point(cvRound(circles[i].x), cvRound(circles[i].y)),
        cvRound(circles[i].z),
        cv::Scalar(0,0,255),2,cv::LINE_AA);
    }
    // for( size_t i = 0; i < lines.size(); ++i ) {
    //     // cv::line(fImg,);
    // }


    cv::imshow("img",img);
    //cv::imshow("img2",img2);
    cv::imshow("proc",fImg);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;

}