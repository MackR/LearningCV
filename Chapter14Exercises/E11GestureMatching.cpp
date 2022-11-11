#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#include <map>
//#include <boost/circular_buffer.hpp>
#include "../CustomTools.cpp"

void extractOutline(cv::InputArray src, cv::OutputArray dst);
static std::vector<cv::Point> sampleContour(const cv::Mat &image, int n = 300);

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
        cv::pyrDown(img, img);
        cv::Mat dst;
        // extractOutline(img,dst);
        DISPLAYIMAGE(img);
        // DISPLAYIMAGE(dst);
    }
    cv::Moments gestureMoms[9];
    cv::Mat imgResults[9];

    typedef std::vector<std::vector<cv::Point>> CONTOUR_SET_T;
    std::vector<std::vector<cv::Point>> singleContour;
    std::vector<CONTOUR_SET_T> imgContours(9);

    for (int i = 0; i < 9; ++i)
    {
        cv::Mat outline;
        extractOutline(imgs[i],outline);
        // cv::findContours(canny, imgContours[i], cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
        std::vector<cv::Point> c1 = sampleContour(outline);
        imgContours[i].push_back(c1);
        // imgResults[i] = canny;
    }

    cv::VideoCapture cap;
    cap.open(0);

    cv::Mat frame, processedFrame;
    CONTOUR_SET_T frameContour;
    cv::Ptr<cv::ShapeContextDistanceExtractor> mysc = cv::createShapeContextDistanceExtractor();
    cv::namedWindow("Original", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("Processed", cv::WINDOW_AUTOSIZE);

    std::string gNames[] = {"Thumbs up", "Shake", "The finger", "Gun", "TU", "Shaka", "Perfect", "Italian", "Fistbump"};
    float distMeasures[9];
    // boost::circular_buffer<int> cb(30);
    while (1)
    {

        cap >> frame;
        cv::pyrDown(frame, frame);
        if (frame.empty())
        {
            std::cout << "Frame was empty. Returning." << std::endl;
            return 0;
        }

        extractOutline(frame, processedFrame);
        std::vector<cv::Point> c2 = sampleContour(processedFrame);
        // cv::findContours(processedFrame, frameContour, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);

        float distPrime = 1000, dist = 0;
        int primeIndex = 0;
        for (int i = 0; i < 9; ++i)
        {
            if (c2.size() != 0)
            {
                dist = mysc->computeDistance(c2,imgContours[i][0]);
                std::cout << gNames[i] << ": " << distMeasures[i] << ", ";

                distMeasures[i] = dist;
                if (dist < distPrime)
                {
                    distPrime = dist;
                    primeIndex = i;
                }
            }
        }
        std::cout << std::endl;

        // cb.pushback(primeIndex);

        cv::putText(frame, gNames[primeIndex], cv::Point(frame.cols / 2, frame.rows - 100), cv::FONT_HERSHEY_COMPLEX, .75, cv::Scalar(255, 0, 0));
        // cv::drawContours(processedFrame,frameContour,-1,cv::Scalar(100));
        cv::Mat inverseMask;
        cv::bitwise_not(processedFrame, inverseMask);


        std::cout << std::endl;

        cv::imshow("Original", frame);
        cv::Mat appliedMask = frame.setTo(cv::Scalar(0, 0, 0), inverseMask);
        cv::imshow("Processed", appliedMask);
        if (cv::waitKey(20) == 27)
        {
            break;
        }
    }

    // double closeness = cv::matchShapes(fImgBWScale,fImgBWScale,cv::CONTOURS_MATCH_I1,1);
    // double closenessAlt = cv::matchShapes(fImgBWRot,img2,cv::CONTOURS_MATCH_I1,1);

    // std::cout << "Closeness match is: " << closeness << std::endl;
    // std::cout << "Closeness non-match is: " << closenessAlt << std::endl;

    return 0;
}

void extractOutline(cv::InputArray src, cv::OutputArray dst)
{
    cv::Mat blur, canny, dilated;
    cv::bilateralFilter(src, blur, -1, 20, 5); // Reccommends 5 for real time applications
    cv::Canny(blur, canny, 150, 10);
    cv::dilate(canny, canny, cv::Mat());
    cv::dilate(canny, canny, cv::Mat());

    cv::floodFill(canny, cv::Point(0, 0), cv::Scalar(128)); // Pick the corner seed to get background
    cv::compare(canny, cv::Scalar(128), dst, cv::CMP_NE);

    // DISPLAYIMAGE(dst);
}

static std::vector<cv::Point> sampleContour(const cv::Mat &image, int n)
{
    std::vector<std::vector<cv::Point>> _contours;
    std::vector<cv::Point> all_points;
    findContours(image, _contours, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
    if(_contours.size() == 0) {std::cout << "Screen Empty" << std::endl; return std::vector<cv::Point>();}
    for (size_t i = 0; i < _contours.size(); i++)
    {
        for (size_t j = 0; j < _contours[i].size(); j++)
            all_points.push_back(_contours[i][j]);
    }
    //
        int dummy = 0;
        for (int add = (int)all_points.size(); add < n; add++)
            all_points.push_back(all_points[dummy++]);

        // Sample uniformly
        random_shuffle(all_points.begin(), all_points.end());
        std::vector<cv::Point> sampled;
        for (int i = 0; i < n; i++){
            sampled.push_back(all_points[i]);
        }
        return sampled;
}