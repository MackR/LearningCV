#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>


int main(int argc, char** argv){
    std::string path = "../Resources/BrightInsideHand.jpg";
    std::string path2 = "../Resources/DarkInsideHand.jpg";
    cv::Mat img;
    cv::Mat img2;

    if (argc >1){
        img = cv::imread(argv[1],-1);
        img2 = cv::imread(argv[2],-1);
}

    cv::namedWindow("img", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("img2", cv::WINDOW_AUTOSIZE);
    // cv::namedWindow("proc", cv::WINDOW_AUTOSIZE);
    if( img.empty()) {
        img = cv::imread(path, cv::IMREAD_COLOR);
        img2 = cv::imread(path2, cv::IMREAD_COLOR);
        if( img.empty()) {
            std::cout << "No image provided";
            return -1;
        }
    }

    // Format image here - No need to format, image is already good size
    cv::Mat fImg = img.clone();
    cv::Mat fImg2 = img2.clone();

    cv::resize(fImg,fImg,cv::Size(600,600));
    cv::resize(fImg2,fImg2,cv::Size(600,600));
    // cv::Mat fImgHSV = fImg.clone();
    // cv::cvtColor(fImg,fImgHSV,cv::COLOR_BGR2HSV);


    // Process image here
    cv::Mat proc;
    cv::Mat histControl, histTest;

    float color_range[] = {0, 256}; // Colors range from 0-256
    const float* ranges[] = {color_range, color_range,color_range}; // Ranges are how big the range of values are
    int histSize[] = {4, 4, 4}, ch[] = {0, 1, 2}; // Hist size is the width of the bins in each dimension?




    // cv::calcHist(&hsv, 1, ch, cv::noArray(), hist, 2, histSize, ranges, true);
    cv::calcHist(&fImg,1,ch,cv::noArray(),histControl,2,histSize,ranges, true);
    cv::calcHist(&fImg2,1,ch,cv::noArray(),histTest,2,histSize,ranges, true);

    cv::normalize(histControl,histControl,1,0,cv::NORM_L1);
    cv::normalize(histTest,histTest,1,0,cv::NORM_L1);

    double matchQuality[5] = {0};
    matchQuality[0] = cv::compareHist(histControl,histTest,cv::HISTCMP_CORREL);
    matchQuality[1] = cv::compareHist(histControl,histTest,cv::HISTCMP_CHISQR);
    matchQuality[2] = cv::compareHist(histControl,histTest,cv::HISTCMP_BHATTACHARYYA);
    matchQuality[3] = cv::compareHist(histControl,histTest,cv::HISTCMP_INTERSECT);
    // matchQuality[4] = cv::compareHist(histControl,histTest,cv::HISTCMP_HELLINGER);
    double controlMatchQuality[5] = {0};
    controlMatchQuality[0] = cv::compareHist(histControl,histControl,cv::HISTCMP_CORREL);
    controlMatchQuality[1] = cv::compareHist(histControl,histControl,cv::HISTCMP_CHISQR);
    controlMatchQuality[2] = cv::compareHist(histControl,histControl,cv::HISTCMP_BHATTACHARYYA);
    controlMatchQuality[3] = cv::compareHist(histControl,histControl,cv::HISTCMP_INTERSECT);

    std::cout << "The control image match quality for each method is: " << std::endl; 
    std::cout << "Correlation: " << controlMatchQuality[0] << std::endl;
    std::cout << "CHISQR: " << controlMatchQuality[1] << std::endl;
    std::cout << "BHATTACHARYYA: " << controlMatchQuality[2] << std::endl;
    std::cout << "INTERSECT: " << controlMatchQuality[3] << std::endl <<std::endl;

    std::cout << "The image match quality for each method is: " << std::endl; 
    std::cout << "Correlation: " << matchQuality[0] << std::endl;
    std::cout << "CHISQR: " << matchQuality[1] << std::endl;
    std::cout << "BHATTACHARYYA: " << matchQuality[2] << std::endl;
    std::cout << "INTERSECT: " << matchQuality[3] << std::endl;
    


    cv::imshow("img",fImg);
    cv::imshow("img2",fImg2);
    // cv::imshow("proc",proc);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;

}