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

Vec3b ImageProcess::to_gray_vec3b(int gray){
    Vec3b color;
    color(0) = color(1) = color(2) = (uchar)gray;
    return color;
}

void ImageProcess::gray_linear_transform(FImage &in_out, int x_min, int x_max, int y_min, int y_max){
    LinearFunction fun(0, 255, 0, 255);
    fun.set(255, 255);
    Mat *img = &in_out.get_opencv_image();
    fun.set(x_min, y_min);
    fun.set(x_max, y_max);
    for (int i = 0; i < img->rows; ++i){
        for (int j = 0; j < img->cols; ++j){
            img->at<Vec3b>(i, j) = to_gray_vec3b(fun.get(get_gray_scale(img->at<Vec3b>(i, j))));
        }
    }
}

void ImageProcess::gray_fun_transform(FImage &in_out, Function *fun){
    Mat* img = &in_out.get_opencv_image();
    for (int i = 0; i < img->rows; ++i){
        for (int j = 0; j < img->cols; ++j){
            img->at<Vec3b>(i, j) = to_gray_vec3b(fun->get(get_gray_scale(img->at<Vec3b>(i, j))));
        }
    }
}

Function* ImageProcess::get_gray_histogram(FImage in, histogram_type type){
    Mat *img = &in.get_opencv_image();
    vector<int> count(256);
    for (int i = 0; i < img->rows; ++i){
        for (int j = 0; j < img->cols; ++j){
            count[get_gray_scale(img->at<Vec3b>(i, j))] += 1;
        }
    }
    Function *fun;
    switch (type){
    case FREQUENCE:
    {
        int max = 0;
        for (unsigned int i = 0; i < count.size(); ++i){
            if (count[i] > max){
                max = count[i];
                qDebug()<<QString("%1 %2").arg(i).arg(max);
            }
        }
        fun = new Function(0, 255, 0, max);
        for (unsigned int i = 0; i < count.size(); ++i){
            fun->set(i, count[i]);
        }
        break;
    }
    case PROBABILITY:
    {
        int sum = img->rows * img->cols;
        int max = 0;
        for (unsigned int i = 0; i < count.size(); ++i){
            count[i] = count[i] * 100 / sum;
            if (count[i] > max)
                max = count[i];
        }
        fun = new Function(0, 255, 0, max);
        for (unsigned int i = 0; i < count.size(); ++i){
            qDebug()<<QString("%1  %2").arg(i).arg(count[i]);
            fun->set(i, count[i]);
        }
        break;
    }
    default:
        break;
    }
    return fun;
}
