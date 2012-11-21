#include "convolution.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;

uchar Convolution::normal_convolution_action(Mat& input, Mat& kernel){
    return double_to_valid_uchar(element_mul_sum(input, kernel));
}

double Convolution::normal_raw_convolution_action(Mat& input, Mat& kernel){
    return element_mul_sum(input, kernel);
}


uchar Convolution::morphology_action(Mat& input, Mat& kernel){

}

void Convolution::to_float_mat(Mat &in, Mat& out){
    if (in.elemSize() == 1){
        Mat tmp_out = Mat(in.rows, in.cols, CV_32FC1);
        for (int i = 0; i < in.rows; ++i){
            for (int j = 0; j < in.cols; ++j){
                tmp_out.at<float>(i, j) = static_cast<float>(in.at<uchar>(i, j));
            }
        }
        out = tmp_out;
    }else{
        out = in;
    }
}

double Convolution::element_mul_sum(Mat& a, Mat& b){
    double rst = 0;
    CV_Assert(a.channels() == 1 && b.channels() == 1);

    Mat fa, fb;
    to_float_mat(a, fa);
    to_float_mat(b, fb);
    for (int i = 0; i < fa.rows; ++i){
        for (int j = 0; j < fa.cols; ++j){
            rst += fa.at<float>(i, j) * fb.at<float>(i, j);
        }
    }
    return rst;
}

uchar Convolution::double_to_valid_uchar(double d){
    if (d > 255){
        d =255.0;
    }
    else if(d < 0){
        d = 0.0;
    }
    return static_cast<uchar>(d);
}

//Scalar ConvolutionEngine::element_mul_sum(Mat a, Mat b){
//    Mat c;
//    multiply(a, b, c, 1, CV_MAKE_TYPE(CV_32F, CV_MAT_DEPTH(a.type())));
//    int channels = a.elemSize()/sizeof(uchar);
//    Scalar rst(0, 0, 0, 0);
//    if (channels == 1){
//        for (int i = 0; i < c.rows; ++i){
//            for (int j = 0; j < c.cols; ++j){
//                rst[0] += c.at<uchar>(i, j);
//            }
//        }
//    }
//    for (int i = 0; i < c.rows; ++i){
//        for (int j = 0; j < c.cols; ++j){
//            for (int ch = 0; ch < channels; ++ch){
//                rst[ch] += c.at<Vec3b>(i, j)[ch];
//            }
//        }
//    }
//    return rst;
