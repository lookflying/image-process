#ifndef BLUR_H
#define BLUR_H
#include <opencv2/core/core.hpp>
class Blur
{
public:
    enum blur_types{GAUSSIAN, MEDIAN, MEAN};
    typedef int blur_type_t;
    static void run(cv::Mat& src, cv::Mat& dst, blur_type_t type, int size = 3, double sigma = 0.5);
    static uchar median_blur_action(cv::Mat& input, cv::Mat& kernel);
    static uchar mean_blur_action(cv::Mat& input, cv::Mat& kernel);
private:
    //size should be odd
    static void get_gaussian_kernel(cv::Mat& out, int size, double sigma);
    static void get_median_kernel(cv::Mat& out, int size);
    static void get_mean_kernel(cv::Mat& out, int size);
};

#endif // BLUR_H
