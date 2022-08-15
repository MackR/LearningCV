#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char** argv){

    float num  = -15.6;
    float num1 = abs(num);
    float num2 = cvCeil(abs(num));
    float num3 = cvFloor(abs(num));

    std::cout << "The float's magnitude, ceiling, and floor, are as follow: " << num1 << " " << num2 << " " << num3 << std::endl;
    
    cv::Point2f p(-5.5, -12);
    
    std::cout << "p is a float Point" << p << std::endl;
    p = (cv::Point)p;
    std::cout << "p is a regular Point" << p << std::endl;
    cv::Point p2(4,20);
    std::cout << "p2 is a regular Point" << p2 << std::endl;
    p2 = (cv::Point2f)p2;
    std::cout << "p2 is a float Point" << p2 << std::endl << std::endl;

    cv::Matx33f smallMat(1,2,3,4,5,6,7,8,9);
    cv::Vec3f smallVec({11,12,13});

    std::cout << "The small mat and vecs are: " << smallMat << " and " << smallVec << std::endl;
    
    cv::Matx31f product = smallMat*smallVec;

    std::cout << "The small mat product is: " << product << std::endl;

    cv::Mat m1(3,3,CV_16FC1, 1.2f);
    //cv::Vec<CV_16FC1,3> m2;

    return 0;
}