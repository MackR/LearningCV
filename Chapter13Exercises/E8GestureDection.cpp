#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#include "../CustomTools.cpp"

int main(int argc, char **argv)
{

    std::string paths[] = {"", "", "", "", ""};
    std::string path2 = "../Resources/Arm3.jpg";
    cv::Mat imgs[3];
    cv::Mat img2, fImg2, fImg2HSV, fImg2GRAY, fImg2BGR;

    img2 = cv::imread(path2);
    cv::resize(img2, fImg2, cv::Size(400, 400));
    cv::cvtColor(fImg2, fImg2HSV, cv::COLOR_BGR2HSV);
    fImg2BGR = fImg2.clone();

    for (int i = 1; i <= 3; ++i)
    {
        paths[i - 1] = "../Resources/WebcamSampleSkin" + std::to_string(i) + ".jpg";
    }

    for (int i = 0; i < 3; ++i)
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
        std::string winName = "Skin" + std::to_string(i + 1);
        cv::namedWindow(winName, cv::WINDOW_AUTOSIZE);
        cv::imshow(winName, imgs[i]);
        cv::waitKey(0);
        cv::destroyAllWindows();
    }

    

    int xshift1 = 200, xshift2 = 200, xshift3 = 275;
    int yshift1 = 200, yshift2 = 200, yshift3 = 150;
    cv::Mat roi1(imgs[0], cv::Range(0 + yshift1, 100 + yshift1), cv::Range(0 + xshift1, 100 + xshift1));
    cv::Mat roi2(imgs[1], cv::Range(0 + yshift2, 100 + yshift2), cv::Range(0 + xshift2, 100 + xshift2));
    cv::Mat roi3(imgs[2], cv::Range(0 + yshift3, 75 + yshift3), cv::Range(0 + xshift3, 75 + xshift3));
    cv::Mat rois[] = {roi1, roi2, roi3};
    std::vector<cv::Mat> roisV = {roi1, roi2, roi3};

    displayImages(roisV,{"roi1","roi2","roi3"});

    cv::Mat hists[5];
    int dims[] = {0, 1}; // We only want the hue saturation values.
    float h_Range[] = {0, 180};
    float s_Range[] = {0, 255};
    float bgr_range[] = {0, 255};
    // float v_Range[] = {0, 100};
    const float *ranges[] = {h_Range, s_Range};
    int histSize[] = {16, 16};
    int histSizeBGR[] = {16, 16, 16};

    cv::Mat histOut;

    cv::calcHist(rois, (int)(sizeof(hists) / sizeof(hists[0])),
                 dims, cv::noArray(), histOut, 2, histSize, ranges, true);

    cv::Mat backProject, fImg2MeanShift;

    //cv::pyrMeanShiftFiltering(fImg2HSV, fImg2MeanShift, 5, 50);
    // DISPLAYIMAGE(fImg2HSV);

    cv::calcBackProject(&fImg2HSV, 1, dims, histOut, backProject, ranges);

    cv::Mat thumbUp1 = cv::imread("../Resources/WebcamThumbUp1.jpg"), thumbUp1Project;
    cv::resize(thumbUp1, thumbUp1, cv::Size(400,400));
    cv::cvtColor(thumbUp1,thumbUp1,cv::COLOR_BGR2HSV);
    cv::Mat thumbUp2 = cv::imread("../Resources/WebcamThumbUp2.jpg"), thumbUp2Project;
    cv::resize(thumbUp2, thumbUp2, cv::Size(400,400));
    cv::cvtColor(thumbUp2,thumbUp2,cv::COLOR_BGR2HSV);
    cv::Mat thumbUp3 = cv::imread("../Resources/WebcamThumbUp3.jpg"), thumbUp3Project;
    cv::resize(thumbUp3, thumbUp3, cv::Size(400,400));
    cv::cvtColor(thumbUp3,thumbUp3,cv::COLOR_BGR2HSV);
    cv::Mat thumbUp4 = cv::imread("../Resources/WebcamThumbUp4.jpg"), thumbUp4Project;
    cv::resize(thumbUp4, thumbUp4, cv::Size(400,400));
    cv::cvtColor(thumbUp4,thumbUp4,cv::COLOR_BGR2HSV);
    cv::Mat thumbDown1 = cv::imread("../Resources/WebcamThumbDown1.jpg"), thumbDown1Project;
    cv::resize(thumbDown1, thumbDown1, cv::Size(400,400));
    cv::cvtColor(thumbDown1,thumbDown1,cv::COLOR_BGR2HSV);
    cv::Mat thumbDown2 = cv::imread("../Resources/WebcamThumbDown2.jpg"), thumbDown2Project;
    cv::resize(thumbDown2, thumbDown2, cv::Size(400,400));
    cv::cvtColor(thumbDown2,thumbDown2,cv::COLOR_BGR2HSV);
    cv::Mat thumbDown3 = cv::imread("../Resources/WebcamThumbDown3.jpg"), thumbDown3Project;
    cv::resize(thumbDown3, thumbDown3, cv::Size(400,400));
    cv::cvtColor(thumbDown3,thumbDown3,cv::COLOR_BGR2HSV);
    cv::Mat thumbDown4 = cv::imread("../Resources/WebcamThumbDown4.jpg"), thumbDown4Project;
    cv::resize(thumbDown4, thumbDown4, cv::Size(400,400));
    cv::cvtColor(thumbDown4,thumbDown4,cv::COLOR_BGR2HSV);
    cv::Mat thumbUpLeft1 = cv::imread("../Resources/WebcamThumbUpLeft1.jpg"), thumbUpLeft1Project;
    cv::resize( thumbUpLeft1,  thumbUpLeft1, cv::Size(400,400));
    cv::cvtColor(thumbUpLeft1,thumbUpLeft1,cv::COLOR_BGR2HSV);
    cv::Mat thumbUpLeft2 = cv::imread("../Resources/WebcamThumbUpLeft2.jpg"), thumbUpLeft2Project;
    cv::resize( thumbUpLeft2,  thumbUpLeft2, cv::Size(400,400));
    cv::cvtColor(thumbUpLeft2,thumbUpLeft2,cv::COLOR_BGR2HSV);
    cv::Mat thumbUpLeft3 = cv::imread("../Resources/WebcamThumbUpLeft3.jpg"), thumbUpLeft3Project;
    cv::resize( thumbUpLeft3,  thumbUpLeft3, cv::Size(400,400));
    cv::cvtColor(thumbUpLeft3,thumbUpLeft3,cv::COLOR_BGR2HSV);
    cv::Mat thumbUpLeft4 = cv::imread("../Resources/WebcamThumbUpLeft4.jpg"), thumbUpLeft4Project;
    cv::resize( thumbUpLeft4,  thumbUpLeft4, cv::Size(400,400));
    cv::cvtColor(thumbUpLeft4,thumbUpLeft4,cv::COLOR_BGR2HSV);
    cv::Mat thumbUpRight1 = cv::imread("../Resources/WebcamThumbUpRight1.jpg"), thumbUpRight1Project;
    cv::resize(thumbUpRight1, thumbUpRight1, cv::Size(400,400));
    cv::cvtColor(thumbUpRight1,thumbUpRight1,cv::COLOR_BGR2HSV);
    cv::Mat thumbUpRight2 = cv::imread("../Resources/WebcamThumbUpRight2.jpg"), thumbUpRight2Project;
    cv::resize(thumbUpRight2, thumbUpRight2, cv::Size(400,400));
    cv::cvtColor(thumbUpRight2,thumbUpRight2,cv::COLOR_BGR2HSV);
    cv::Mat thumbUpRight3 = cv::imread("../Resources/WebcamThumbUpRight3.jpg"), thumbUpRight3Project;
    cv::resize(thumbUpRight3, thumbUpRight3, cv::Size(400,400));
    cv::cvtColor(thumbUpRight3,thumbUpRight3,cv::COLOR_BGR2HSV);
    cv::Mat thumbUpRight4 = cv::imread("../Resources/WebcamThumbUpRight4.jpg"), thumbUpRight4Project;
    cv::resize(thumbUpRight4, thumbUpRight4, cv::Size(400,400));
    cv::cvtColor(thumbUpRight4,thumbUpRight4,cv::COLOR_BGR2HSV);
    cv::Mat thumbRight1 = cv::imread("../Resources/WebcamThumbRight1.jpg"), thumbRight1Project;
    cv::resize(thumbRight1, thumbRight1, cv::Size(400,400));
    cv::cvtColor(thumbRight1,thumbRight1,cv::COLOR_BGR2HSV);
    cv::Mat thumbRight2 = cv::imread("../Resources/WebcamThumbRight2.jpg"), thumbRight2Project;
    cv::resize(thumbRight2, thumbRight2, cv::Size(400,400));
    cv::cvtColor(thumbRight2,thumbRight2,cv::COLOR_BGR2HSV);
    cv::Mat thumbRight3 = cv::imread("../Resources/WebcamThumbRight3.jpg"), thumbRight3Project;
    cv::resize(thumbRight3, thumbRight3, cv::Size(400,400));
    cv::cvtColor(thumbRight3,thumbRight3,cv::COLOR_BGR2HSV);
    cv::Mat thumbRight4 = cv::imread("../Resources/WebcamThumbRight4.jpg"), thumbRight4Project;
    cv::resize(thumbRight4, thumbRight4, cv::Size(400,400));
    cv::cvtColor(thumbRight4,thumbRight4,cv::COLOR_BGR2HSV);
    cv::Mat thumbRight5 = cv::imread("../Resources/WebcamThumbRight5.jpg"), thumbRight5Project;
    cv::resize(thumbRight5, thumbRight5, cv::Size(400,400));
    cv::cvtColor(thumbRight5,thumbRight5,cv::COLOR_BGR2HSV);
    cv::Mat thumbLeft1 = cv::imread("../Resources/WebcamThumbLeft1.jpg"), thumbLeft1Project;
    cv::resize(thumbLeft1, thumbLeft1, cv::Size(400,400));
    cv::cvtColor(thumbLeft1,thumbLeft1,cv::COLOR_BGR2HSV);
    cv::Mat thumbLeft2 = cv::imread("../Resources/WebcamThumbLeft2.jpg"), thumbLeft2Project;
    cv::resize(thumbLeft2, thumbLeft2, cv::Size(400,400));
    cv::cvtColor(thumbLeft2,thumbLeft2,cv::COLOR_BGR2HSV);
    cv::Mat thumbLeft3 = cv::imread("../Resources/WebcamThumbLeft3.jpg"), thumbLeft3Project;
    cv::resize(thumbLeft3, thumbLeft3, cv::Size(400,400));
    cv::cvtColor(thumbLeft3,thumbLeft3,cv::COLOR_BGR2HSV);
    cv::Mat thumbLeft4 = cv::imread("../Resources/WebcamThumbLeft4.jpg"), thumbLeft4Project;
    cv::resize(thumbLeft4, thumbLeft4, cv::Size(400,400));
    cv::cvtColor(thumbLeft4,thumbLeft4,cv::COLOR_BGR2HSV);

    cv::resize(img2, fImg2, cv::Size(400, 400));

    cv::Mat thumbUpTrain[] = {thumbUp1, thumbUp2,thumbUp3};
    cv::Mat thumbDownTrain[] = {thumbDown1, thumbDown2,thumbDown3};
    cv::Mat thumbLeftTrain[] = {thumbLeft1, thumbLeft2,thumbLeft3};
    cv::Mat thumbRightTrain[] = {thumbRight1, thumbRight2,thumbRight3};
    cv::Mat thumbUpRightTrain[] = {thumbUpRight1, thumbUpRight2,thumbUpRight3};
    cv::Mat thumbUpLeftTrain[] = {thumbUpLeft1, thumbUpLeft2,thumbUpLeft3};

    cv::Mat thumbUpTrainProject[] = {thumbUp1Project, thumbUp2Project,thumbUp3Project};
    cv::Mat thumbDownTrainProject[] = {thumbDown1Project, thumbDown2Project,thumbDown3Project};
    cv::Mat thumbLeftTrainProject[] = {thumbLeft1Project, thumbLeft2Project,thumbLeft3Project};
    cv::Mat thumbRightTrainProject[] = {thumbRight1Project, thumbRight2Project,thumbRight3Project};
    cv::Mat thumbUpRightTrainProject[] = {thumbUpRight1Project, thumbUpRight2Project,thumbUpRight3Project};
    cv::Mat thumbUpLeftTrainProject[] = {thumbUpLeft1Project, thumbUpLeft2Project,thumbUpLeft3Project};

    for (int i = 0; i < 3; ++i){
        cv::calcBackProject(thumbUpTrain, 3, dims, histOut, thumbUpTrainProject, ranges); // 


    }


    std::cout << "Hit end of images" << std::endl;

    //DISPLAYIMAGE(backProject); // Macro that gets the name of my variable and calls displayImages("img", img)

    cv::morphologyEx(backProject, backProject, cv::MORPH_OPEN, cv::Mat()); // gets rid of white noise
    DISPLAYIMAGE(backProject);                                             // Macro that gets the name of my variable and calls displayImages("img", img)

    cv::threshold(backProject, backProject, 60, 255, cv::THRESH_BINARY); // If probability is below 100/255, make it zero, otherwise, make it 100%
    DISPLAYIMAGE(backProject);                                           // Macro that gets the name of my variable and calls displayImages("img", img)

    floodFillLargestRegion(backProject, backProject); // Function within CustomTools.cpp
    DISPLAYIMAGE(backProject);

    cv::Mat mask;
    cv::morphologyEx(backProject, mask, cv::MORPH_DILATE, cv::Mat(), cv::Point(-1, -1), 5);
    //cv::morphologyEx(backProject,mask,cv::MORPH_GRADIENT,cv::Mat(), cv::Point(-1, -1), 2);
    floodFillLargestRegion(mask,mask);


    std::vector<cv::Mat> imgs2 = {fImg2, mask};
    std::vector<std::string> names = {"fImg2", "mask"};
    displayImages(imgs2, names); // CustomTools.cpp // Accepts imgs as array and names as vector

    cv::Mat masked = fImg2.clone();
    cv::Mat inverseMask;
    cv::Mat dx, dy, angle, magnitude;
    cv::bitwise_not(mask, inverseMask);
    // masked.setTo(0, inverseMask); // just as good at bitwise_and mask
    cv::Mat circle = cv::imread("../Resources/circle2.png", cv::IMREAD_COLOR);
    cv::pyrDown(circle, circle);
    cv::cvtColor(fImg2BGR, fImg2GRAY, cv::COLOR_BGR2GRAY);
    cv::GaussianBlur(fImg2GRAY, fImg2GRAY, cv::Size(9, 9), 0);
    DISPLAYIMAGE(fImg2GRAY);
    cv::threshold(backProject, mask, 80, 255, cv::THRESH_TOZERO);

    cv::Sobel(mask, dx, CV_32F, 1, 0);
    cv::Sobel(mask, dy, CV_32F, 0, 1);
    dx.setTo(0,inverseMask);
    dy.setTo(0,inverseMask);
    displayImages(std::vector<cv::Mat>{dx, dy}, {"dx", "dy"});

    cv::phase(dx, dy, angle, true);
    angle.convertTo(angle, CV_32FC1, 1.0 / 360.0);
    cv::magnitude(dx, dy, magnitude);
    magnitude.convertTo(magnitude, CV_32F);
    DISPLAYIMAGE(angle);

    cv::Mat colorMapAngle = angle.clone();
    cv::normalize(colorMapAngle, colorMapAngle, 360, 0, cv::NORM_MINMAX);
    cv::Mat saturation = angle.clone();
    cv::Mat vibrance = angle.clone();
    cv::Mat result;

    std::vector<cv::Mat> combo = {colorMapAngle, cv::Mat::ones(angle.size(), angle.type()), vibrance};
    cv::merge(combo, result);
    cv::cvtColor(result, result, cv::COLOR_HSV2BGR);
    //circle.convertTo(circle,CV_32FC3);
    //std::cout << circle.channels() << " channel num: " << result.channels() << std::endl;
    //cv::hconcat(cv::Mat {circle,result},result);

    DISPLAYIMAGE(result);
    // cv::imshow("img2",img2);

    cv::destroyAllWindows();
    return 0;
}