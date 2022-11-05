#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>

int main(int argc, char **argv)
{

    std::string paths[] = {"", "", "", "", ""};
    std::string path2 = "../Resources/Arm2.jpg";
    cv::Mat imgs[2];
    cv::Mat img2;

    img2 = cv::imread(path2);
    cv::resize(img2, img2, cv::Size(600, 600));
    cv::cvtColor(img2, img2, cv::COLOR_BGR2HSV);

    for (int i = 1; i <= 1; ++i)
    {
        paths[i - 1] = "../Resources/Hand" + std::to_string(i) + ".jpg";
    }

    for (int i = 0; i < 1; ++i)
    {
        cv::Mat img = cv::imread(paths[i]);
        if (!img.empty())
        {
            imgs[i] = img;
            cv::resize(imgs[i], imgs[i], cv::Size(600, 600));
            cv::cvtColor(imgs[i], imgs[i], cv::COLOR_BGR2HSV);
        }
        else
        {
            std::cout << "Image was empty" << std::endl;
            return -1;
        }
        std::string winName = "Hand" + std::to_string(i + 1);
        cv::namedWindow(winName, cv::WINDOW_AUTOSIZE);
        cv::imshow(winName, imgs[i]);
    }

    cv::waitKey(0);
    cv::destroyAllWindows();

    cv::Mat roi(imgs[0], cv::Range(0, 100), cv::Range(0, 100));
    cv::Mat roi2(imgs[0], cv::Range(100, 200), cv::Range(0, 100));
    // cv::Mat roi(imgs[0], cv::Range(150, 200), cv::Range(215, 315));
    // cv::Mat roi2(imgs[0], cv::Range(250, 300), cv::Range(350, 450));
    cv::imshow("img2", roi);
    cv::waitKey(0);
    cv::imshow("img2", roi2);
    cv::waitKey(0);
    cv::Mat rois[] = {roi, roi2};

    cv::Mat hists[5];
    int dims[] = {0}; // We only want the hue saturation values.
    float h_Range[] = {0, 180};
    float s_Range[] = {0, 255};
    float v_Range[] = {0, 100};
    const float *ranges[] = {h_Range};
    int histSize[] = {16};

    cv::Mat histOut;

    cv::calcHist(rois, (int)(sizeof(hists) / sizeof(hists[0])),
                 dims, cv::noArray(), histOut, 1, histSize, ranges, true);

    // cv::normalize(histOut,histOut,1,0,cv::NORM_L1);
    // cv::imshow("img2", histOut);
    // cv::waitKey(0);

    // cv::threshold(histOut,histOut,cv::THRESH_OTSU,cv::THRESH_OTSU,cv::THRESH_TOZERO);
    cv::Mat backProject;
    cv::VideoCapture cap;
    cap.open(0);
    cv::namedWindow("img2", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("orig", cv::WINDOW_AUTOSIZE);
    // cv::Mat frame;
    while (1)
    {
        cap >> img2;
        if (img2.empty()) {break;}

        // cv::resize(img2, img2, cv::Size(600, 600));
        cv::pyrDown(img2,img2);
        cv::calcBackProject(&img2, 1, dims, histOut, backProject, ranges);
        //cv::morphologyEx(backProject, backProject, cv::MORPH_OPEN, cv::Mat());

        // uchar pixel = 0;
        // int areaPrime = 0, area = -1;
        // std::pair<int, int> location(0, 0), locationPrime(0, 0);
        // for (int row = 0; row < backProject.rows; ++row)
        // {
        //     for (int col = 0; col < backProject.cols; ++col)
        //     {
        //         pixel = backProject.at<uchar>(row, col);
        //         if (pixel == 255)
        //         {

        //             // backProject.at<uchar>(row, col) = 0;
        //             location.first = col;
        //             location.second = row;
        //             area = cv::floodFill(backProject, cv::Point(col, row), 100);

        //             if (area <= areaPrime)
        //             {
        //                 cv::floodFill(backProject, cv::Point(col, row), 0);
        //                 // std::cout << "Not a larger zone, moving on" << std::endl;
        //             }
        //             else if (area > areaPrime)
        //             {
        //                 // std::cout << "New area found, reassigning, old area, new area: " << area << ", " << areaPrime << std::endl;
        //                 areaPrime = area;
        //                 cv::floodFill(backProject, cv::Point(locationPrime.first, locationPrime.second), 0);
        //                 locationPrime.first = location.first;
        //                 locationPrime.second = location.second;
        //             }

        //             //     std::cout << "Error, else condition reached, previously thought impossible" << std::endl;
        //             // std::cout << "Working on it, row, col, val: " << row << ", " << col << ", " << (int)pixel << std::endl;

        //             // cv::imshow("img2",backProject);
        //             // cv::waitKey(0);
        //         }
        //         else
        //         {
        //             cv::floodFill(backProject, cv::Point(col, row), 0);
        //         }
        //     }
        // }
        // cv::floodFill(backProject, cv::Point(locationPrime.first, locationPrime.second), 255);
        //cv::morphologyEx(backProject, backProject, cv::MORPH_OPEN, cv::Mat());

        //std::cout << "Image processing complete" << std::endl;

        // cv::equalizeHist(backProject,backProject);

        cv::imshow("orig", img2);
        cv::imshow("img2", backProject);

        // cv::imshow("img2",img2);

        if (cv::waitKey(25) == 27) break;

    }
    cv::destroyAllWindows();
    return 0;
}