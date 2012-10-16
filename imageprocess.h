#ifndef IMAGEPROCESS_H
#define IMAGEPROCESS_H
#include "fimage.h"
#include "function.h"
#include "linearfunction.h"
#include <opencv2/core/core.hpp>
class ImageProcess
{
public:
    ImageProcess();
    static void gray_linear_transform(FImage &in_out, int x_min, int x_max, int y_min, int y_max);
    static void gray_log_transform(FImage &in_out, double a, double b, double c);
    static void gray_exponent_transform(FImage &in_out, double a, double b, double c);
private:
    static int get_gray_scale(cv::Vec3b color);
    static cv::Vec3b to_gray_scale(int gray);
};

#endif // IMAGEPROCESS_H
