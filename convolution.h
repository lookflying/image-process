#ifndef CONVOLUTION_H
#define CONVOLUTION_H
#include <opencv2/core/core.hpp>

typedef uchar convolution_action(cv::Mat input, cv::Mat kernel);

class Convolution
{
public:
    static uchar normal_convolution_action(cv::Mat input, cv::Mat kernel);
    static uchar morphology_action(cv::Mat input, cv::Mat kernel);
private:
    static uchar element_mul_sum(cv::Mat a, cv::Mat b);
    static uchar double_to_valid_uchar(double d);
};

#endif // CONVOLUTION_H
