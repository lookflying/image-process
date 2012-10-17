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

Function* ImageProcess::get_gray_histogram(FImage &in, histogram_type type){
    Mat *img = &in.get_opencv_image();
    if(img->empty())
        return new Function();
    vector<int> count(256);
    count.assign(count.size(), 0);
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
            fun->set(i, count[i]);
        }
        break;
    }
    default:
        break;
    }
    return fun;
}

Function* ImageProcess::get_histogram_equalization_fun(Function *fun){
    double sum = 0;
    int min_in, max_in, min_out, max_out;
    fun->get_range(min_in, max_in, min_out, max_out);
    if (min_in != 0 || max_in != 255)
        return new Function();
    int l = 255;
    vector<double> temp(l + 1);
    for (int i = 0; i <= l; ++i){
        sum += static_cast<double>(fun->get(min_in + i));
        temp[i] = sum;
    }
    for (int i = 0; i <= l; ++i){
        temp[i] = temp[i] * l / sum;
    }
    Function *new_fun = new Function(0, 255, 0, 255);
    for (int i = 0; i <= l; ++i){
        new_fun->set(i, static_cast<int>(temp[i]));
    }
    return new_fun;
}

Function* ImageProcess::get_histogram_match_fun(Function *origin, Function *target){
    double sum_origin = 0;
    double sum_target = 0;
    int min_in, max_in, min_out, max_out;
    origin->get_range(min_in, max_in, min_out, max_out);
    if (min_in != 0 || max_in != 255)
        return new Function();
    target->get_range(min_in, max_in, min_out, max_out);
    if (min_in != 0 || max_in != 255)
        return new Function();
    int l = 255;
    vector<double> temp_origin(l + 1);
    vector<double> temp_target(l + 1);
    Function *fun = new Function(0, 255, 0, 255);
    for (int i = 0; i <= l; ++i){
        sum_origin += static_cast<double>(origin->get(min_in + i));
        temp_origin[i] = sum_origin;
        sum_target += static_cast<double>(target->get(min_in + i));
        temp_target[i] = sum_target;
    }
    for (int i = 0; i <= l; ++i){
        temp_origin[i] = temp_origin[i] / sum_origin;
        temp_target[i] = temp_target[i] / sum_target;
    }
    for (int i = 0, j = 0; j <= l; ++j){
        for (; i <= l; ++i){
            if (temp_origin[i] <= temp_target[j]){
                fun->set(i, j);
            }else{
                break;
            }
        }
    }
    return fun;

}
