#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>

void onMouse(int event, int x, int y, int flags, void *img){
    cv::Point2f p(x,y);
    cv::Mat fImg = *((cv::Mat*)img); // Take the void pointer and cast as a cv::Mat pointer, then dereference it.
    cv::Mat proc = fImg.clone();
    // cv::logPolar(proc,proc,p,0.55,cv::WARP_FILL_OUTLIERS);
    cv::logPolar(proc, proc,
        p,
        80,
        cv::WARP_FILL_OUTLIERS);
    std::cout << "Found mouse event point: " << p << std::endl;
    cv::imshow("img", fImg);
    cv::imshow("proc", proc);
    cv::waitKey(20);
}

int main(int argc, char** argv){
    std::string path = "../Resources/GreenDetail.jpg";
    //std::string path2 = "../Resources/img2.jpg";
    cv::Mat img;
    //cv::Mat img2;

    if (argc >1){
        cv::Mat img = cv::imread(argv[1],-1);
        //cv::Mat img2 = cv::imread(argv[2],-1);
}

    cv::namedWindow("img", cv::WINDOW_AUTOSIZE);
    //cv::namedWindow("img2", cv::WINDOW_AUTOSIZE);
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

    cv::setMouseCallback("img",onMouse, &fImg);

    cv::Mat proc = fImg.clone();
    while(1){

    
    if(cv::waitKey(20) == 27) break;

    //cv::imshow("img",img);
    // if(counter > 100){
    //     img = orig.clone();
    //     counter = 0;
    // }
    // ++counter;

    }
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;

}

//Exercise 3:
// A log-polar transform takes shapes of different rotations and sizes into a space
// where these correspond to shifts in the θ-axis and log(r) axis. The Fourier trans‐
// form is translation invariant. How can we use these facts to force shapes of differ‐
// ent sizes and rotations to automatically give equivalent representations in the
// log-polar domain?

// Answer: If the log-polar warps all sizes and orientations to the same orientation but shifted along
//         the axies differently, and the fourier only looks for certain wave patterns/line in an image
//         we can use log-polar, then fourier to get an image where all shapes look the same and appear
//         as a specific kind of pattern in the fourier. As long as the same shapes are in two images?