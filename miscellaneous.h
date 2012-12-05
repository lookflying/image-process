#ifndef MISCELLANEOUS_H
#define MISCELLANEOUS_H
#include <opencv2/core/core.hpp>
#include <vector>
class Miscellaneous
{
public:
    enum histogram_types{PROBABILITY, FREQUENCE};
    typedef int histogram_type_t;
    static std::vector<double> histogram(cv::Mat src, histogram_type_t type = PROBABILITY);
    enum threshold_types{NORMAL_THRESHOLD,
                         DUAL_THRESHOLD};
    typedef int threshold_type_t;
    static void threshold(cv::Mat src, cv::Mat &dst, int th, threshold_type_t type = NORMAL_THRESHOLD, int optional_threshold = 0);
    enum auto_threshold_types{
        ISODATA,//parameters[0] percentage of 0s
                //parameters[1] initial threshold(optional)
        OTSU,
        ENTROPY,
        SOBEL_AREA
    };
    typedef int auto_threshold_type_t;
    static unsigned char threshold_action(cv::Mat &input, cv::Mat &kernel);
    static unsigned char auto_threshold(cv::Mat src, cv::Mat *dst, auto_threshold_type_t type, std::vector<double> parameters);
    static void turn_gray(cv::Mat &src, cv::Mat &dst);
};

#endif // MISCELLANEOUS_H
