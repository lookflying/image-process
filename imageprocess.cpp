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

Vec3b ImageProcess::add(Vec3b v1, Vec3b v2){
    int a[3];
    Vec3b v;
    for (int i = 0; i < 3; i++){
        a[i] = static_cast<int>(v1[i]) + static_cast<int>(v2[i]);
        if (a[i] > 255)
            a[i] = 255;
        v[i] = static_cast<uchar>(a[i]);
    }
    return v;
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



void ImageProcess::geometry_zoom(FImage &in_out, int percentage, zoom_type type){
    Mat *img = &in_out.get_opencv_image();
    if (img->empty())
        return;
    if (percentage == 100 || percentage == 0)
        return;
    int width = img->cols * percentage / 100;
    int height = img->rows * percentage / 100;
    int ori_h = img->rows;
    int ori_w = img->cols;
    Mat new_img = Mat(height, width, CV_8UC3);
    for (int i = 0; i < height; ++i){
        for (int j = 0; j < width; j++){
            switch (type){
            case Nearest:
                new_img.at<Vec3b>(j, i) = img->at<Vec3b>(j * 100 / percentage, i * 100 / percentage);
                break;
            case BILINEAR:
            {
                int py = j * 100 / percentage;
                int px = i * 100 / percentage;
                int py1 = py >= ori_h? py: py + 1;
                int px1 = px >= ori_w? px: px + 1;
                double y = static_cast<double>(j) * 100.0 / static_cast<double>(percentage) - static_cast<double>(py);
                double x = static_cast<double>(i) * 100.0 / static_cast<double>(percentage) - static_cast<double>(px);
                double xy = x * y;
                double coe00, coe01, coe10, coe11;
                coe00 = 1.0 - x - y + xy;
                coe01 = y - xy;
                coe10 = x - xy;
                coe11 = xy;
                Vec3b v00, v01, v10, v11;
                for (int k = 0; k < 3; ++k){
                    v00[k] = static_cast<uchar>(static_cast<double>(img->at<Vec3b>(py, px)[k]) * coe00);
                    v01[k] = static_cast<uchar>(static_cast<double>(img->at<Vec3b>(py1, px)[k]) * coe01);
                    v10[k] = static_cast<uchar>(static_cast<double>(img->at<Vec3b>(py, px1)[k]) * coe10);
                    v11[k] = static_cast<uchar>(static_cast<double>(img->at<Vec3b>(py1, px1)[k]) * coe11);
                }
                new_img.at<Vec3b>(j, i) = add(
                            add(v00,
                                v01),
                            add(v10,
                                v11));
            }
                break;
            case BICUBIC:
                break;
            default:
                return;
            }
        }
    }
    img->release();
    new_img.copyTo(in_out.get_opencv_image());
}
