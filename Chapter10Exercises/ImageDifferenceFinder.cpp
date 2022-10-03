#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>

int main(int argc, char **argv)
{
    std::string path = "../Resources/Similar1.png";
    std::string path2 = "../Resources/Similar2.png";
    cv::Mat src1, src2, diff12, cleandiff, dirtydiff;
    cv::Size three(3, 3), five(5, 5), nine(9, 9), eleven(11, 11);

    if (argc > 1)
    {
        cv::Mat src1 = cv::imread(argv[1], -1);
    }

    cv::namedWindow("src1", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("diff12", cv::WINDOW_AUTOSIZE);
    // cv::namedWindow("cleandiff", cv::WINDOW_AUTOSIZE);
    // cv::namedWindow("dirtydiff", cv::WINDOW_AUTOSIZE);
    if (src1.empty())
    {
        src1 = cv::imread(path, cv::IMREAD_GRAYSCALE);
        src2 = cv::imread(path2, cv::IMREAD_GRAYSCALE);

        // cv::pyrDown(src1,src1);
        // cv::pyrDown(src2,src2);
    }
    if (src1.empty())
        std::cout << "Couldn't read file type1!" << std::endl;
    if (src2.empty())
        std::cout << "Couldn't read file type2!" << std::endl;

    if (src1.empty())
    {
        std::cout << "No image provided";
        return -1;
    }
    else
        std::cout << "src1 and src2 are not empty" << std::endl;

    // Format the data/images to same dimensions assuming similar shape +- a few rows/columns
    const int rowScope = MIN(src1.rows, src2.rows), colScope = MIN(src1.cols, src2.cols);
    cv::Mat formattedSrc1(src1, cv::Rect(0, 0, colScope, rowScope)), formattedSrc2(src2, cv::Rect(0, 0, colScope, rowScope));

    // Create a larger output image to store the end result
    const int padding = 20;
    cv::Mat padded2(formattedSrc2.rows + padding, formattedSrc2.cols + padding, formattedSrc2.type(), cv::Scalar(0));
    // Specify the size of the copy and its offset
    cv::Rect offset_rect = cv::Rect(padding / 2, padding / 2, formattedSrc2.cols, formattedSrc2.rows);
    // Copy to the output Mat
    formattedSrc2.copyTo(padded2(offset_rect));


    // IMAGE PROCESSING BEGINS

    std::cout << "formattedSrc1.size = formattedSrc2.size: " << formattedSrc1.size << std::endl;
    std::cout << "Padded2 size: " << padded2.size << std::endl;

    int yshift = padding / 2, xshift = padding / 2;
    double minScore = 1000000;
    int xPrime = 0, yPrime = 0;

    cv::Mat smallpadded2, smallDiff;
    cv::Mat smallLens2(src2, cv::Rect(formattedSrc2.cols / 2, formattedSrc2.rows / 2, 100, 100)),
            smallLens1(src1, cv::Rect(formattedSrc1.cols / 2, formattedSrc1.rows / 2, 100, 100));


    for (int xShift = -10; xShift <= 10; xShift++)
    {
        for (int yShift = -10; yShift <= 10; yShift++)
        {
            smallLens2 = formattedSrc2(cv::Rect(formattedSrc2.cols / 2 + xShift, formattedSrc2.rows / 2 + yShift, 100, 100));
            cv::absdiff(smallLens1, smallLens2, smallDiff);
            double score = cv::sum(smallDiff)[0];
            if (score < minScore)
            {
                minScore = score;
                xPrime = xShift;
                yPrime = yShift;
                std::cout << "New best position found (X,Y): " << xPrime << ", " << yPrime << std::endl;
                std::cout << "Score: " << score << std::endl;
                cv::imshow("smallDiff", smallDiff);
                cv::Mat src2Lens(padded2, cv::Rect(xPrime + 10, yPrime + 10, formattedSrc2.cols, formattedSrc2.rows));
                cv::absdiff(formattedSrc1, src2Lens, diff12);
                cv::threshold(diff12, diff12, 70, 255, cv::THRESH_BINARY);
                cv::morphologyEx(diff12,diff12,cv::MORPH_OPEN,cv::Mat());
                cv::imshow("diff12", diff12);
                cv::moveWindow("smallDiff",600,150);
                cv::moveWindow("diff12",600,300);

                cv::waitKey(200);
            }
        }
    }

    int key = 0;
    while (key != 27)
    {
        
        std::cout << "Key is: " << key << std::endl;
        if (key == (int)'w' && yPrime != padding / 2)
        {
            yPrime++;
        }
        else if (key == (int)'s' && yPrime != -10)
        {
            --yPrime;
        }
        else if (key == (int)'a' && xPrime != -10)
        {
            --xPrime;
        }
        else if (key == (int)'d' && xPrime != padding / 2)
        {
            ++xPrime;
        }
        std::cout << "xPrime and yPrime are: " << xPrime << ", " << yPrime << std::endl;


        cv::Mat src2Lens(padded2, cv::Rect(xPrime + 10, yPrime + 10, formattedSrc2.cols, formattedSrc2.rows));
        cv::absdiff(formattedSrc1, src2Lens, diff12);
        cv::threshold(diff12, diff12, 70, 70, cv::THRESH_TOZERO);
                cv::morphologyEx(diff12,diff12,cv::MORPH_OPEN,cv::Mat());




        smallLens2 = src2(cv::Rect(formattedSrc2.cols / 2 + xPrime, formattedSrc2.rows / 2 + yPrime, 100, 100));
        cv::absdiff(smallLens1, smallLens2, smallDiff);
        cv::imshow("smallDiff", smallDiff);
        // cv::dilate(diff12,diff12,cv::Mat());
        // cv::erode(diff12,diff12,cv::Mat());

        // cv::erode(diff12,cleandiff,cv::Mat());
        // cv::dilate(cleandiff,cleandiff,cv::Mat());

        // cv::dilate(diff12,dirtydiff,cv::Mat());
        // cv::erode(dirtydiff,dirtydiff,cv::Mat());

        cv::imshow("src1", formattedSrc1);
        cv::moveWindow("src1", 0,0);
        cv::imshow("src2", formattedSrc2);
        cv::moveWindow("src2", formattedSrc1.cols, 0);
        cv::imshow("diff12", diff12);
        cv::moveWindow("diff12", formattedSrc1.cols*3/2, 0);
        // cv::imshow("cleandiff",cleandiff);
        // cv::imshow("dirtydiff",dirtydiff);

        key = cv::waitKey(0);

        cv::Mat cp1 = diff12.clone();
        cv::erode(diff12,diff12,cv::Mat());
        cv::bitwise_xor(diff12,cp1,diff12);

        cv::imshow("diff12", diff12);

        cv::waitKey(0);


    }
    // cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}