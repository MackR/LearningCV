#include <iostream>
#include <opencv2/opencv.hpp>

void onTrackbarSlide(int pos, void *image){ // When we slide the trackbar,
    
}

int main(int argc, char** argv){

    std::string path = "../Resources/Greenery.jpg";
    cv::Mat img = cv::imread(path);
    cv::Mat img2;
    int sliderPos = 0;

    std::vector<cv::Mat> colors;

    cv::split(img, colors);
    std::cout << "Colors[1] channel number: " << colors[1].channels() << '\n';

    cv::Mat clone1, clone2;
    // Separately clone each set of data, 
    // because equating them will make them point to same object
    clone1 = colors[1].clone(); 
    clone2 = colors[1].clone();
    // std::cout << "Colors[1] channel number: " << colors[1].channels() << '\n';


    double minVal1 = 0, maxVal1 = 0;

    // std::cout << "Colors[1] channel number: " << colors[1].channels() << '\n';
    cv::minMaxIdx(clone1, &minVal1, &maxVal1);
    auto thresh = (unsigned char)((maxVal1-minVal1)/2.0);
    clone1.setTo(sliderPos);
    clone2.setTo(0);

    cv::namedWindow("img", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("img2", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("colors1", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("clone1", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("clone2", cv::WINDOW_AUTOSIZE);
    cv::createTrackbar("Threshold","clone2",&sliderPos, 255, onTrackbarSlide);
    cv::Mat orig = colors[1].clone();
for(;;){
    // When the values in colors[1] are greater than the threshold in clone1, set pixels in clone2 to 255
    if(cv::waitKey(10) == 27) break;
    cv::setTrackbarPos("clone2", "Threshold Control", sliderPos);
    colors[1] = orig.clone();
    clone1.setTo(sliderPos);
    cv::compare(colors[1],clone1,clone2,cv::CMP_LE);

    // cv::imshow("clone2",clone2);
    


    // std::cout << "Colors[1] channel number: " << colors[1].channels() << '\n';
    cv::subtract(colors[1], 255, colors[1],clone2);
    // std::cout << "Img2 channel number: " << img2.channels() << '\n';
    // std::cout << "Colors[1] channel number: " << colors[1].channels() << '\n';
    // std::cout << "Colors[2] channel number: " << colors[2].channels() << '\n';
    // std::cout << "Colors[0] channel number: " << colors[0].channels() << '\n';

    cv::merge(colors, img2);
    // std::cout << "Img2 channel number: " << img2.channels() << '\n';
    // cv::insertChannel(colors[1],img2,1);

    cv::imshow("img",img);
    cv::imshow("img2",img2);
    cv::imshow("colors1",colors[1]);
    cv::imshow("clone1",clone1);
    cv::imshow("clone2", clone2); // Set the capture stream position

}
    // cv::waitKey(0);

    cv::destroyAllWindows();

    return 0;
}