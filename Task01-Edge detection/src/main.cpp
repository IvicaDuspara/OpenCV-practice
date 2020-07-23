#include <iostream>
#include <string>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

const std::string res1_rel_path = "../../resources/img1.jpg";
const std::string res2_rel_path = "../../resources/img2.jpg";
const std::string w1_name = "Example_in";
const std::string w2_name = "Example_out";

struct Image_Pack{
    int stddev[2] = {0,0};
    int threshholds[2] = {0,0};
    cv::Mat& m_in,m_o_blurred,m_o_cannied;
    cv::Size& m_s;
    Image_Pack(cv::Mat& in, cv::Mat& o_blurred, cv::Mat& o_cannied, cv::Size& s) : m_in{in}, m_o_blurred{o_blurred},
                                                                                   m_o_cannied{o_cannied}, m_s{s}
    {};
};

void output_window(Image_Pack& pack) {
    cv::GaussianBlur(pack.m_in, pack.m_o_blurred, pack.m_s, pack.stddev[0], pack.stddev[1]);
    cv::Canny(pack.m_o_blurred, pack.m_o_cannied, pack.threshholds[0], pack.threshholds[1]);
    cv::imshow(w2_name, pack.m_o_cannied);
}

int main (int argc, char** argv) {
    cv::Mat image1;
    if(argc != 2) {
        std::cout << "Usage: ./Task01 <path_to_image>|<1>|<2>";
        return -1;
    }
    std::string temp_arg(argv[1]);
    if(temp_arg == "1") {
        image1 = cv::imread(res1_rel_path);
    }

    else if(temp_arg == "2") {
        image1 = cv::imread(res2_rel_path);
    }
    else {
        image1 = cv::imread(argv[1]);
    }
    cv::Mat o_blurred, o_cannied;
    cv::Size s{5,5};
    Image_Pack pack1(image1, o_blurred, o_cannied,s);

    cv::namedWindow(w1_name,cv::WINDOW_NORMAL);
    cv::namedWindow(w2_name,cv::WINDOW_NORMAL);
    cv::resizeWindow(w1_name,1200,800);
    cv::resizeWindow(w2_name,1200,800);
    cv::createTrackbar("stddev_x",w2_name,&pack1.stddev[0],25,[](int position, void* params){
            auto* casted = reinterpret_cast<Image_Pack*>(params);
            casted->stddev[0] = position;
            output_window(*casted);

    },&pack1);
    cv::createTrackbar("stddev_y",w2_name,&pack1.stddev[1],25,[](int position, void* params){
            auto* casted = reinterpret_cast<Image_Pack*>(params);
            casted->stddev[1] = position;
            output_window(*casted);
    },&pack1);
    cv::createTrackbar("t1",w2_name,&pack1.threshholds[0],25,[](int position, void* params){
            auto* casted = reinterpret_cast<Image_Pack*>(params);
            casted->threshholds[0] = position;
            output_window(*casted);
    },&pack1);
    cv::createTrackbar("t2",w2_name,&pack1.threshholds[1],25,[](int position, void* params){
            auto* casted = reinterpret_cast<Image_Pack*>(params);
            casted->threshholds[1] = position;
            output_window(*casted);
    },&pack1);

    cv::imshow(w1_name,image1);
    output_window(pack1);
    cv::waitKey(0);
    return 0;
}