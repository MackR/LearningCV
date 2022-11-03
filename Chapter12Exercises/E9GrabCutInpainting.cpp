#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>

struct Ims {
    cv::Mat preDraw;
    cv::Mat postDraw;
    cv::Point2i pStart;

    Ims(cv::Mat preDraw, cv::Mat postDraw){
        this->preDraw = preDraw;
        this->postDraw = postDraw;
    }

};

void onMouse(int event, int x, int y, int flags, void *imgs)
{

    Ims* images = ((Ims *)imgs);
    cv::Mat preDraw = images->preDraw;
    cv::Mat postDraw = images->postDraw;

    cv::Point p(x, y);
    cv::Scalar white = {255, 255, 255, 255};

    if (event == cv::EVENT_LBUTTONDOWN)
    { // Start doing a new white masking
        images->pStart  = p;
        try
        {
            // Code that could throw an exception
            cv::destroyWindow("proc");
        }
        catch (...)
        {
            // Code that executes when an exception of type
        }
    }
    else if (event == cv::EVENT_MOUSEMOVE && flags & cv::EVENT_FLAG_LBUTTON)
    { // Continue doing white masking

        cv::Point pFinish(x, y);
        cv::Rect selection(images->pStart, pFinish);
        // std::cout << selection << '\n';
        postDraw = preDraw.clone();                      // cleans up the image from having prior rectangle on it
        // std::cout << "Reset image!" << "\n";
        cv::rectangle(postDraw, selection, white, 1); // draws the rectangle on the image
        // std::cout << "Drew Rectangle" << "\n";
        cv::imshow("img",postDraw);


    }

    else if (event == cv::EVENT_LBUTTONUP)
    { // create inpainted image based on masking and display it. End masking process
        // Wipe the images clean
        // cv::Mat copy = orig.clone();
        //image = orig.clone();
        std::cout << "Reset image!" << "\n";


        // Get and set the corners of selection rectangle
        cv::Point pFinish(x, y);
        cv::Point topLeft(images->pStart),
            bottomLeft(images->pStart.x, pFinish.y),
            topRight(pFinish.x, images->pStart.y),
            bottomRight(pFinish);
        cv::Rect selectionBox(images->pStart,pFinish);
        cv::Point corners[] = {topLeft, topRight, bottomRight, bottomLeft};
        std::cout << corners[1] << '\n';
        if (images->pStart == pFinish){std::cout << "Same start and end point" << std::endl; return;}


        // Fill the rectangle and alpha blend the images for transparent selection
        // cv::fillConvexPoly(*image, corners, 4, white);
        // std::cout << "Filled rectangle" << "\n";

        // cv::addWeighted(*image, 0.25, copy, 0.75, 0.0, *image);
        // std::cout << "Alpha blended" << "\n";

        // Create the Histogram
        // cv::Mat histogramImg(300, 300, CV_8UC3, clickedColor);

        // int histSize = 256;
        // float range[] = {0,256.0};
        // float histRange[] = {0,256.0};
        cv::Mat bgdModel;
        cv::Mat fgdModel;
        cv::Mat mask;
        cv::grabCut(preDraw,mask,selectionBox,bgdModel, fgdModel,4,cv::GC_INIT_WITH_RECT);
        typedef uchar PIXEL_T;
        PIXEL_T pixel = 0;
        cv::Mat proc1 = mask;
        for (int row = 0; row < proc1.rows; ++row){
            for (int col = 0; col < proc1.cols; ++col){
                pixel = proc1.at<PIXEL_T>(col,row);
                int area = 0;
                if (pixel <3){
                    pixel = proc1.at<PIXEL_T>(col,row) = 0;
                }
            }
        }
        cv::morphologyEx(mask,mask,cv::MORPH_CLOSE,cv::Mat(), cv::Point(-1,-1),2);
        cv::inpaint(preDraw,mask,postDraw,3,cv::INPAINT_NS);
        // cv::blur(postDraw,postDraw, cv::Size(3,3));

        // std::cout << "rectMask: " << rectMask << std::endl;
        cv::equalizeHist(proc1, proc1);

        cv::imshow("mask", proc1);
        cv::imshow("proc", postDraw);
        


    }
}

int main(int argc, char** argv){
    std::string path = "../Resources/PeopleLandscape.jpeg";
    //std::string path2 = "../Resources/img2.jpg";
    cv::Mat img;
    //cv::Mat img2;

    if (argc >1){
        cv::Mat img = cv::imread(argv[1],-1);
        //cv::Mat img2 = cv::imread(argv[2],-1);
}

    cv::namedWindow("img", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("mask", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("proc", cv::WINDOW_AUTOSIZE);
    if( img.empty()) {
        img = cv::imread(path, cv::IMREAD_COLOR);
        //img2 = cv::imread(path2, cv::IMREAD_COLOR);
        if( img.empty()) {
            std::cout << "No image provided";
            return -1;
        }
    }

    // Format image here
    cv::Mat fImg = img.clone();
    cv::resize(fImg,fImg,cv::Size(600,600));
    //cv::Mat fImgBW = fImg.clone();
    //cv::cvtColor(fImg,fImgBW,cv::COLOR_BGR2GRAY);
    //cv::Mat fImg2 = img2.clone();

    // Process image here
    cv::Mat proc = fImg.clone();

    cv::Mat preDraw = proc.clone();
    cv::Mat postDraw = proc.clone();

    Ims images(preDraw,postDraw); 

    imshow("img", images.preDraw);
    imshow("proc", images.postDraw);
    // imshow("mask", mask);

    cv::setMouseCallback("img",onMouse,&images);

    cv::waitKey(0);


    while (1){


        if(cv::waitKey(20) == 27) {break;}

    }
    cv::imshow("img",img);
    //cv::imshow("img2",img2);
    cv::imshow("proc",proc);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;

}