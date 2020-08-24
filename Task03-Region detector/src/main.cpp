#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
const char* res1_path = "../../resources/blank1.jpg";
const char* res2_path = "../../resources/items1.jpg";
constexpr const int dilation_kernel_size = 7;
constexpr const int dilation_iteration = 8;
constexpr const int mb_kernel_size = 5;

struct ImagePack{
    cv::Mat& m_o_ref;
    cv::Mat& m_i_ref;
    int m_value;

    ImagePack(cv::Mat& i_ref, cv::Mat& o_ref, int value) : m_i_ref{i_ref}, m_o_ref{o_ref},m_value{value}{};
};

cv::Mat removeShadows(const cv::Mat& input) {
    cv::Mat aux;
    auto dilation_kernel = cv::getStructuringElement(cv::MORPH_DILATE,cv::Size{dilation_kernel_size,dilation_kernel_size});
    cv::dilate(input,aux,dilation_kernel,cv::Point{-1,-1},dilation_iteration);
    cv::medianBlur(aux,aux,mb_kernel_size);
    cv::Mat diff;
    cv::absdiff(input,aux,diff);
    diff = 255 - diff;
    cv::normalize(diff,diff,0,255,cv::NORM_MINMAX,CV_8UC1);
    cv::threshold(diff,diff,230,0,cv::THRESH_TRUNC);
    cv::normalize(diff,diff,0,255,cv::NORM_MINMAX,CV_8UC1);
    return diff;
}


void repaint(ImagePack& iPack) {
    cv::threshold(iPack.m_i_ref,iPack.m_o_ref,iPack.m_value,255,0);
    cv::imshow("Win1",iPack.m_o_ref);
}

int main (int argc, char** argv) {
    cv::Mat in1 = cv::imread(res2_path);
    cv::cvtColor(in1,in1,cv::COLOR_BGR2GRAY);
    cv::Mat out;
    cv::threshold(in1,out,0,255,0);
    ImagePack pack{in1,out,0};
    cv::namedWindow("Win0",cv::WINDOW_NORMAL);
    cv::resizeWindow("Win0",800,600);
    cv::imshow("Win0",in1);
    cv::namedWindow("Win1",cv::WINDOW_NORMAL);
    cv::resizeWindow("Win1",800,600);
    cv::createTrackbar("Threshold","Win1",&pack.m_value,255,[](int pos, void* params){
        auto* casted = static_cast<ImagePack*>(params);
        casted->m_value = pos;
        repaint(*casted);
    },&pack);
    cv::imshow("Win1",out);
    cv::waitKey(0);
    return 0;
}