#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>


int main(int argc, char** argv){

    

    std::string paths[] = {"","","","",""};
    std::string path2 = "../Resources/Arm1.jpg";
    cv::Mat imgs[5];
    cv::Mat img2;

    img2 = cv::imread(path2);
    cv::resize(img2,img2,cv::Size(600,600));
    cv::cvtColor(img2,img2,cv::COLOR_BGR2HSV);

    for (int i = 1; i <=5; ++i){
        paths[i-1] = "../Resources/Hand" + std::to_string(i) + ".jpg";
    }
    cv::Mat img = cv::imread("../Resources/Hand1.jpg", cv::IMREAD_COLOR);
    std::cout<< "HI" << std::endl;
    for (int i = 0; i <5; ++i){
        cv::Mat img = cv::imread(paths[i]);
        if (!img.empty()){
            imgs[i] = img;
            cv::resize(imgs[i],imgs[i],cv::Size(600,600));
            cv::cvtColor(imgs[i],imgs[i],cv::COLOR_BGR2HSV);
        }
        else {std::cout << "Image was empty" << std::endl; return -1;}
    std::string winName = "Hand" + std::to_string(i+1);
    cv::namedWindow(winName, cv::WINDOW_AUTOSIZE);
    cv::imshow(winName,imgs[i]);
    }

    cv::waitKey(0);

    cv::Mat hists[5];
    int dims[] = {0,1}; // We only want the hue saturation values.
    float h_Range[] = {0,180};
    float s_Range[] = {0,255};
    const float* ranges[] = {h_Range, s_Range};
    int histSize[] = {16,16};

    cv::Mat histOut;

        cv::calcHist(hists,(int)(sizeof(hists)/sizeof(hists[0])),
        dims, cv::noArray(),histOut,2,histSize,ranges,true);

    cv::normalize(histOut,histOut,1,0,cv::NORM_L1);


    //cv::threshold(histOut,histOut,cv::THRESH_OTSU,cv::THRESH_OTSU,cv::THRESH_TOZERO);
    cv::Mat backProject;
    cv::calcBackProject(&img2,1,dims,histOut,backProject,ranges);

    cv::equalizeHist(backProject,backProject);
    
    cv::namedWindow("img2",cv::WINDOW_AUTOSIZE);
    cv::imshow("img2",backProject);

    //cv::imshow("img2",img2);

    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;

}