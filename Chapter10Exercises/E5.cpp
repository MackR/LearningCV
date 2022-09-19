#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>


int main(int argc, char** argv){
    std::string path = "../Resources/Similar1.png";
    std::string path2 = "../Resources/Similar2.png";
    cv::Mat src1, src2, diff12, cleandiff, dirtydiff;
    cv::Size three(3,3), five(5,5), nine(9,9), eleven(11,11);


    if (argc >1){
        cv::Mat src1 = cv::imread(argv[1],-1);
}

    cv::namedWindow("src1", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("diff12", cv::WINDOW_AUTOSIZE);
    // cv::namedWindow("cleandiff", cv::WINDOW_AUTOSIZE);
    // cv::namedWindow("dirtydiff", cv::WINDOW_AUTOSIZE);
    if( src1.empty()) {
        src1 = cv::imread(path, cv::IMREAD_GRAYSCALE);
        src2 = cv::imread(path2, cv::IMREAD_GRAYSCALE);

        if (src1.empty()) std::cout << "Couldn't read file type1!" << std::endl;
        if (src2.empty()) std::cout << "Couldn't read file type2!" << std::endl;
        
        if( src1.empty()) {
            std::cout << "No image provided";
            return -1;
        }
    }

    // Do image processing here
    // Format the images to same dimensions:
    // const int LENSWIDTH = 100, LENSHEIGHT = 100;
    const int buffer = 0;
    const int rowScope = MIN(src1.rows,src2.rows), colScope = MIN(src1.cols,src2.cols);
    // int x = colScope/2, y = rowScope/2;
    // int possibleXRange = abs(src1.cols-src2.cols), possibleYRange = abs(src1.rows - src2.rows);
    // cv::Mat src1Lens(src1,cv::Rect(x,y, LENSWIDTH, LENSHEIGHT)), 
    cv::Mat src2Lens(src2,cv::Rect(0,0, colScope-buffer, rowScope-buffer));
    // double minScore = 1000000, xPrime = 0, yPrime = 0;


    // for (int xShift = -5; xShift <= 5; xShift++){
    //     for (int yShift = -5; yShift <= 5; yShift++){
    //         src2Lens = src2(cv::Rect(x+xShift, y+yShift, LENSWIDTH, LENSHEIGHT));
    //         cv::absdiff(src1Lens,src2Lens,diff12);
    //         double score = cv::sum(diff12)[0];
    //         if (score < minScore){
    //             minScore = score;
    //             xPrime = xShift;
    //             yPrime = yShift;
    //             std::cout << "New best position found (X,Y): " << xPrime << ", " << yPrime << std::endl;
    //             std::cout << "Score: " << score << std::endl;
    //         }
    //     }
    // }


    
    cv::resize(src1,src1,cv::Size(colScope,rowScope));
    cv::resize(src2Lens,src2Lens,cv::Size(colScope,rowScope));
    // Use me!!! cv::copyMakeBorder();

    // std::cout << "The size of src1 is: " << src1.size << std::endl;
    // std::cout << "The size of src2 is: " << src2.size << std::endl;

    cv::absdiff(src1, src2Lens, diff12);

    // cv::erode(diff12,cleandiff,cv::Mat());
    // cv::dilate(cleandiff,cleandiff,cv::Mat());

    // cv::dilate(diff12,dirtydiff,cv::Mat());
    // cv::erode(dirtydiff,dirtydiff,cv::Mat());

    cv::imshow("src1",src1);
    cv::imshow("diff12",diff12);
    // cv::imshow("cleandiff",cleandiff);
    // cv::imshow("dirtydiff",dirtydiff);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;

}