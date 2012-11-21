#include "convolution.h"
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

uchar Convolution::normal_convolution_action(Mat input, Mat kernel){
    return element_mul_sum(input, kernel);
}

uchar Convolution::morphology_action(Mat input, Mat kernel){

}

uchar Convolution::element_mul_sum(Mat a, Mat b){
    Mat c;
    double rst = 0;
    CV_Assert(a.channels() == 1 && b.channels() == 1);
    multiply(a, b, c, 1, CV_32FC1);
    for (int i = 0; i < c.rows; ++i){
        for (int j = 0; j < c.cols; ++j){
            rst += c.at<float>(i, j);
        }
    }
    double_to_valid_uchar(rst);
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
