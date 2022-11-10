#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#include <map>
#include <boost/circular_buffer.hpp>
#include "../CustomTools.cpp"

void extractOutline(cv::InputArray src, cv::OutputArray dst);

int main(int argc, char **argv)
{
    std::string paths[9];
    cv::Mat imgs[9];
    std::string baseImageName = "Gesture";
    std::string imgExtension = ".jpg";


    for (auto &img : imgs)
    {
        int index = (&img - imgs);
        std::cout << "The index of image is: " << index << std::endl;
        std::string path = "../Resources/" + baseImageName + std::to_string(index + 1) + imgExtension;
        std::cout << "Path is: " << path << std::endl;
        img = cv::imread(path, cv::IMREAD_COLOR);
        if (img.empty())
        {
            std::cout << "Error! Image " << index + 1 << " is empty" << std::endl;
            return 0;
        }
        // DISPLAYIMAGE(img);

    }
    cv::Moments gestureMoms[9];
    cv::Mat imgResults[9];

    for (int i = 0; i < 9; ++i){


        // DISPLAYIMAGE(imgs[i]);
        cv::Mat blur, canny, dilated;
        cv::bilateralFilter(imgs[i], blur, -1, 15, 5); // Reccommends 5 for real time applications
        // DISPLAYIMAGE(blur);
        cv::Canny(blur, canny, 150, 10);
        // DISPLAYIMAGE(canny);
        cv::dilate(canny, dilated, cv::Mat());
        // DISPLAYIMAGE(dilated);

        cv::floodFill(dilated, cv::Point(0, 0), cv::Scalar(128)); // Pick the corner seed to get background

        cv::Mat scan = dilated.clone();
        typedef uchar PIXEL_T;
        PIXEL_T pixel = 0;
        for (int row = 0; row < scan.rows; ++row)
        {
            for (int col = 0; col < scan.cols; ++col)
            {
                pixel = scan.at<PIXEL_T>(row, col);
                // Perform pixel operation here
                if (pixel == 0)
                {
                    // std::cout << "The pixel location is: " << col << ", " << row << std::endl;
                    // DISPLAYIMAGE(scan);
                    cv::floodFill(scan, cv::Point(col, row), cv::Scalar(255));
                }
            }
        }
        canny = scan.clone();
        cv::floodFill(canny, cv::Point(0, 0), cv::Scalar(0));

        //DISPLAYIMAGE(canny);

        imgResults[i] = canny;  

    }

        cv::VideoCapture cap;
        cap.open(0);

        cv::Mat frame, processedFrame;
        cv::namedWindow("Original",cv::WINDOW_AUTOSIZE);
        cv::namedWindow("Processed",cv::WINDOW_AUTOSIZE);
        
        std::string gNames[] = {"Thumbs up", "Shake", "The finger", "Gun", "TU", "Shaka", "Perfect", "Italian", "Fistbump"};
        boost::circular_buffer<int> cb(30);
        while(framePose++){
            
            cap >> frame;
            cv::pyrDown(frame,frame);
            if (frame.empty()){
                std::cout << "Frame was empty. Returning." << std::endl; return 0;
            }

            extractOutline(frame,processedFrame);
            double matchPrime = 1000, match = 0;
            int primeIndex;
            for (int i = 0; i < 9; ++i){
                match = cv::matchShapes(processedFrame,imgResults[i],cv::CONTOURS_MATCH_I1,0);
                if(match < matchPrime){matchPrime = match; primeIndex = i; }

            }

            cb.pushback(primeIndex);


            cv::putText(frame,gNames[primeIndex],cv::Point(frame.cols/2,frame.rows-200),cv::FONT_HERSHEY_COMPLEX,.75,cv::Scalar(255,0,0));

            cv::imshow("Original", frame);
            cv::imshow("Processed", processedFrame);
            if(cv::waitKey(20) == 27){break;}



        }

        

        // double closeness = cv::matchShapes(fImgBWScale,fImgBWScale,cv::CONTOURS_MATCH_I1,1);
        // double closenessAlt = cv::matchShapes(fImgBWRot,img2,cv::CONTOURS_MATCH_I1,1);

        // std::cout << "Closeness match is: " << closeness << std::endl;
        // std::cout << "Closeness non-match is: " << closenessAlt << std::endl;

        return 0;
    }

    void extractOutline(cv::InputArray src, cv::OutputArray dst){
        cv::Mat blur, canny, dilated;
        cv::bilateralFilter(src, blur, -1, 15, 5); // Reccommends 5 for real time applications
        cv::Canny(blur, canny, 150, 10);
        cv::dilate(canny, canny, cv::Mat());

        cv::floodFill(canny, cv::Point(0, 0), cv::Scalar(128)); // Pick the corner seed to get background
        typedef uchar PIXEL_T;
        PIXEL_T pixel = 0;
        for (int row = 0; row < canny.rows; ++row)
        {
            for (int col = 0; col < canny.cols; ++col)
            {
                pixel = canny.at<PIXEL_T>(row, col);
                // Perform pixel operation here
                if (pixel == 0)
                {
                    // std::cout << "The pixel location is: " << col << ", " << row << std::endl;
                    // DISPLAYIMAGE(scan);
                    cv::floodFill(canny, cv::Point(col, row), cv::Scalar(255));
                }
            }
        }
        cv::compare(canny,128,dst,cv::CMP_GT);

        //DISPLAYIMAGE(dst);

    }