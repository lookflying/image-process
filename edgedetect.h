#ifndef EDGEDETECT_H
#define EDGEDETECT_H
#include <opencv2/core/core.hpp>

class EdgeDetect
{
public:
    static const float roberts_operator_x_[];
    static const float roberts_operator_y_[];
    static const float sobel_operator_x_[];
    static const float sobel_operator_y_[];
    static const float prewitt_operator_x_[];
    static const float prewitt_operator_y_[];

    enum edge_detect_types{ROBERTS, SOBEL, PREWITT};
    typedef int edge_detect_type_t;
    static void run(cv::Mat& src, cv::Mat& dst, edge_detect_type_t type);
private:
    void static sqrt(cv::Mat& src, cv::Mat& dst);
    void static to_uchar_mat(cv::Mat& in, cv::Mat& out);
};


#endif // EDGEDETECT_H
