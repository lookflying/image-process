#ifndef IMAGEPROCESS_H
#define IMAGEPROCESS_H
#include "fimage.h"
#include "function.h"
#include "linearfunction.h"
#include <opencv2/core/core.hpp>
#include "function.h"
class ImageProcess
{
public:
    ImageProcess();
    static void gray_linear_transform(FImage &in_out, int x_min, int x_max, int y_min, int y_max);
    static void gray_fun_transform(FImage &in_out, Function* fun);
    enum histogram_types{FREQUENCE, PROBABILITY};
    typedef int histogram_type;
    static Function* get_gray_histogram(FImage &in, histogram_type type = PROBABILITY);
    static Function* get_histogram_equalization_fun(Function *fun);
    static Function* get_histogram_match_fun(Function *origin, Function *target);
    enum zoom_types{Nearest, BILINEAR, BICUBIC};
    typedef int zoom_type;
    static void geometry_zoom(FImage &in_out, int percentage, zoom_type type = BICUBIC);
private:
    static int get_gray_scale(cv::Vec3b color);
    static cv::Vec3b to_gray_vec3b(int gray);
    static cv::Vec3b add(cv::Vec3b v1, cv::Vec3b v2);
};

#endif // IMAGEPROCESS_H
