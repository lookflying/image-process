#include "miscellaneous.h"
#include "convolutionengine.h"
#include "edgedetect.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cmath>
#include <cstdio>
#include <map>
using namespace cv;
using namespace std;
vector<double> Miscellaneous::histogram(Mat src, histogram_type_t type){
    CV_Assert(src.channels() == 1 && src.elemSize() == 1);
    vector<double> hist = vector<double>(256);
    memset(&hist[0], 0, hist.size() * sizeof(unsigned char));
    for (int i = 0; i < src.rows; ++i){
        for (int j = 0; j < src.cols; ++j){
            hist[src.at<unsigned char>(i, j)]++;
        }
    }
    if (type == PROBABILITY){
        for(unsigned int i = 0; i < hist.size(); ++i){
            hist[i] /= (src.cols * src.rows);
        }
    }
    return hist;
}

void Miscellaneous::threshold(Mat src, Mat &dst, int th, threshold_type_t type, int optional_threshold){
    CV_Assert(src.channels() == 1 && src.elemSize() == sizeof(unsigned char));

    dst = Mat(src.rows, src.cols, CV_8UC1);
    switch(type){
    case NORMAL_THRESHOLD:
    {
        Mat se(1, 2, CV_8UC1);
        se.at<unsigned char>(0, 0) = static_cast<unsigned char>(th);
        se.at<unsigned char>(0, 1) = 255;
        ConvolutionEngine::run(src, dst, se, threshold_action);
    }
        break;
    case DUAL_THRESHOLD:
    {
        Mat se(1, 2, CV_8UC1);
        se.at<unsigned char>(0, 0) = static_cast<unsigned char>(std::min(th, optional_threshold));
        se.at<unsigned char>(0, 1) = static_cast<unsigned char>(std::max(th, optional_threshold));
        ConvolutionEngine::run(src, dst, se, threshold_action);
    }
        break;
    default:
        break;
    }
}

/*
  every row in kernel represent a range that should be turned into maxval(255), otherwise 0
  example:
  kernel = { 100, 150;
             45, 70;}
  then if( (src(x, y) =< 150 && src(x, y) > 100) || (src(x, y) =< 70 && src(x, y) > 45))
            dst(x, y) = 255
        else
            dst(x, y) = 0
  */
unsigned char Miscellaneous::threshold_action(Mat &input, Mat &kernel){
    CV_Assert(kernel.cols == 2);
    unsigned char in_value = input.at<unsigned char>(0, 0);
    unsigned char out_value = 0;
    for(int i = 0; i < kernel.rows; ++i){
        if (in_value > kernel.at<unsigned char>(0, 0)
                && in_value <= kernel.at<unsigned char>(0, 1)){
            out_value = 255;
        }
    }
    return out_value;
}

unsigned char Miscellaneous::auto_threshold(Mat &src, Mat &dst, auto_threshold_type_t type, vector<double> parameters){
    CV_Assert(src.channels() == 1);
    Mat rst;
    int th;
    switch(type){
    case ISODATA:
    {
        CV_Assert(parameters.size() > 0);
        double percentage = parameters[0];
        th = parameters.size() > 1 ? static_cast<int>(parameters[1]) : static_cast<int>(255 * percentage);
        int target_count = static_cast<int>(src.rows * src.cols * percentage);
        Mat temp;
        int low = 0, high = 255;
        while(high - low > 1){
            threshold(src, temp, th);
            int count = 0;
            for(int i = 0; i < src.rows; ++i){
                for(int j = 0; j < src.cols; ++j){
                    if(temp.at<unsigned char>(i, j) == 0){
                        ++count;
                    }
                }
            }
            if (count == target_count){
                break;
            }else if (count > target_count){
                high = th;
                th = (low + high) / 2;
            }else{
                low = th;
                th = (low + high) / 2;
            }
        }
        rst = temp;
    }
        break;
    case OTSU:
    {
        vector<double> hist = histogram(src, PROBABILITY);
        vector<double> px(256);
        vector<double> w(256);
        vector<double> u(256);
        map<double, unsigned int> thetas;
        for (unsigned int i = 0; i < px.size(); ++i){
            px[i] = hist[i] * i;
        }
        w[0] = hist[0];
        u[0] = px[0];
        for (unsigned int i = 1; i < w.size(); ++i){
            w[i] = w[i - 1] + hist[i];
            u[i] = u[i - 1] + px[i];
        }
        for (unsigned int i = 0; i < w.size(); ++i){
            double theta;
            if (w[i] != 0 && 1 - w[i] != 0){
                theta = w[i] * (1 - w[i])
                        * (u[i] / w[i] - (u[255] - u[i]) / (1 - w[i]))
                        * (u[i] / w[i] - (u[255] - u[i]) / (1 - w[i]));
            }else{
                theta = 0;
            }
            thetas[theta] = i;
        }
        map<double, unsigned int>::reverse_iterator rit = thetas.rbegin();
        th = static_cast<int>(rit->second);
//        th += static_cast<int>((++rit)->second);
//        th /= 2;
    }
        break;
    case ENTROPY:
    {
         vector<double> hist = histogram(src, PROBABILITY);
         vector<double> w(256);
         vector<double> Hb(256);
         vector<double> Hw(256);
         map<double, unsigned int> entropies;
         w[0] = hist[0];
         for (unsigned int i = 1; i < w.size(); ++i){
             w[i] = w[i - 1] + hist[i];
         }
         for (unsigned int i = 0; i < Hb.size(); ++i){
             Hb[i] = 0;
             if (w[i] != 0){
                 for (int j = 0; j <= i; ++j){
                     if (hist[j] != 0){
                         Hb[i] += - hist[j] / w[i] * std::log(hist[j] / w[i]);
                     }
                 }
             }
             Hw[i] = 0;
             if (1 - w[i] != 0){
                 for (int j = 255; j > i; --j){
                     if (hist[j] != 0){
                         Hw[i] += - hist[j] / (1 - w[i]) * std::log(hist[j] / (1 - w[i]));
                     }
                 }
             }
         }
         for (unsigned int i = 0; i < Hb.size(); ++i){
             double entropy = Hb[i] + Hw[i];
             entropies[entropy] = i;
         }
         map<double, unsigned int>::reverse_iterator rit = entropies.rbegin();
         th = static_cast<int>(rit->second);

    }
        break;
    case SOBEL_AREA:
    {
        Mat mask, temp;
        EdgeDetect::run(src, mask, EdgeDetect::SOBEL);


        imshow("edge", mask);


        unsigned char max = 0, min = 255;
        for (int i = 0; i < mask.rows; ++i){
            for (int j = 0; j < mask.cols; ++j){
                if (mask.at<unsigned char>(i, j) > max){
                    max = mask.at<unsigned char>(i, j);
                }
                if (mask.at<unsigned char>(i, j) < min){
                    min = mask.at<unsigned char>(i, j);
                }
            }
        }
        int edge_th = (static_cast<int>(max) + static_cast<int>(min)) / 2;
        threshold(mask, mask, edge_th);


        imshow("thresholded edge", mask);


        Mat se(3, 3, CV_32FC1, Scalar(1.0 / 9));
        ConvolutionEngine::run(src, temp, se, mask,  Convolution::normal_convolution_action);

        imshow("temp", temp);


        th = 0;
        int count = 0;
        for (int i = 0; i < temp.rows; ++i){
            for (int j = 0; j < temp.cols; ++j){
                if (temp.at<unsigned char>(i, j) > 0){
                    th += static_cast<int>(temp.at<unsigned char>(i, j));
                    count ++;
                }
            }
        }
        th /= count;
    }
        break;
    default:
        break;
    }
    dst = rst;
    return static_cast<unsigned char>(th);
}

void Miscellaneous::turn_gray(Mat &src, Mat &dst){
    CV_Assert(src.channels() == 3 && src.elemSize() == 3);
    cvtColor(src, dst, CV_RGB2GRAY);
}
