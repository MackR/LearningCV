// WARNING: This function fails with image sizes bigger than 100x100. 
// Probably because of the excessively large intgration over the randn image


#include <iostream>
#include <opencv2/opencv.hpp>

int main(int argc, char **argv)
{

    cv::namedWindow("img", 1);
    cv::namedWindow("sum", 1);

    cv::Mat img(100, 100, CV_8U);
    cv::Mat sum(100, 100, CV_64F);
    cv::randu(img, 0, 255);

    // cv::imshow("img",img);
    // std::cout << img << std::endl;
    // std::cout << img.at<int>(1,1);
    // cv::waitKey();

    for (int row = 0; row < img.rows; ++row)
    {
        // uchar* p = img.ptr(row);
        // uchar* psum = sum.ptr(row);
        for (int col = 0; col < img.cols; ++col)
        {
            cv::Mat ROI(img, cv::Rect(0, 0, col + 1, row + 1));
            _Float64 val = cv::sum(ROI)[0];
            sum.at<_Float64>(col, row) = val;
            if(row+1 == 25 && col+1 == 25){
                std::cout << "25,25 is: " << val << std::endl;    
            } 
            // std::cout << "The value that went into sum at col: " << col +1
            // << " Row: " << row + 1 << " is " << val << std::endl;
            // std::cout << std::endl;
        }
    }

    std::cout << "25,25 is: " << sum.at<_Float64>(24,24) << std::endl;
    double maxValV = 0;
    double minValV = 0;
    double* minVal = &minValV;
    double* maxVal = &maxValV;
    
    // std::cout << "The address that the pointer points to is " << maxVal << std::endl;
    // std::cout << "The address of the pointer is " << &maxVal << std::endl;
    // std::cout << "The value of the pointer is " << *maxVal << std::endl;



    cv::minMaxIdx(sum, minVal, maxVal);
    std::cout << "Maxval value is: " << *maxVal << std::endl;

    sum /= (_Float64)*maxVal;
    //sum.convertTo(output8UC, CV_8U); 
    std::cout << "50,50 sum is: " << sum.at<_Float64>(49,49) << std::endl;
    // std::cout << "25,25 output is: " << output8UC.at<int>(24,24) << std::endl;
    // std::cout << "The max value is: " << output8UC.at<int>(output8UC.max.x, output8UC.max.y);
    //std::cout << sum << std::endl;
    // cv::normalize(sum,output,0,255,cv::NORM_MINMAX,);
    // std::cout << "After convertTo() 25,25 is: " << output.at<int>(24, 24) << std::endl;

    // // double max = cv::max(sum,)

    // std::cout << "After convertTo() 25,25 is: " << output.at<int>(24, 24) << std::endl;

    cv::imshow("img", img);
    cv::imshow("sum", sum);

    while(1){
        if(cv::waitKey(27) == 27) break; 
    }
    

    /*
        for(auto it = )
        sum.at<float>(0,0) = img.at<float>(0,0) + img.at<float>(0,0) + sum.at<float>(x-1,y-1)
    */

    return 0;
}