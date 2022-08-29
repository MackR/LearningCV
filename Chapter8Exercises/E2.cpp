#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>

void onMouse(int event, int x, int y, int flags, void* img){

    cv::Mat image = *((cv::Mat*)img);
    cv::Point p(x,y);
    

    if (event == cv::EVENT_LBUTTONDOWN || flags & cv::EVENT_FLAG_LBUTTON){
        cv::Scalar color, black = {0,0,0,0}, white = {255,255,255,255};
        color = image.at<cv::Vec3b>(y,x);
        
        std::string textpt1 = "Pixel color at point " + 
        std::to_string(x) + ", " + std::to_string(y) + " is: ";
        std::string textpt2 =  
        std::to_string((int)color[0]) + ", " + 
        std::to_string((int)color[1]) + ", " + 
        std::to_string((int)color[2]);
        cv::Point textP1(5, 20);
        cv::Point textP2(5, 45);

        cv::Mat selectedColor(300,300,CV_8UC3,color);
        cv::Scalar textColor;
        if (color[0] + color[1] + color[2] < 100){
            textColor = white;
        }
        else textColor = black; 

        cv::putText(selectedColor,textpt1,textP1,cv::FONT_HERSHEY_COMPLEX,0.5,textColor);
        cv::putText(selectedColor,textpt2,textP2,cv::FONT_HERSHEY_COMPLEX,0.5,textColor);
        cv::namedWindow("Color Display", 1);
        cv::imshow("Color Display",selectedColor);
        cv::moveWindow("Color Display",400,400);
        // cv::destroyWindow("Color Display");
    }
}

int textCounter = 0;

int main(int argc, char** argv){
    std::string path = "../Resources/Greenery.jpg";

    cv::Mat orig, img;

    
    if(argc >1){
    orig = cv::imread(argv[1],-1);
    img = orig.clone();
    }

    cv::namedWindow("img", cv::WINDOW_AUTOSIZE);
    if( img.empty()) {
        orig = cv::imread(path, cv::IMREAD_COLOR);
        img = orig.clone();
        if( img.empty()) {
            std::cout << "No image provided";
            return -1;
        }
    }

    cv::setMouseCallback("img",onMouse, &img);


    // Do image processing here
int counter = 0;
while(1){

    cv::imshow("img",img);
    if(cv::waitKey(20) == 27) break;
    // if(counter > 100){
    //     img = orig.clone();
    //     counter = 0;
    // }
    // ++counter;
}
    cv::destroyWindow("img");
    return 0;

}