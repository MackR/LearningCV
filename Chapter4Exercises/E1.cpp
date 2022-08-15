#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#include <chrono>
#include <thread>


int main(int argc, char** argv){
    
    cv::namedWindow("Typebar", cv::WINDOW_AUTOSIZE);
    cv::Mat zMat = cv::Mat::zeros(500,500, CV_8UC3);
    //cv::Mat z2Mat(500,500,CV_8U,0);
    std::string text = "";

    for(;;){


        char key = static_cast<char>(cv::waitKey());

        if (key){
            if( key == 27){
                return 0;
            }
            else if (key == 8 && text.size() != 0){               
                text.pop_back();
            }
            else if (key == 13){
                std::cout << "RETURN HOME!" << std::endl;
            }
            else{
            text.push_back(key);
            }
        }
        cv::putText(zMat,text, {100,100},cv::QT_FONT_NORMAL,0.5,{255,255,255,255});
        cv::imshow("Typebar",zMat);
        zMat.setTo(0);

    }

    
    return 0;
}