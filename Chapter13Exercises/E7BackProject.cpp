#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>

int main(int argc, char **argv)
{

    std::string paths[] = {"", "", "", "", ""};
    std::string path2 = "../Resources/ThumbRight.jpg";
    cv::Mat imgs[2];
    cv::Mat img2;

    img2 = cv::imread(path2);
    cv::resize(img2, img2, cv::Size(600, 600));
    cv::cvtColor(img2, img2, cv::COLOR_BGR2HSV);

    for (int i = 2; i <= 3; ++i)
    {
        paths[i - 2] = "../Resources/Hand" + std::to_string(i) + ".jpg";
    }

    for (int i = 0; i < 2; ++i)
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

    // cv::Mat roi(imgs[0], cv::Range(0, 100), cv::Range(0, 100));
    // cv::Mat roi2(imgs[0], cv::Range(100, 200), cv::Range(0, 100));
    cv::Mat roi(imgs[0], cv::Range(250, 350), cv::Range(215, 315));
    cv::Mat roi2(imgs[1], cv::Range(250, 300), cv::Range(350, 450));
    cv::imshow("img2", roi);
    cv::waitKey(0);
    cv::imshow("img2", roi2);
    cv::waitKey(0);
    cv::Mat rois[] = {roi, roi2};

    cv::Mat hists[5];
    int dims[] = {0,1}; // We only want the hue saturation values.
    float h_Range[] = {0, 180};
    float s_Range[] = {0, 255};
    float bgr_range[]= {0, 255};
    // float v_Range[] = {0, 100};
    const float *ranges[] = {h_Range, s_Range};
    int histSize[] = {16,16};
    int histSizeBGR[] = {16,16,16};

    cv::Mat histOut;

    cv::calcHist(rois, (int)(sizeof(hists) / sizeof(hists[0])),
                 dims, cv::noArray(), histOut, 2, histSize, ranges, true);

    // cv::normalize(histOut,histOut,1,0,cv::NORM_L1);
    // cv::imshow("img2", histOut);
    // cv::waitKey(0);

    // cv::threshold(histOut,histOut,cv::THRESH_OTSU,cv::THRESH_OTSU,cv::THRESH_TOZERO);
    cv::Mat backProject;

    // cv::Mat frame;

        // cv::resize(img2, img2, cv::Size(600, 600));
        cv::pyrDown(img2,img2);
        cv::calcBackProject(&img2, 2, dims, histOut, backProject, ranges);

        cv::imshow("img2", backProject);
        cv::waitKey(0);

        cv::morphologyEx(backProject, backProject, cv::MORPH_OPEN, cv::Mat());
        //cv::equalizeHist(backProject,backProject);
        cv::imshow("img2", backProject);
        cv::waitKey(0);
        // cv::threshold(backProject,backProject,cv::THRESH_OTSU,255,cv::THRESH_BINARY);
        cv::threshold(backProject,backProject,100,255,cv::THRESH_BINARY);
        cv::imshow("img2", backProject);
        cv::waitKey(0);

        uchar pixel = 0;
    int areaPrime = 0, area = 0;
    std::pair<int, int> location(0,0), locationPrime(0,0);
    for (int row = 0; row < backProject.rows; ++row)
    {
        for (int col = 0; col < backProject.cols; ++col)
        {
            pixel = backProject.at<uchar>(row, col);
            if (pixel >= 200)
            {   
                //diff1.at<uchar>(row, col) = 0;
                area = cv::floodFill(backProject, cv::Point(col, row), 100);

                if (area < areaPrime)
                {
                    cv::floodFill(backProject, cv::Point(col, row), 0);
                    std::cout << "Not a larger zone, moving on" << std::endl;
                }
                else if (area > areaPrime)
                {   
                    std::cout << "New area found, reassigning. Old area, new area: " << areaPrime << ", " << area << std::endl;
                    areaPrime = area;
                    cv::floodFill(backProject, cv::Point(locationPrime.first, locationPrime.second), 0);
                    locationPrime.first = col;
                    locationPrime.second = row;
                }
                else if (area == areaPrime){
                    std::cout << "Areas are equal, do nothing" << std::endl;
                }
                else
                    std::cout << "Error, else condition reached, previously thought impossible" << std::endl;
                std::cout << "Working on it, row, col, val: " << row << ", " << col << ", " << (int)pixel << std::endl;

                cv::imshow("img2",backProject);
                cv::waitKey(0);

            }
        }
    }
        cv::floodFill(backProject, cv::Point(locationPrime.first, locationPrime.second), 255);
        cv::morphologyEx(backProject, backProject, cv::MORPH_DILATE, cv::Mat(),cv::Point(-1,-1), 2);



        std::cout << "Image processing complete" << std::endl;

        // cv::equalizeHist(backProject,backProject);

        cv::namedWindow("img2", cv::WINDOW_AUTOSIZE);
        cv::namedWindow("orig", cv::WINDOW_AUTOSIZE);

        cv::imshow("orig", img2);
        cv::imshow("img2", backProject);
        cv::waitKey(0);

        // cv::imshow("img2",img2);

    cv::destroyAllWindows();
    return 0;
}