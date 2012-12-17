#ifndef CONVOLUTIONEGINE_H
#define CONVOLUTIONEGINE_H
#include <opencv2/core/core.hpp>

#include "convolution.h"
class ConvolutionEngine
{
public:
    static void run(cv::Mat& src, cv::Mat &dst, cv::Mat &kernel, convolution_action* action = Convolution::normal_convolution_action, int center_x = -1, int center_y = -1);
    static void run(cv::Mat &src, cv::Mat &dst, cv::Mat &kernel, cv::Mat &mask, convolution_action *action = Convolution::normal_convolution_action, int center_x = -1, int center_y = -1);
    static void run_raw(cv::Mat &src, cv::Mat &dst, cv::Mat &kernel, convolution_action_raw* action = Convolution::normal_raw_convolution_action, int center_x = -1, int center_y = -1);

    static void run2(cv::Mat &src, cv::Mat &src2, cv::Mat &dst, cv::Mat &kernel, cv::Mat &mask, convolution_action2 *action, int center_x = -1, int center_y = -1);


};

#endif // CONVOLUTIONEGINE_H
