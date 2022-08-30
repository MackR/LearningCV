#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>

cv::Point pStart(0, 0);
cv::Mat orig;

void onMouse(int event, int x, int y, int flags, void *img)
{

    cv::Mat* image = ((cv::Mat *)img);
    cv::Point p(x, y);
    cv::Scalar clickedColor, black = {0, 0, 0, 0}, white = {255, 255, 255, 255};
    clickedColor = image->at<cv::Vec3b>(y, x);

    if (event == cv::EVENT_LBUTTONDOWN)
    {
        pStart = p;
        try
        {
            // Code that could throw an exception
            cv::destroyWindow("Histogram");
        }
        catch (...)
        {
            // Code that executes when an exception of type
        }
    }
    else if (event == cv::EVENT_MOUSEMOVE && flags & cv::EVENT_FLAG_LBUTTON)
    {

        cv::Point pFinish(x, y);
        cv::Rect selection(pStart, pFinish);
        // std::cout << selection << '\n';
        *image = orig.clone();                      // cleans up the image from having prior rectangle on it
        // std::cout << "Reset image!" << "\n";
        cv::rectangle(*image, selection, white, 1); // draws the rectangle on the image
        // std::cout << "Drew Rectangle" << "\n";
        //cv::imshow("img",*image);


    }

    else if (event == cv::EVENT_LBUTTONUP)
    { // create histogram
        // Wipe the images clean
        cv::Mat copy = orig.clone();
        //image = orig.clone();
        std::cout << "Reset image!" << "\n";

        // Get and set the corners of selection rectangle
        cv::Point pFinish(x, y);
        cv::Point topLeft(pStart),
            bottomLeft(pStart.x, pFinish.y),
            topRight(pFinish.x, pStart.y),
            bottomRight(pFinish);
        cv::Rect selectionBox(pStart,pFinish);
        cv::Point corners[] = {topLeft, topRight, bottomRight, bottomLeft};
        std::cout << corners[1] << '\n';

        // Fill the rectangle and alpha blend the images for transparent selection
        cv::fillConvexPoly(*image, corners, 4, white);
        std::cout << "Filled rectangle" << "\n";

        cv::addWeighted(*image, 0.25, copy, 0.75, 0.0, *image);
        std::cout << "Alpha blended" << "\n";

        // Create the Histogram
        cv::Mat histogramImg(300, 300, CV_8UC3, clickedColor);

        int histSize = 256;
        float range[] = {0,256.0};
        float histRange[] = {0,256.0};
        cv::Mat b_hist, g_hist, r_hist;
        std::vector<cv::Mat> bgr_planes;

        std::cout << "Pre-roi()" << std::endl;
        cv::Mat rectMask = cv::Mat::zeros(image->rows, image->cols, CV_8U);
        rectMask(selectionBox) = 1;
        // std::cout << "rectMask: " << rectMask << std::endl;


        std::cout << "Pre-split()" << std::endl;
        cv::split(orig, bgr_planes);

        std::cout << "Pre-calcHist()" << std::endl;


        cv::calcHist( &bgr_planes[0],1, 0, rectMask, b_hist, 1, &histSize, 0);
        cv::calcHist( &bgr_planes[1],1, 0, rectMask, g_hist, 1, &histSize, 0);
        cv::calcHist( &bgr_planes[2],1, 0, rectMask, r_hist, 1, &histSize, 0);

        std::cout << "Calculated Histograms!" << std::endl;

        int hist_w = 512, hist_h = 400;
        int bin_w = cvRound((double)hist_w/histSize);
        cv::Mat histImg(hist_h, hist_w, CV_8UC3,cv::Scalar(0,0,0,0));
        cv::normalize(b_hist,b_hist,0,hist_h,cv::NORM_MINMAX,-1,cv::Mat());
        cv::normalize(g_hist,g_hist,0,hist_h,cv::NORM_MINMAX,-1,cv::Mat());
        cv::normalize(r_hist,r_hist,0,hist_h,cv::NORM_MINMAX,-1,cv::Mat());

        std::cout << "Normalized Histograms!" << std::endl;
        

        for (int i = 1; i < histSize; i++){
            line(histImg, cv::Point(bin_w * (i-1), hist_h - cvRound(b_hist.at<float>(i-1))), 
            cv::Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))), cv::Scalar(255,0,0),2,8,0);
            line(histImg, cv::Point(bin_w * (i-1), hist_h - cvRound(g_hist.at<float>(i-1))), 
            cv::Point(bin_w * (i), hist_h - cvRound(g_hist.at<float>(i))), cv::Scalar(0,255,0),2,8,0);
            line(histImg, cv::Point(bin_w * (i-1), hist_h - cvRound(r_hist.at<float>(i-1))), 
            cv::Point(bin_w * (i), hist_h - cvRound(r_hist.at<float>(i))), cv::Scalar(0,0,255),2,8,0);
            
        }
        std::cout << "Drew Histograms!" << std::endl;

        cv::namedWindow("Histogram", 1);
        cv::imshow("Histogram", histImg);
        cv::moveWindow("Histogram", 400, 400);


    }
}

int main(int argc, char **argv)
{
    std::string path = "../Resources/Greenery.jpg";

    cv::Mat img;

    if (argc > 1)
    {
        orig = cv::imread(argv[1], -1);
        img = orig.clone();
    }

    cv::namedWindow("img", cv::WINDOW_AUTOSIZE);
    if (img.empty())
    {
        orig = cv::imread(path, cv::IMREAD_COLOR);
        img = orig.clone();
        if (img.empty())
        {
            std::cout << "No image provided";
            return -1;
        }
    }

    cv::setMouseCallback("img", onMouse, &img);

    // Do image processing here
    int counter = 0;
    while (1)
    {

        cv::imshow("img", img);
        if (cv::waitKey(20) == 27)
            break;
        // if(counter > 100){
        //     img = orig.clone();
        //     counter = 0;
        // }
        // ++counter;
    }
    cv::destroyWindow("img");
    return 0;
}