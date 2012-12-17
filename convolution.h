#ifndef CONVOLUTION_H
#define CONVOLUTION_H
#include <opencv2/core/core.hpp>

typedef uchar convolution_action(cv::Mat& input, cv::Mat& kernel);
typedef int convolution_action2(cv::Mat& input, cv::Mat& input2, cv::Mat &kernel);
typedef double convolution_action_raw(cv::Mat& input, cv::Mat& kernel);


class Convolution
{
public:
    static uchar normal_convolution_action(cv::Mat& input, cv::Mat& kernel);
    static double normal_raw_convolution_action(cv::Mat& input, cv::Mat& kernel);


    static double element_mul_sum(cv::Mat& a, cv::Mat& b);
    static void to_uchar_mat(cv::Mat& in, cv::Mat& out);
    static void to_normalized_uchar_mat(cv::Mat& in, cv::Mat& out, float max);
    static void to_float_mat(cv::Mat &in, cv::Mat& out);
    static uchar double_to_valid_uchar(double d);
private:
};

#endif // CONVOLUTION_H
