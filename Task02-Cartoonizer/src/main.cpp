#include <iostream>
#include <string>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

const std::string res1_path = "../../resources/image1.jpg";
const std::string res2_path = "../../resources/image2.jpg";


cv::Mat cartoonize(const cv::Mat& in, int bilateral_passes=0, int median_blur = 0, int adaptive_block_size = 0) {
    int pyramids = 2;
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
    cv::medianBlur(grayscaled,grayscaled,median_blur);
    cv::adaptiveThreshold(grayscaled,grayscaled,255,cv::ADAPTIVE_THRESH_MEAN_C,cv::THRESH_BINARY,adaptive_block_size,2);
    cv::cvtColor(grayscaled,grayscaled,cv::COLOR_GRAY2BGR);

    cv::Mat cartoon;
    cv::bitwise_and(filtered,grayscaled,cartoon);
    return cartoon;
}

int main(int argc, char** argv) {
    if(argc != 2) {
        std::cout << "Usage: ./Task02 <path to image>|<1>|<2>";
        return -1;
    }
    cv::Mat in1;
    std::string temp(argv[1]);
    if(temp == "1") {
        in1 = cv::imread(res1_path);
    }
    else if(temp == "2") {
        in1 = cv::imread(res2_path);
    }
    else {
        in1 = cv::imread(temp);
    }
    cv::Mat out1 = cartoonize(in1);
    Output_Pack pack(in1,out1,0,0,0);
    repaint(pack);
    cv::namedWindow("Example1",cv::WINDOW_NORMAL);
    cv::resizeWindow("Example1",1200,800);
    cv::imshow("Original",in1);
    cv::imshow("Cartoonized",out1);
    cv::waitKey(0);
    return 0;
}
