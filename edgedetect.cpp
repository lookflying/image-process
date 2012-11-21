#include "edgedetect.h"
#include "convolution.h"
#include "convolutionengine.h"
#include <opencv2/highgui/highgui.hpp>
#include <cmath>
#include <iostream>

using namespace cv;

const float EdgeDetect::roberts_operator_x_[] = {
    1, 0,
    0, -1,
};

const float EdgeDetect::roberts_operator_y_[] = {
    0, 1,
    -1, 0,
};
const float EdgeDetect::sobel_operator_x_[] = {
    -1, 0, 1,
    -2, 0, 2,
    -1, 0, 1,
};

const float EdgeDetect::sobel_operator_y_[] = {
    -1, -2, -1,
    0, 0, 0,
    1, 2, 1,
};

const float EdgeDetect::prewitt_operator_x_[] = {
    1, 0, -1,
    1, 0, -1,
    1, 0, -1,
};

const float EdgeDetect::prewitt_operator_y_[] = {
    -1, -1, -1,
    0, 0, 0,
    1, 1, 1,
};
void EdgeDetect::sqrt(Mat &src, Mat &dst){
    CV_Assert(src.channels() == 1 && src.elemSize() == sizeof(float));
    Mat temp = Mat(src.size(), src.type());
    for (int i = 0; i < src.rows; ++i){
        for (int j = 0; j < src.cols; ++j){
            float a = std::sqrt(src.at<float>(i, j));
            temp.at<float>(i, j) = a;
        }
    }
    dst = temp;
}



void EdgeDetect::run(Mat &src, Mat &dst, edge_detect_type_t type){
    Mat kernel_x, kernel_y;
    Mat temp_x, temp_y, temp;
    switch(type){
    case ROBERTS:
    {
        kernel_x = Mat(2, 2, CV_32FC1, (float*)roberts_operator_x_);
        kernel_y = Mat(2, 2, CV_32FC1, (float*)roberts_operator_y_);
        ConvolutionEngine::run_raw(src, temp_x, kernel_x, Convolution::normal_raw_convolution_action, 0, 0);
        ConvolutionEngine::run_raw(src, temp_y, kernel_y, Convolution::normal_raw_convolution_action, 0, 0);
        add(temp_x, temp_y, temp);
        multiply(temp, temp, temp);
        sqrt(temp, temp);
        Convolution::to_uchar_mat(temp, temp);
        dst = temp;
    }
        break;
    case SOBEL:
    {
        kernel_x = Mat(3, 3, CV_32FC1, (float*)sobel_operator_x_);
        kernel_y = Mat(3, 3, CV_32FC1, (float*)sobel_operator_y_);
        ConvolutionEngine::run_raw(src, temp_x, kernel_x, Convolution::normal_raw_convolution_action, 0, 0);
        ConvolutionEngine::run_raw(src, temp_y, kernel_y, Convolution::normal_raw_convolution_action, 0, 0);
        temp_x = abs(temp_x);
        temp_y = abs(temp_y);
        temp = max(temp_x, temp_y);
        Convolution::to_uchar_mat(temp, temp);
        dst = temp;
    }
        break;
    case PREWITT:
    {
        kernel_x = Mat(3, 3, CV_32FC1, (float*)prewitt_operator_x_);
        kernel_y = Mat(3, 3, CV_32FC1, (float*)prewitt_operator_y_);
        ConvolutionEngine::run_raw(src, temp_x, kernel_x, Convolution::normal_raw_convolution_action, 0, 0);
        ConvolutionEngine::run_raw(src, temp_y, kernel_y, Convolution::normal_raw_convolution_action, 0, 0);
        temp_x = abs(temp_x);
        temp_y = abs(temp_y);
        temp = max(temp_x, temp_y);
        Convolution::to_uchar_mat(temp, temp);
        dst = temp;
    }
        break;
    default:
        break;
    }
}
