#include "morphology.h"
#include "convolutionengine.h"
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <cmath>
#include <cstdio>
#include <limits>
#include <map>
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

static void visualize32SC1(Mat img, int threshold, Mat &dst, bool colored = false){
    CV_Assert(img.type() == CV_32SC1);
    if (colored){
        Mat color_show;
        color_show = Mat(img.rows, img.cols, CV_8UC3, Scalar(0, 0, 0));
        std::map<int, Vec3b> color_map;
        for (int i = 0; i < img.rows; ++i){
            for (int j = 0; j < img.cols; ++j){
                if (img.at<int>(i, j) > threshold && color_map.find(img.at<int>(i, j)) == color_map.end()){
                    int r = theRNG().uniform(0, 256);
                    int g = theRNG().uniform(0, 256);
                    int b = theRNG().uniform(0, 256);
                    color_map[img.at<int>(i, j)] = Vec3b(b, g, r);
                }
            }
        }
        for (int i = 0; i < img.rows; ++i){
            for (int j = 0; j < img.cols; ++j){
                if (img.at<int>(i, j) > threshold){
                    color_show.at<Vec3b>(i, j) = color_map[img.at<int>(i, j)];
                }
            }
        }
        color_show.copyTo(dst);
    }else{
        Mat gray_show;
        gray_show = Mat(img.rows, img.cols, CV_8UC1, Scalar(0));
        for (int i = 0; i < img.rows; ++i){
            for (int j = 0; j < img.cols; ++j){
                gray_show.at<uchar>(i, j) = (img.at<int>(i, j) > threshold ? 255: 0);
            }
        }
        gray_show.copyTo(dst);
    }
}

static void show32SC1(Mat img, int threshold, std::string name = "", bool colored = false){
    CV_Assert(img.type() == CV_32SC1);
    if (colored){
        Mat color_show;
        color_show = Mat(img.rows, img.cols, CV_8UC3, Scalar(0, 0, 0));
        std::map<int, Vec3b> color_map;
        for (int i = 0; i < img.rows; ++i){
            for (int j = 0; j < img.cols; ++j){
                if (img.at<int>(i, j) > threshold && color_map.find(img.at<int>(i, j)) == color_map.end()){
                    int r = theRNG().uniform(0, 256);
                    int g = theRNG().uniform(0, 256);
                    int b = theRNG().uniform(0, 256);
                    color_map[img.at<int>(i, j)] = Vec3b(b, g, r);
                }
            }
        }
        for (int i = 0; i < img.rows; ++i){
            for (int j = 0; j < img.cols; ++j){
                if (img.at<int>(i, j) > threshold){
                    color_show.at<Vec3b>(i, j) = color_map[img.at<int>(i, j)];
                }
            }
        }
        imshow("display"+name, color_show);
    }else{
        Mat gray_show;
        gray_show = Mat(img.rows, img.cols, CV_8UC1, Scalar(0));
        for (int i = 0; i < img.rows; ++i){
            for (int j = 0; j < img.cols; ++j){
                gray_show.at<uchar>(i, j) = (img.at<int>(i, j) > threshold ? 255: 0);
            }
        }
        imshow("display"+name, gray_show);
    }
}

static void dfs_mark(Mat &to_mark, int x, int y, int cc){
    CV_Assert(to_mark.type() == CV_32SC1);
    if (x >= 0 && x < to_mark.cols && y >= 0 && y < to_mark.rows){
        if (to_mark.at<int>(y, x) < 0){
            to_mark.at<int>(y, x) = cc;
            dfs_mark(to_mark, x, y -1, cc);
            dfs_mark(to_mark, x, y + 1, cc);
            dfs_mark(to_mark, x - 1, y, cc);
            dfs_mark(to_mark, x + 1, y, cc);
        }
    }
}

static void flood(Mat &img, Mat &to_mark, int water_level){
    for (int i = 0; i < img.rows; ++i){
        for (int j = 0; j < img.cols; ++j){
            if (to_mark.at<int>(i, j) == 0 && img.at<uchar>(i, j) <= static_cast<uchar>(water_level)){
                to_mark.at<int>(i, j) = -1;
            }
        }
    }
}

static void flood_mark(Mat &to_mark, int x, int y){
    CV_Assert(to_mark.type() == CV_32SC1);
    if (to_mark.at<int>(y, x) < 0){
        int count = 0;
        int cc = 0;
        for (int i = ((y - 1) >= 0 ? (y - 1): y); i <= ((y + 1) < to_mark.rows ? (y + 1): y); ++i){
            for (int j = ((x - 1) >= 0 ? (x -1): x); j <= ((x + 1) < to_mark.cols ? (x + 1): x); ++j){
                if (to_mark.at<int>(i, j) > 0 && to_mark.at<int>(i, j) != std::numeric_limits<int>::max()){
                    if (cc == 0){
                        ++count;
                        cc = to_mark.at<int>(i, j);
                    }else if (cc != to_mark.at<int>(i, j)){
                        ++count;
                    }
                }
            }

        }
        if (count == 1){
            to_mark.at<int>(y, x) = cc;
        }else if (count > 1){
            to_mark.at<int>(y, x) = std::numeric_limits<int>::max();
        }
    }

}
void Morphology::watershed_seeds(Mat src, Mat &seeds, Mat se, int min_value){
    CV_Assert(se.channels() == 1);
    seeds = Mat(src.rows, src.cols, CV_8UC1, Scalar(0));
    int min_min = 255;
    for (int i = 0; i < src.rows; ++i){
        for (int j = 0; j < src.cols; ++j){
            min_min = std::min(min_min, static_cast<int>(src.at<uchar>(i, j)));
        }
    }
    if (min_value < min_min){
        min_value = min_min;
    }

    for (int i = 0; i < src.rows; ++i){
        for (int j = 0; j < src.cols; ++j){
            if (static_cast<int>(src.at<uchar>(i, j)) <= min_value){
                seeds.at<uchar>(i, j) = 255;
            }
        }
    }
//    ConvolutionEngine::run(seeds, seeds, se, dilation_action_binary, -1, -1);
//    ConvolutionEngine::run(seeds, seeds, se, erosion_action_binary, -1, -1);

}

static void generate_segment_rst(Mat src, Mat seg, Mat &rst){
    CV_Assert(src.channels() == 1 && src.type() == CV_8UC1 && src.size == seg.size);
    Mat src_color;
    cvtColor(src, src_color, CV_GRAY2BGR);
    addWeighted(src_color, 0.5, seg, 0.5, 0.0, rst);
}

void Morphology::watershed_segment(Mat src, Mat seeds, Mat &marked, Mat &result, int init_level){
    CV_Assert(src.channels() == 1 && seeds.channels() == 1 && src.type() == CV_8UC1 && seeds.type() == CV_8UC1);
    marked = Mat(src.rows, src.cols, CV_32SC1, Scalar(0));
    result = Mat(src.rows, src.cols, CV_8UC1, Scalar(0));


    for (int i = 0; i < marked.rows; ++i){
        for (int j = 0; j < marked.cols; ++j){
            if (seeds.at<uchar>(i, j) > 0){
                marked.at<int>(i, j) = -1;
            }
        }
    }

    //find connected components
    int last_cc = 0;
    for (int i = 0; i < marked.rows; ++i){
        for (int j = 0; j < marked.cols; ++j){
            dfs_mark(marked, j, i, ++last_cc);
        }
    }

    int level = init_level;
    while(level <= 255){
        flood(src, marked, level);
        ++level;
        for (int i = 0; i < marked.rows; ++i){
            for (int j = 0; j < marked.cols; ++j){
                flood_mark(marked, j, i);
            }
        }
    }

    for (int i = 0; i < marked.rows; ++i){
        for (int j = 0; j < marked.cols; ++j){
            if (marked.at<int>(i, j) == std::numeric_limits<int>::max()){
                result.at<uchar>(i, j) = 255;
            }
        }
    }


}





void Morphology::run(Mat &src, Mat &dst, morphology_type_t type, Mat se, cv::Mat mask, int center_x, int center_y){
    CV_Assert(src.channels() == 1);
    if (mask.size != src.size){
        mask = Mat();
    }
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
        }
        dst = rst;

    }
        break;
    case CONDITIONAL_DILATION:{
        Mat rst = Mat(src.rows, src.cols, src.type());
        do{
            Mat temp;
            ConvolutionEngine::run(src, temp, se, mask, dilation_action_binary, center_x, center_y);
            if (sum(rst - temp)[0] == 0){
                break;
            }
            temp.copyTo(rst);
        }while(true);
        dst = rst;
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
    case EDGE_STANDARD:{
        Mat dilated, erosioned;
        ConvolutionEngine::run(src, dilated, se, dilation_action_grayscale, center_x, center_y);
        ConvolutionEngine::run(src, erosioned, se, erosion_action_grayscale, center_x, center_y);
        dst = dilated - erosioned;
    }
        break;
    case EDGE_EXTERNAL:{
        Mat dilated;
        ConvolutionEngine::run(src, dilated, se, dilation_action_grayscale, center_x, center_y);
        dst = dilated - src;
    }
        break;
    case EDGE_INTERNAL:{
        Mat erosioned;
        ConvolutionEngine::run(src, erosioned, se, erosion_action_grayscale, center_x, center_y);
        dst = src - erosioned;
    }
        break;
    case GRAYSCALE_RECONSTRUCTION:{
        Mat rst = Mat(src.rows, src.cols, src.type());
        do{
            Mat temp;
            ConvolutionEngine::run(src, temp, se, mask, dilation_action_grayscale, center_x, center_y);
            if (sum(rst - temp)[0] == 0){
                break;
            }
            temp.copyTo(rst);
        }while(true);
        dst = rst;
    }
        break;
    case GRADIENT:{
        Mat dilated, erosioned;
        ConvolutionEngine::run(src, dilated, se, dilation_action_grayscale, center_x, center_y);
        ConvolutionEngine::run(src, erosioned, se, erosion_action_grayscale, center_x, center_y);
        dst = (dilated - erosioned) / 2;
    }
        break;
    case GRADIENT_EXTERNAL:{
        Mat dilated;
        ConvolutionEngine::run(src, dilated, se, dilation_action_grayscale, center_x, center_y);
        dst = (dilated - src) / 2;
    }
        break;
    case GRADIENT_INTERNAL:{
        Mat erosioned;
        ConvolutionEngine::run(src, erosioned, se, erosion_action_grayscale, center_x, center_y);
        dst = (src - erosioned) / 2;
    }
        break;
    case WATERSHED:{
        Mat marked, seg, rst, marked_v;
        watershed_segment(src, mask, marked, seg);
        visualize32SC1(marked, 0, marked_v, true);
        generate_segment_rst(src, marked_v, rst);

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

