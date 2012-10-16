#include "imageprocess.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <QDebug>
using namespace std;
using namespace cv;
ImageProcess::ImageProcess()
{
}

int ImageProcess::get_gray_scale(Vec3b color){
    return ((int)color(0) + (int)color(1) + (int)color(2)) / 3;
}

Vec3b ImageProcess::to_gray_scale(int gray){
    Vec3b color;
    color(0) = color(1) = color(2) = (uchar)gray;
    return color;
}

void ImageProcess::gray_linear_transform(FImage &in_out, int x_min, int x_max, int y_min, int y_max){
    LinearFunction fun(0, 255, 0, 255);
    fun.set(255, 255);
    Mat* img = &in_out.get_opencv_image();
    fun.set(x_min, y_min);
    fun.set(x_max, y_max);
    for (int i = 0; i < img->rows; ++i){
        for (int j = 0; j < img->cols; ++j){
            img->at<Vec3b>(i, j) = to_gray_scale(fun.get(get_gray_scale(img->at<Vec3b>(i, j))));
        }
    }
}

void ImageProcess::gray_log_transform(FImage &in_out, double a, double b, double c){

}

void ImageProcess::gray_exponent_transform(FImage &in_out, double a, double b, double c){

}
