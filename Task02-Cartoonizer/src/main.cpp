#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

cv::Mat cartoonize(const cv::Mat& in, int pyramids=2, int bilateral_passes=4) {
    cv::Mat down_sized,filtered;
    for(int i = 0; i < pyramids; i++) {
        cv::pyrDown(in,down_sized);
    }
    for(int i = 0; i < bilateral_passes; i++) {
        cv::bilateralFilter(down_sized, filtered, 9, 150, 150);
    }
    for(int i = 0; i < pyramids; i++) {
        cv::pyrUp(filtered, filtered);
    }
    if(filtered.size != in.size) {
        cv::resize(filtered, filtered, cv::Size{in.cols, in.rows});
    }
    cv::Mat grayscaled;
    cv::cvtColor(in,grayscaled,cv::COLOR_BGR2GRAY);
    cv::medianBlur(grayscaled,grayscaled,7);
    cv::adaptiveThreshold(grayscaled,grayscaled,255,cv::ADAPTIVE_THRESH_MEAN_C,cv::THRESH_BINARY,9,2);
    cv::cvtColor(grayscaled,grayscaled,cv::COLOR_GRAY2BGR);
    cv::Mat cartoon;
    cv::bitwise_and(filtered,grayscaled,cartoon);
    return cartoon;
}

int main(int argc, char** argv) {
    cv::Mat in1 = cv::imread("../../resources/image1.jpg");
    cv::Mat out1 = cartoonize(in1);
    cv::namedWindow("Example1",cv::WINDOW_NORMAL);
    cv::resizeWindow("Example1",1200,800);
    cv::imshow("Example1",out1);
    cv::imshow("Og:",in1);
    cv::waitKey(0);
    return 0;
}
