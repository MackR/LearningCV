#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>

int main(int argc, char **argv)
{
    std::map<char,int> keyboard {
    {'1',1}, {'2',2}, {'3',3}, 
    {'4',4}, {'5',5}, {'6',6}, 
    {'7',7}, {'8',8}, {'9',9},
    {'!',-1}, {'@',-2}, {'#',-3}, 
    {'$',-4}, {'%',-5}, {'^',-6}, 
    {'&',-7}, {'*',-8}, {'(',-9}, {',', 5}, {'.', -5}};

    std::string path = "../Resources/Greenery.jpg";

    cv::Mat img;
    if (argc > 1)
    {
        cv::Mat img = cv::imread(argv[1], -1);
    }

    cv::namedWindow("combo", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("warped", cv::WINDOW_AUTOSIZE);

    if (img.empty())
    {
        img = cv::imread(path);
        if (img.empty())
        {
            std::cout << "No image provided" << std::endl;
            return -1;
        }
    }

    // Do image processing
    cv::Mat warpImg = img.clone();
    cv::Mat combo(img.rows,img.cols*2,img.type());
    cv::Mat comboPt1(combo, cv::Range::all(),cv::Range(0,combo.cols/2)), 
    comboPt2(combo, cv::Range::all(),cv::Range(combo.cols/2, combo.cols));
    img.copyTo(comboPt1);

    double zoomFactor = 1.0;
    double angle = 0;
    while (1)
    {

        char key = cv::waitKey(27);
        double warpVal = 0.0;

        if (keyboard.find(key) != keyboard.end()){
            if ((char)key == ',' || (char)key == '.'){
                angle += (double)keyboard[key];
                std::cout << "Angle: " << angle << std::endl;
            }
            else if(keyboard[key] < 10 && keyboard[key] > -10){
            zoomFactor += (double)keyboard[key]/100;
            std::cout << "Zoom: " << zoomFactor << std::endl;
            }
            cv::Mat rotate = cv::getRotationMatrix2D(cv::Point(img.rows/2,img.cols/2),angle, zoomFactor);
            cv::warpAffine(img,warpImg,rotate,img.size());
            // std::cout << 
            // warpImg(cv::Rect(cv::Point(img.cols/2,img.rows/2),cv::Point(img.cols/2+5,img.rows/2+5))) 
            // << std::endl;
            comboPt2 = warpImg;
            warpImg.copyTo(comboPt2);

            cv::imshow("warped", warpImg);

            
        }
        else if (key == (char)27) break;
        // std::cout << warpVal << std::endl;

        //warp the image here

        cv::imshow("combo", combo);
    }
    cv::destroyWindow("combo");
    return 0;
}