#ifndef CONVOLUTIONEGINE_H
#define CONVOLUTIONEGINE_H
#include <opencv2/core/core.hpp>

#include "convolution.h"
class ConvolutionEngine
{
public:
    static void run(cv::Mat& src, cv::Mat &dst, cv::Mat &kernel, convolution_action* action = Convolution::normal_convolution_action, int center_x = -1, int center_y = -1);
    static void run_raw(cv::Mat &src, cv::Mat &dst, cv::Mat &kernel, convolution_action_raw* action = Convolution::normal_raw_convolution_action, int center_x = -1, int center_y = -1);
//    void init(cv::Mat &src, cv::Mat &dst, cv::Mat &kernel, int center_x = -1 , int center_y = -1);
//private:
//    cv::Mat src_;
//    cv::Mat dst_;
//    cv::Mat kernel_;
//    cv::Mat temp_;
//    int src_col_;
//    int src_row_;
//    int kernel_col_;
//    int kernel_row_;
//    int temp_col_;
//    int temp_row_;
//    int center_x_;
//    int center_y_;
//    //only accept uchar data type
//    //one channel or three channels
//    cv::Scalar element_mul_sum(cv::Mat a, cv::Mat b);
//    cv::Mat normalize_kernel(cv::Mat k);


};

#endif // CONVOLUTIONEGINE_H
