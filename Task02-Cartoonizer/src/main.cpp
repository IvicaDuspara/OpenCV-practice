#include <iostream>
#include <string>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

const std::string res1_path = "../../resources/image1.jpg";
const std::string res2_path = "../../resources/image2.jpg";

struct Output_Pack{
    Output_Pack(cv::Mat& in, cv::Mat& out, int bilateral, int blur, int ab_size) : m_in{in}, m_out{out},
                                                                   m_bilateral{bilateral},m_blur{blur},
                                                                   m_ab_size{ab_size}{}
    cv::Mat& m_in;
    cv::Mat& m_out;
    int m_bilateral,m_blur,m_ab_size;
};

void cartoonize(Output_Pack& pack) {
    cv::Mat down_sized,filtered,grayscaled;
    for(int i = 0; i < 2; i++) {
        cv::pyrDown(pack.m_in,down_sized);
    }
    for(int i = 0; i < pack.m_bilateral; i++) {
        cv::bilateralFilter(down_sized,filtered,9,150,150);
    }
    for(int i = 0; i < 2; i++) {
        cv::pyrUp(filtered,filtered);
    }
    if(filtered.size != pack.m_in.size) {
        cv::resize(filtered, filtered, cv::Size{pack.m_in.cols, pack.m_in.rows});
    }
    cv::cvtColor(pack.m_in,grayscaled,cv::COLOR_BGR2GRAY);
    cv::medianBlur(grayscaled,grayscaled,pack.m_blur);
    cv::adaptiveThreshold(grayscaled,grayscaled,255,cv::ADAPTIVE_THRESH_MEAN_C,cv::THRESH_BINARY,pack.m_ab_size,2);
    cv::cvtColor(grayscaled,grayscaled,cv::COLOR_GRAY2BGR);
    cv::bitwise_and(filtered,grayscaled,pack.m_out);
}

void repaint(Output_Pack& pack) {
    cartoonize(pack);
    cv::imshow("Out",pack.m_out);
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
    cv::Mat out1;
    Output_Pack pack(in1,out1,2,5,7);
    cv::namedWindow("In",cv::WINDOW_NORMAL);
    cv::resizeWindow("In",1200,800);
    cv::namedWindow("Out",cv::WINDOW_NORMAL);
    cv::resizeWindow("Out",1200,800);
    cv::imshow("In",in1);
    repaint(pack);
    cv::waitKey(0);
    return 0;
}
