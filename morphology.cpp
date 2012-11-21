#include "morphology.h"
#include "convolutionengine.h"
using namespace cv;


void Morphology::run(Mat &src, Mat &dst, morphology_type_t type, Mat se, int center_x, int center_y){
    CV_Assert(src.channels() == 1);
    switch(type){
    case EROSION:{
        ConvolutionEngine::run(src, dst, se, erosion_action, center_x, center_y);
    }
        break;
    case DILATION:{
        ConvolutionEngine::run(src, dst, se, dilation_action, center_x, center_y);
    }
        break;
    case OPENING:{
        ConvolutionEngine::run(src, dst, se, erosion_action, center_x, center_y);
        ConvolutionEngine::run(dst, dst, se, dilation_action, center_x, center_y);
    }
        break;
    case CLOSING:{
        ConvolutionEngine::run(src, dst, se, dilation_action, center_x, center_y);
        ConvolutionEngine::run(dst, dst, se, erosion_action, center_x, center_y);
    }
        break;
    default:
        break;
    }
}

//only work with binary images
uchar Morphology::erosion_action(Mat& input, Mat& se){
    for (int i = 0; i < se.rows; ++i){
        for (int j = 0; j < se.cols; ++j){
            if (se.at<uchar>(i, j) != 0 && input.at<uchar>(i, j) == 0){
                return 0;
            }
        }
    }
    return 255;
}

uchar Morphology::dilation_action(Mat &input, Mat &se){
    for (int i = 0; i < se.rows; ++i){
        for (int j = 0; j < se.cols; ++j){
            if (se.at<uchar>(i, j) != 0 && input.at<uchar>(i, j) != 0){
                return 255;
            }
        }
    }
    return 0;
}

