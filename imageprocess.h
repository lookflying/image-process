#ifndef IMAGEPROCESS_H
#define IMAGEPROCESS_H
#include "fimage.h"
#include "function.h"
#include "linearfunction.h"
#include <opencv2/core/core.hpp>
#include "function.h"
#include "edgedetect.h"
#include "blur.h"
#include "morphology.h"
#include "convolutionengine.h"
#include "miscellaneous.h"
class ImageProcess
{
public:
    ImageProcess();
    static void gray_linear_transform(FImage &in_out, int x_min, int x_max, int y_min, int y_max)__attribute__((deprecated));
    static void gray_linear_transform(cv::Mat in, cv::Mat &out, int x_min, int x_max, int y_min, int y_max);
    static void gray_fun_transform(FImage &in_out, Function* fun)__attribute__((deprecated));
    //only accept one channel image
    static void gray_fun_transform(cv::Mat in, cv::Mat &out, Function *fun);
    enum histogram_types{FREQUENCE, PROBABILITY};
    typedef int histogram_type;
    static Function* get_gray_histogram(FImage &in, histogram_type type = PROBABILITY)__attribute__((deprecated));
    static Function* get_gray_histogram(cv::Mat in, histogram_type type = PROBABILITY);
    static Function* get_histogram_equalization_fun(Function *fun);
    static Function* get_histogram_match_fun(Function *origin, Function *target);
    enum zoom_types{NEAREST, BILINEAR, BICUBIC};
    typedef int zoom_type;
    static void geometry_zoom(FImage &in_out, int percentage, zoom_type type = BICUBIC);
    static void geometry_rotate(FImage &in_out, double rad, zoom_type type = BICUBIC);
    static void geometry_rotate(cv::Mat in, cv::Mat &out, double degree, zoom_type type = BICUBIC);
    static uchar get_zoom_value(cv::Mat in, int x, int y, double scale, zoom_type type = BICUBIC, uchar d_value = 255);
    static void cut_edge(cv::Mat in, cv::Mat &out, uchar edge_value = 255);
    static void get_rotated_vertex(cv::Mat image, int center_x, int center_y, double rad, std::vector<cv::Point> &points);
    enum algebra_types{ADD, SUB, MUL, DIV};
    typedef int algebra_type;
    static void algebra(FImage &in_out, FImage &another, algebra_type type);

    static void edge_detect(FImage &in_out, EdgeDetect::edge_detect_type_t type)__attribute__((deprecated));
    static void edge_detect(cv::Mat &in, cv::Mat &out, EdgeDetect::edge_detect_type_t type);
    static void blur(FImage &in_out, Blur::blur_type_t type, int size, double sigma) __attribute__((deprecated));
    static void blur(cv::Mat in, cv::Mat &out, Blur::blur_type_t type, int size, double sigma);
    static void morphology_transform(FImage &in_out, Blur::blur_type_t type, cv::Mat se, int center_x, int center_y) __attribute__((deprecated));
    static void morphology_transform(cv::Mat in, cv::Mat &out, Morphology::morphology_type_t type, cv::Mat se, int center_x, int center_y);
    static cv::Mat& morphology_mask();
    static void threshold(FImage &in_out, Miscellaneous::threshold_type_t type, int t1, int t2)__attribute__((deprecated));
    static void threshold(cv::Mat in, cv::Mat &out, Miscellaneous::threshold_type_t type, int t1, int t2);
    static unsigned char auto_threshold(FImage &in_out, Miscellaneous::auto_threshold_type_t type, std::vector<double> parameters)__attribute__((deprecated));
    static unsigned char auto_threshold(cv::Mat in, cv::Mat &out, Miscellaneous::auto_threshold_type_t type, std::vector<double> parameters);
private:
    static int get_gray_scale(cv::Vec3b color);
    static cv::Vec3b to_gray_vec3b(int gray);
    static cv::Vec3b add(cv::Vec3b v1, cv::Vec3b v2);
    static cv::Vec3b subtract(cv::Vec3b v1, cv::Vec3b v2);
    static cv::Vec3b multiply(cv::Vec3b v1, cv::Vec3b v2);
    static cv::Vec3b divide(cv::Vec3b v1, cv::Vec3b v2);
    static void get_position_after_rotation_center(int center_x, int center_y, int x, int y, double rad, int &x_r, int &y_r);
    static void get_position_before_rotation_center(int center_x, int center_y, int x_r, int y_r, double rad, int &x, int &y);
    static void get_position_after_rotation(int x, int y, double rad, int &x_r, int &y_r);
    static void get_position_before_rotation(int x_r, int y_r, double rad, int &x, int &y);
    static void get_edge(int x, int y, int &pos_x, int &neg_x, int &pos_y, int &neg_y);

    static cv::Mat morphology_mask_;
};

#endif // IMAGEPROCESS_H
