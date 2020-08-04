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
    cv::Mat& m_in,m_o_auxiliary,m_o_output;
    cv::Size& m_s;
    Image_Pack(cv::Mat& in, cv::Mat& o_auxiliary, cv::Mat& o_output, cv::Size& s) : m_in{in}, m_o_auxiliary{o_auxiliary},
                                                                                   m_o_output{o_output}, m_s{s}
    {};
};

void output_window_mode_1(Image_Pack& pack) {
    cv::GaussianBlur(pack.m_in, pack.m_o_auxiliary, pack.m_s, pack.stddev[0], pack.stddev[1]);
    cv::Canny(pack.m_o_auxiliary, pack.m_o_output, pack.threshholds[0], pack.threshholds[1]);
    cv::imshow(w2_name, pack.m_o_output);
}

void output_window_mode_2(Image_Pack& pack) {
    cv::Mat k= cv::getStructuringElement(pack.stddev[0],
                                        cv::Size(2*pack.stddev[1] + 1, 2*pack.stddev[1] + 1),
                                        cv::Size{pack.stddev[1],pack.stddev[1]});
    cv::morphologyEx(pack.m_in,pack.m_o_output,2,k,cv::Point{-1,-1},pack.threshholds[0]);
    cv::imshow(w2_name,pack.m_o_output);
}

int main (int argc, char** argv) {
    cv::Mat image1;
    if(argc != 3) {
        std::cout << "Usage: ./Task01 <path_to_image>|<1>|<2> <1>|<2>\n";
        return -1;
    }
    std::string temp_path_arg(argv[1]);
    std::string temp_mode_arg(argv[2]);
    if(temp_path_arg == "1") {
        image1 = cv::imread(res1_rel_path);
    }

    else if(temp_path_arg == "2") {
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
    cv::imshow(w1_name,image1);
    if(temp_mode_arg == "1") {
        cv::createTrackbar("stddev_x",w2_name,&pack1.stddev[0],25,[](int position, void* params){
            auto* casted = reinterpret_cast<Image_Pack*>(params);
            casted->stddev[0] = position;
            output_window_mode_1(*casted);

        },&pack1);
        cv::createTrackbar("stddev_y",w2_name,&pack1.stddev[1],25,[](int position, void* params){
            auto* casted = reinterpret_cast<Image_Pack*>(params);
            casted->stddev[1] = position;
            output_window_mode_1(*casted);
        },&pack1);
        cv::createTrackbar("t1",w2_name,&pack1.threshholds[0],25,[](int position, void* params){
            auto* casted = reinterpret_cast<Image_Pack*>(params);
            casted->threshholds[0] = position;
            output_window_mode_1(*casted);
        },&pack1);
        cv::createTrackbar("t2",w2_name,&pack1.threshholds[1],25,[](int position, void* params){
            auto* casted = reinterpret_cast<Image_Pack*>(params);
            casted->threshholds[1] = position;
            output_window_mode_1(*casted);
        },&pack1);
        output_window_mode_1(pack1);
        cv::waitKey(0);
    }
    else if(temp_mode_arg == "2") {
        cv::createTrackbar("morph_elem",w2_name,&pack1.stddev[0],5,[](int position, void* params){
            auto* casted = reinterpret_cast<Image_Pack*>(params);
            casted->stddev[0] = position;
            output_window_mode_2(*casted);
        },&pack1);
        cv::createTrackbar("morph_size",w2_name,&pack1.stddev[1],21,[](int position, void* params){
            auto* casted = reinterpret_cast<Image_Pack*>(params);
            casted->stddev[1] = position;
            output_window_mode_2(*casted);
         },&pack1);
        cv::createTrackbar("iterations",w2_name,&pack1.threshholds[0],10 ,[](int position, void* params){
            auto* casted = reinterpret_cast<Image_Pack*>(params);
            casted->threshholds[0] = position;
            output_window_mode_2(*casted);
        },&pack1);
        output_window_mode_2(pack1);
        cv::waitKey(0);
    }
    else{
        std::cerr << "Invalid argument for operation mode.\n";
        return -1;
    }

    return 0;
}