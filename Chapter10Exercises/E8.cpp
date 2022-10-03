#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>

// Continuation of exercise 5

int main(int argc, char **argv)
{
    std::string path1 = "../Resources/NoPeanutButter.jpg";
    std::string path2 = "../Resources/PeanutButter.jpg";
    std::string path3 = "../Resources/PeanutButter2.jpg";
    cv::Mat img1, img2, result;

    if (argc > 1)
    {
        cv::Mat img1 = cv::imread(argv[1], -1);
        cv::Mat img2 = cv::imread(argv[2], -1);
    }

    cv::namedWindow("img1", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("img2", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("result", cv::WINDOW_AUTOSIZE);
    if (img1.empty() || img2.empty())
    {
        img1 = cv::imread(path1, cv::IMREAD_COLOR);
        img2 = cv::imread(path2, cv::IMREAD_COLOR);
        if (img1.empty() || img2.empty())
        {
            std::cout << "One image missing";
            return -1;
        }
    }

    // Format the images here
    cv::Mat fImg1 = img1.clone(), fImg2 = img2.clone();
    while (fImg1.rows > 700 || fImg1.cols > 1200)
    {
        cv::pyrDown(fImg1, fImg1);
        cv::pyrDown(fImg2, fImg2);
    }

    cv::cvtColor(fImg1, fImg1, cv::COLOR_BGR2GRAY);
    cv::cvtColor(fImg2, fImg2, cv::COLOR_BGR2GRAY);

    // Do image processing here

    cv::Mat diff1(fImg1.rows, fImg1.cols,CV_8U), diff2(fImg1.rows, fImg1.cols,CV_8U);
    cv::absdiff(fImg1, fImg2, diff1);

    cv::threshold(diff1, diff1, 50, 255, cv::THRESH_BINARY);

    std::cout << "Image size is: " << diff1.size << std::endl;
    std::cout << "Checkpoint reached!, Moving to flood fill" << std::endl;
    cv::imshow("result", diff1);
    cv::waitKey(0);

    // cv::boxFilter(diff1,diff1,-1,cv::Size(5,5));
    cv::dilate(diff1, diff1, cv::Mat());
    cv::morphologyEx(diff1, diff1, cv::MORPH_OPEN, cv::Mat(), cv::Point(-1, -1), 1);

    std::cout << "Dilation and opening complete" << std::endl;
    cv::imshow("result", diff1);
    cv::waitKey(0);
    // cv::erode(diff1, diff2, cv::Mat());
    // cv::bitwise_xor(diff1, diff2, diff1);

    // Perform flood fill of largest shape remaining

    uchar pixel = 0;
    int areaPrime = 0, area = -1;
    std::pair<int, int> location(0,0), locationPrime(0,0);
    for (int row = 0; row < diff1.rows; ++row)
    {
        for (int col = 0; col < diff1.cols; ++col)
        {
            pixel = diff1.at<uchar>(row, col);
            if (pixel == 255)
            {   
                //diff1.at<uchar>(row, col) = 0;
                location.first = col;
                location.second = row;
                area = cv::floodFill(diff1, cv::Point(col, row), 100);

                if (area <= areaPrime)
                {
                    cv::floodFill(diff1, cv::Point(col, row), 0);
                    std::cout << "Not a larger zone, moving on" << std::endl;
                }
                else if (area > areaPrime)
                {   
                    std::cout << "New area found, reassigning, old area, new area: " << area << ", " << areaPrime << std::endl;
                    areaPrime = area;
                    cv::floodFill(diff1, cv::Point(locationPrime.first, locationPrime.second), 0);
                    locationPrime.first = location.first;
                    locationPrime.second = location.second;
                }
                else
                    std::cout << "Error, else condition reached, previously thought impossible" << std::endl;
                std::cout << "Working on it, row, col, val: " << row << ", " << col << ", " << (int)pixel << std::endl;

                cv::imshow("result",diff1);
                cv::waitKey(0);

            }
        }
    }
    cv::floodFill(diff1,cv::Point(locationPrime.first,locationPrime.second),255);

    result = diff1;

    std::cout << "Image processing complete" << std::endl;
    cv::imshow("img1", img1);
    cv::imshow("img2", img2);
    cv::imshow("result", result);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}