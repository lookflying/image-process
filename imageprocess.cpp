#include "imageprocess.h"
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
ImageProcess::ImageProcess()
{
}

void ImageProcess::gray_linear_transform(FImage &in, FImage &out, int x_min, int x_max, int y_min, int y_max){
    LinearFunction fun(0, 255, 0, 255);
    fun.set(255, 255);
    Mat* img = &in.get_opencv_image();
    if(img->channels() > 1){
        cvtColor(in.get_opencv_image(), in.get_opencv_image(), CV_RGB2GRAY);
    }
    fun.set(x_min, y_min);
    fun.set(x_max, y_max);
    for (int i = 0; i < img->rows; ++i){
        for (int j = 0; j < img->cols; ++i){
            img->at<uchar>(i, j) = (uchar)fun.get((int)img->at<uchar>(i, j));
        }
    }

}

void ImageProcess::gray_log_transform(FImage &in, FImage &out, double a, double b, double c){

}

void ImageProcess::gray_exponent_transform(FImage &in, FImage &out, double a, double b, double c){

}
