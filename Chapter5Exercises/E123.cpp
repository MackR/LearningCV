#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char** argv){

    cv::namedWindow("src", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("src2", cv::WINDOW_AUTOSIZE);
    
    cv::Mat src = cv::Mat::zeros(100,100,CV_8UC3) ;
    cv::Mat src2 = cv::Mat::zeros(100,100,CV_8UC3) ;


    cv::Scalar color(100,50,50);
    cv::Scalar color2(0,255,0);

    cv::circle(src, {src.cols/2-1,src.rows/2-1}, 25, color, 3);
    //cv::Point p1(20,5);
    cv::Point p1(20,05);
    cv::Point p2(40,20);
    // //For Loops drawing
    // for(int col = p1.x; col < p2.x; ++col){
    //         src2.at<cv::Vec3b>(05,col)[1] = color2[1];
    //         src2.at<cv::Vec3b>(20,col)[1] = color2[1];
    // }
    // for(int row = p1.y; row <= p2.y; ++row){
    //         src2.at<cv::Vec3b>(row,20)[1] = color2[1];
    //         src2.at<cv::Vec3b>(row,40)[1] = color2[1];
    // }
    
    // Pointer arithmetic drawing
    for (int row = p1.y; row < p2.y; ++row){
        const float* Mrow = src2.ptr<float>(row);
        for(int col = p1.x; col < p2.x; ++col){
            src2.at<cv::Vec3b>(col,row)[1] = color2[1];
        }
    }

    cv::imshow("src", src);
    cv::imshow("src2", src2);
    
    cv::waitKey();

    cv::destroyWindow("src");




    return 0;
}