#include "convolutionengine.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <highgui.h>
#include <vector>
#include <iostream>
using namespace cv;
using namespace std;

void ConvolutionEngine::run(Mat &src, Mat &dst, Mat &kernel, convolution_action* action, int center_x, int center_y){
    CV_Assert(src.channels() == 1 && kernel.channels() == 1 && src.elemSize() == 1);//ensure gray and uchar, kernel can use double
    int kernel_row, kernel_col;
    Mat temp, rst = Mat(src.rows, src.cols, src.type());
    kernel_row = kernel.rows;
    kernel_col = kernel.cols;
    if (center_x == -1){
        center_x = kernel_col / 2;
    }
    if (center_y == -1){
        center_y = kernel_row / 2;
    }
    copyMakeBorder(src, temp, center_y, kernel_row - 1 - center_y, center_x, kernel_col - 1 - center_x, BORDER_REPLICATE);
    for (int i = 0; i < src.rows; ++i){
        for (int j = 0; j < src.cols; ++j){
            Mat temp_roi = temp(Rect(j, i, kernel_col, kernel_row));
            rst.at<uchar>(i, j) = (*action)(temp_roi, kernel);
        }
    }
    dst = rst;
}

void ConvolutionEngine::run_raw(Mat &src, Mat &dst, Mat &kernel, convolution_action_raw* action, int center_x, int center_y){
    CV_Assert(src.channels() == 1 && kernel.channels() == 1 && src.elemSize() == 1);//ensure gray and uchar, kernel can use double
    int kernel_row, kernel_col;
    Mat temp, rst = Mat(src.rows, src.cols, CV_32FC1);
    kernel_row = kernel.rows;
    kernel_col = kernel.cols;
    if (center_x == -1){
        center_x = kernel_col / 2;
    }
    if (center_y == -1){
        center_y = kernel_row / 2;
    }
    copyMakeBorder(src, temp, center_y, kernel_row - 1 - center_y, center_x, kernel_col - 1 - center_x, BORDER_REPLICATE);

    for (int i = 0; i < src.rows; ++i){
        for (int j = 0; j < src.cols; ++j){
            Mat temp_roi = temp(Rect(j, i, kernel_col, kernel_row));
            rst.at<float>(i, j) = (*action)(temp_roi, kernel);
        }
    }
    dst = rst;

}

//void ConvolutionEngine::init(Mat &src, Mat &dst, Mat &kernel, int center_x, int center_y){
//    src_ = src;
//    dst_ = dst;
//    kernel_ = kernel;
//    center_x_ = center_x;
//    center_y_ = center_y;

//    src_col_ = src.cols;
//    src_row_ = src.rows;
//    kernel_col_ = kernel.cols;
//    kernel_row_ = kernel.rows;
//    temp_col_ = src_col_ + kernel_col_ - 1;
//    temp_row_ = src_row_ + kernel_row_ - 1;
//}

//void ConvolutionEngine::run(){
//    copyMakeBorder(src_, temp_, center_y_, kernel_row_ - 1 - center_y_, center_x_, kernel_col_ - 1 - center_x_, BORDER_REPLICATE);

//}

//}

//Mat ConvolutionEngine::normalize_kernel(Mat kernel){
//    double sum = 0;
//    for (int i = 0; i < kernel.rows; ++i){
//        for (int j = 0; j < kernel.cols; ++j){
////            sum +=
//        }
//    }
//}

