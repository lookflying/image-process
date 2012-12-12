#include "morphology.h"
#include "convolutionengine.h"
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cmath>
#include <cstdio>
using namespace cv;

const uchar Morphology::distance_metric_[] = {
    255, 255, 255,
    255, 255, 255,
    255, 255, 255,
};
void Morphology::cut_black_edge(Mat in, Mat &out){
    CV_Assert(in.channels() == 1);
    int x = 0, y = 0, w = 0, h = 0;

    for (int i = 0; i < in.rows; ++i){
        for (int j = 0; j < in.cols; ++j){
            if (in.at<unsigned char>(i, j) > 0){
                y = i;
                goto from_bottom;
            }
        }
    }
from_bottom:
    for (int i = in.rows - 1; i > y; --i){
        for (int j = 0; j < in.cols; ++j){
            if (in.at<unsigned char>(i, j) > 0){
                h = i - y + 1;
                goto from_left;
            }
        }
    }
from_left:
    for (int j = 0; j < in.cols; ++j){
        for (int i = y; i < y + h; ++i){
            if (in.at<unsigned char>(i, j) > 0){
                x = j;
                goto from_right;
            }
        }
    }
from_right:
    for (int j = in.cols - 1; j > x; --j){
        for (int i = y; i < y + h; ++i){
            if (in.at<unsigned char>(i, j) > 0){
                w = j - x + 1;
                goto end;
            }
        }
    }
end:
    in(Rect(x, y, w, h)).copyTo(out);

}

Mat Morphology::generate_structing_element(int width, int height, structing_element_type_t type){
    if(width <= 0 || height <= 0){
        width = 3;
        height = 3;
    }
    Mat se = Mat(height, width, CV_8UC1);
    switch(type){
    case DISC:
    {
        int radius_x = width / 2, radius_y = height / 2;
        int aa = radius_x * radius_x;
        int bb = radius_y * radius_y;
        int aabb = aa * bb;
        for(int i = 0; i <= radius_y; ++i){
            for(int j = 0; j <= radius_x; j++){
               int xx = (radius_x - j) * (radius_x - j) * bb;
               int yy = (radius_y - i) * (radius_y - i) * aa;
               unsigned char value;
               if(xx + yy <= aabb){
                   value = 255;
               }else{
                   value = 0;
               }
               se.at<unsigned char>(i, j) = value;
               se.at<unsigned char>(height - 1 - i, j) = value;
               se.at<unsigned char>(i, width - 1 - j) = value;
               se.at<unsigned char>(height - 1 -i, width - 1 - j) = value;
            }
        }
    }
        break;
    case CUBE:
    {
        for(int i = 0; i < height; ++i){
            for(int j = 0; j < width; ++j){
                se.at<unsigned char>(i, j) = 255;
            }
        }
    }
        break;
    case CROSS:
    {
        int radius_x = width / 2, radius_y = height / 2;
        for(int i = 0; i <= radius_y; ++i){
            for(int j = 0; j <= radius_x; ++j){
                unsigned char value;
                if(i <= radius_y / 2 && j <= radius_x / 2){
                    value = 0;
                }else{
                    value = 255;
                }
                se.at<unsigned char>(i, j) = value;
                se.at<unsigned char>(height - 1 - i, j) = value;
                se.at<unsigned char>(i, width - 1 - j) = value;
                se.at<unsigned char>(height - 1 -i, width - 1 - j) = value;
            }
        }
    }
        break;
    default:
        break;
    }
    return se;

}

void Morphology::run(Mat &src, Mat &dst, morphology_type_t type, Mat se, int center_x, int center_y){
    CV_Assert(src.channels() == 1);
    switch(type){
    case EROSION_BINARY:{
        ConvolutionEngine::run(src, dst, se, erosion_action_binary, center_x, center_y);
    }
        break;
    case DILATION_BINARY:{
        ConvolutionEngine::run(src, dst, se, dilation_action_binary, center_x, center_y);
    }
        break;
    case OPENING_BINARY:{
        ConvolutionEngine::run(src, dst, se, erosion_action_binary, center_x, center_y);
        ConvolutionEngine::run(dst, dst, se, dilation_action_binary, center_x, center_y);
    }
        break;
    case CLOSING_BINARY:{
        ConvolutionEngine::run(src, dst, se, dilation_action_binary, center_x, center_y);
        ConvolutionEngine::run(dst, dst, se, erosion_action_binary, center_x, center_y);
    }
        break;
    case EROSION_GRAYSCALE:{
        ConvolutionEngine::run(src, dst, se, erosion_action_grayscale, center_x, center_y);
    }
        break;
    case DILATION_GRAYSCALE:{
        ConvolutionEngine::run(src, dst, se, dilation_action_grayscale, center_x, center_y);
    }
        break;
    case OPENING_GRAYSCALE:{
        ConvolutionEngine::run(src, dst, se, erosion_action_grayscale, center_x, center_y);
        ConvolutionEngine::run(src, dst, se, dilation_action_grayscale, center_x, center_y);
    }
        break;
    case CLOSING_GRAYSCALE:{
        ConvolutionEngine::run(src, dst, se, dilation_action_grayscale, center_x, center_y);
        ConvolutionEngine::run(src, dst, se, erosion_action_grayscale, center_x, center_y);
    }
        break;
    case DISTANCE_TRANSFORM:
    {
        Mat temp = Mat(src.rows, src.cols, CV_32FC1, Scalar(0)),marked = src.clone();
        int distance = 0;
        while(sum(marked)[0] != 0){
            ++distance;
            ConvolutionEngine::run(marked, marked, se, erosion_action_binary, center_x, center_y);
            temp.setTo(static_cast<float>(distance), marked);
        }
        Convolution::to_normalized_uchar_mat(temp, dst, static_cast<float>(distance));
    }
        break;
    case SKELETONIZATION:{
        Mat rst = Mat(src.rows, src.cols, CV_8UC1, Scalar(0));
        Mat nse = se.clone();
        while(true){
            Mat erosioned;
            Mat opened;
            ConvolutionEngine::run(src, erosioned, nse, erosion_action_binary, center_x, center_y);
            if (sum(erosioned)[0] == 0){
                break;
            }
            ConvolutionEngine::run(erosioned, opened, se, erosion_action_binary, center_x, center_y);
            ConvolutionEngine::run(opened, opened, se, dilation_action_binary, center_x, center_y );

            copyMakeBorder(nse, nse, 2, 2, 2, 2, BORDER_CONSTANT,  Scalar(0));
            ConvolutionEngine::run(nse, nse, se, dilation_action_binary, -1, -1);
            cut_black_edge(nse, nse);
            Mat mask = Mat(src.rows, src.cols, CV_8UC1, Scalar(255));
            mask.setTo(0, opened);
            Mat delta = erosioned & mask;
            rst |= delta;
//            imshow("erosioned", erosioned);
//            imshow("opened", opened);
//            imshow("delta", delta);
//            imshow("rst", rst);
//            imshow("se", se);
//            waitKey(1);
        }
        dst = rst;

    }
        break;
    default:
        break;
    }
}

//only work with binary images
uchar Morphology::erosion_action_binary(Mat& input, Mat& se){
    for (int i = 0; i < se.rows; ++i){
        for (int j = 0; j < se.cols; ++j){
            if (se.at<uchar>(i, j) != 0 && input.at<uchar>(i, j) == 0){
                return 0;
            }
        }
    }
    return 255;
}

uchar Morphology::dilation_action_binary(Mat &input, Mat &se){
    for (int i = 0; i < se.rows; ++i){
        for (int j = 0; j < se.cols; ++j){
            if (se.at<uchar>(i, j) != 0 && input.at<uchar>(i, j) != 0){
                return 255;
            }
        }
    }
    return 0;
}

//grayscale erosion
uchar Morphology::erosion_action_grayscale(Mat &input, Mat &se){
    int min_value = 255;
    for (int i = 0; i < se.rows; ++i){
        for (int j = 0; j < se.cols; ++j){
            min_value = std::min(static_cast<int>(input.at<uchar>(i, j)) - static_cast<int>(se.at<uchar>(i, j)), min_value);
        }
    }
    if (min_value < 0){
        return 0;
    }else{
        return static_cast<uchar>(min_value);
    }
}

//grayscalce dilation
uchar Morphology::dilation_action_grayscale(Mat &input, Mat &se){
    int max_value = 0;
    for (int i = 0; i < se.rows; ++i){
        for (int j = 0; j < se.cols; ++j){
            max_value = std::max(static_cast<int>(se.at<uchar>(i, j)) + static_cast<int>(input.at<uchar>(i, j)), max_value);
        }
    }
    if (max_value > 255){
        return 255;
    }else{
        return static_cast<uchar>(max_value);
    }
}
