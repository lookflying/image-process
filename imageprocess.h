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
private:
    static int get_gray_scale(cv::Vec3b color);
    static cv::Vec3b to_gray_vec3b(int gray);
};

#endif // IMAGEPROCESS_H
