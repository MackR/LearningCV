#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>


int main(int argc, char** argv){
    std::string path = "../Resources/MediumInsideHand.jpg";
    std::string path2 = "../Resources/BrightInsideHand.jpg";
    std::string path3 = "../Resources/BicycleLowContrast.jpg";
    std::string path4 = "../Resources/BlueChairOutside.jpg";
    cv::Mat img;
    cv::Mat img2;
    cv::Mat img3;
    cv::Mat img4;

    if (argc >1){
        img = cv::imread(argv[1],-1);
        img2 = cv::imread(argv[2],-1);
}

    cv::namedWindow("img", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("img2", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("img3", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("img4", cv::WINDOW_AUTOSIZE);
    // cv::namedWindow("proc", cv::WINDOW_AUTOSIZE);
    if( img.empty()) {
        img = cv::imread(path, cv::IMREAD_COLOR);
        img2 = cv::imread(path2, cv::IMREAD_COLOR);
        img3 = cv::imread(path3, cv::IMREAD_COLOR);
        img4 = cv::imread(path4, cv::IMREAD_COLOR);
        if( img.empty()) {
            std::cout << "No image provided";
            return -1;
        }
    }

    // Format image here - No need to format, image is already good size
    cv::Mat fImg = img.clone();
    cv::Mat fImg2 = img2.clone();
    cv::Mat fImg3 = img3.clone();
    cv::Mat fImg4 = img4.clone();

    cv::resize(fImg,fImg,cv::Size(600,600));
    cv::resize(fImg2,fImg2,cv::Size(600,600));
    cv::resize(fImg3,fImg3,cv::Size(600,600));
    cv::resize(fImg4,fImg4,cv::Size(600,600));
    // cv::Mat fImgHSV = fImg.clone();
    // cv::cvtColor(fImg,fImgHSV,cv::COLOR_BGR2HSV);


    // Process image here
    cv::Mat proc;
    cv::Mat histControl, histTest, histTest2, histTest3;

    float color_range[] = {0, 256}; // Colors range from 0-256
    const float* ranges[] = {color_range, color_range,color_range}; // Ranges are how big the range of values are
    int histSize[] = {16, 16, 16}, ch[] = {0, 1, 2}; // Hist size is the number of bins in each dimension




    // cv::calcHist(&hsv, 1, ch, cv::noArray(), hist, 2, histSize, ranges, true);
    cv::calcHist(&fImg,1,ch,cv::noArray(),histControl,2,histSize,ranges, true);
    cv::calcHist(&fImg2,1,ch,cv::noArray(),histTest,2,histSize,ranges, true);
    cv::calcHist(&fImg3,1,ch,cv::noArray(),histTest2,2,histSize,ranges, true);
    cv::calcHist(&fImg4,1,ch,cv::noArray(),histTest3,2,histSize,ranges, true);

    cv::normalize(histControl,histControl,1,0,cv::NORM_L1);
    cv::normalize(histTest,histTest,1,0,cv::NORM_L1);
    cv::normalize(histTest2,histTest2,1,0,cv::NORM_L1);
    cv::normalize(histTest3,histTest3,1,0,cv::NORM_L1);

    // Create the signatures setup for the EMD calculation

    std::vector<cv::Vec3f> sigControl;
    std::vector<cv::Vec3f> sigTest;
    std::vector<cv::Vec3f> sigTest2;
    std::vector<cv::Vec3f> sigTest3;
    
    for (int row = 0; row < histSize[0]; ++row){
        for (int col = 0; col < histSize[0]; ++col){
            float binCount = histControl.at<float>(col,row);
            if(binCount != 0){
            }
                sigControl.push_back(cv::Vec3f(binCount,(float)col,(float)row)); // Making the cast to float explicit.
        }
    }

    for (int row = 0; row < histSize[0]; ++row){
        for (int col = 0; col < histSize[0]; ++col){
            float binCount = histTest.at<float>(col,row);
            if(binCount != 0){
            }
                sigTest.push_back(cv::Vec3f(binCount,(float)col,(float)row)); // Making the cast to float explicit.
        }
    }

    for (int row = 0; row < histSize[0]; ++row){
        for (int col = 0; col < histSize[0]; ++col){
            float binCount = histTest2.at<float>(col,row);
            if(binCount != 0){
            }
                sigTest2.push_back(cv::Vec3f(binCount,(float)col,(float)row)); // Making the cast to float explicit.
        }
    }

    for (int row = 0; row < histSize[0]; ++row){
        for (int col = 0; col < histSize[0]; ++col){
            float binCount = histTest3.at<float>(col,row);
            if(binCount != 0){
            }
                sigTest3.push_back(cv::Vec3f(binCount,(float)col,(float)row)); // Making the cast to float explicit.
        }
    }

        // make Nx3 32fC1 matrix, where N is the number of nonzero histogram bins
    //
    cv::Mat sigControlShape = cv::Mat(sigControl).clone().reshape(1);
    cv::Mat sigTestShape = cv::Mat(sigTest).clone().reshape(1);
    cv::Mat sigTestShape2 = cv::Mat(sigTest2).clone().reshape(1);
    cv::Mat sigTestShape3 = cv::Mat(sigTest3).clone().reshape(1);
    float EMDQuality = EMD(sigControlShape, sigTestShape, cv::DIST_L2);
    float EMDQuality2 = EMD(sigControlShape, sigTestShape2, cv::DIST_L2);
    float EMDQuality3 = EMD(sigControlShape, sigTestShape3, cv::DIST_L2);
    float EMDQualityControl = EMD(sigControlShape, sigControlShape, cv::DIST_L2);



    std::cout << "The EMD match control quality is:" << EMDQualityControl << std::endl;
    std::cout << "The EMD match quality is:" << EMDQuality << std::endl;
    std::cout << "The EMD match quality is:" << EMDQuality2 << std::endl;
    std::cout << "The EMD match quality is:" << EMDQuality3 << std::endl;


    // std::cout << "The control image match quality for each method is: " << std::endl; 
    // std::cout << "Correlation: " << controlMatchQuality[0] << std::endl;
    // std::cout << "CHISQR: " << controlMatchQuality[1] << std::endl;
    // std::cout << "BHATTACHARYYA: " << controlMatchQuality[2] << std::endl;
    // std::cout << "INTERSECT: " << controlMatchQuality[3] << std::endl <<std::endl;

    // std::cout << "The image match quality for each method is: " << std::endl; 
    // std::cout << "Correlation: " << matchQuality[0] << std::endl;
    // std::cout << "CHISQR: " << matchQuality[1] << std::endl;
    // std::cout << "BHATTACHARYYA: " << matchQuality[2] << std::endl;
    // std::cout << "INTERSECT: " << matchQuality[3] << std::endl;
    


    cv::imshow("img",fImg);
    cv::imshow("img2",fImg2);
    cv::imshow("img3",fImg3);
    cv::imshow("img4",fImg4);
    // cv::imshow("proc",proc);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;

}