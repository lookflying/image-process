#include "blur.h"
#include <convolution.h>
#include <convolutionengine.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <algorithm>
using namespace cv;


void Blur::run(Mat &src, Mat &dst, blur_type_t type, int size, double sigma){
    Mat kernel, temp;
    CV_Assert(src.channels() == 1);
    switch(type){
    case GAUSSIAN:{
        get_gaussian_kernel(kernel, size, sigma);
        Mat kernel_transpose = kernel.t(), temp_x, temp_y;
        ConvolutionEngine::run_raw(src, temp_x, kernel, Convolution::normal_raw_convolution_action);
        ConvolutionEngine::run_raw(src, temp_y, kernel_transpose, Convolution::normal_raw_convolution_action);
        temp = temp_x / 2 + temp_y / 2;
        Convolution::to_uchar_mat(temp, temp);
        dst = temp;
    }
        break;
    case MEDIAN:{
        get_median_kernel(kernel, size);
        ConvolutionEngine::run(src, temp, kernel, median_blur_action);
        dst = temp;
    }
        break;
    case MEAN:{
        get_mean_kernel(kernel, size);
        ConvolutionEngine::run(src, temp, kernel, mean_blur_action);
        dst = temp;
    }
        break;
    default:
        break;
    }

}


void Blur::get_gaussian_kernel(Mat &out, int size, double sigma){
    if (size % 2 != 1){
        ++size;
    }
    out = getGaussianKernel(size, sigma, CV_32F);
}

uchar Blur::mean_blur_action(Mat& input, Mat& kernel){
    Scalar rst = mean(input);
    return rst[0];
}

void Blur::get_mean_kernel(Mat &out, int size){
    if (size % 2 != 1){
        ++size;
    }
    out = Mat(size, size, CV_32FC1);
}

uchar Blur::median_blur_action(Mat& input, Mat& kernel){
    Mat temp;
    input.copyTo(temp);
    MatIterator_<uchar> it = temp.begin<uchar>(), it_end = temp.end<uchar>();
    std::sort(it, it_end);
    return temp.at<uchar>(temp.rows / 2, temp.cols / 2);
}

void Blur::get_median_kernel(Mat &out, int size){
    if (size % 2 != 1){
        ++size;
    }
    out = Mat(size, size, CV_32FC1);
}
