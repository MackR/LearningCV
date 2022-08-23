#include <iostream>
#include <opencv2/opencv.hpp>
static cv::Scalar color = {0,0,0};
void interpretMouse(int event, int x, int y, int flags, void* img){
    // interpret the ambiguous pointer to image
    
    cv::Mat img1 = *((cv::Mat*)img);

    if(cv::EVENT_MOUSEMOVE == 0 || cv::EVENT_RBUTTONDOWN) {
        if(flags & 1){
            cv::line(img1,{x,y},{x,y},color,2,8);
            
        }
        else if(flags & 2){
            color = img1.at<cv::Vec3b>(y,x);
            cv::Mat selectedColor(200,200,CV_8UC3,color);
            cv::namedWindow("Color Display", 1);
            cv::imshow("Color Display",selectedColor);
            cv::moveWindow("Color Display",400,400);
            color = img1.at<cv::Vec3b>(y,x);
            // cv::destroyWindow("Color Display");
        }
    }
}

int main(int argc, char** argv){

    std::string path = "../../Resources/Greenery.jpg";
    cv::Mat img = cv::imread(path);
    int rows = img.rows;
    int cols = img.cols;

    // int points(2,4);
    // points

    cv::circle(img,{rows*3/10,cols*3/10},rows/10/2,{0,0,250},2,4);
    cv::ellipse(img,{rows*4/10,cols*4/10},{rows/20,cols/40},0,0,180,{255,0,0},2,8);
    // cv::fillConvexPoly(img,,{255,255,0},cv::LINE_AA);
    cv::namedWindow("img",1);

    for(;;){
    
    if (cv::waitKey(1) == 27) break; 
    cv::setMouseCallback("img",interpretMouse, &img);
    cv::imshow("img",img);

    }

    // cv::waitKey(0);

    

    

    return 0;
}