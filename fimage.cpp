#include "fimage.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QDebug>

using namespace cv;
FImage::FImage()
{
    is_gray_ = false;
}


bool FImage::load(QString file_name){
    bool ret = false;
    origin_ = imread(file_name.toStdString());
    ret = !origin_.empty();
    if (ret){
        origin_.copyTo(image_);
        is_gray_ = false;
    }
    return ret;
}

bool FImage::save(QString file_name){
    return imwrite(file_name.toStdString(), image_);
}

void FImage::restore(){
    origin_.copyTo(image_);
}

QImage FImage::data(){
    if (need_sync_)
        sync_changes();
    return get_display_image();
}
QImage FImage::get_display_image(){
    if (is_gray_){
        cvtColor(gray_img_, image_, CV_GRAY2RGB);
    }
    return QImage((uchar*)image_.data, image_.cols, image_.rows, image_.channels() * image_.cols, QImage::Format_RGB888);

}

QImage FImage::get_qimage(Mat &img){
    Mat tmp;
    if (img.channels() == 1){
        cvtColor(img, tmp, CV_GRAY2RGB);
        return QImage((uchar*)tmp.data, tmp.cols, tmp.rows, tmp.channels() * img.cols, QImage::Format_RGB888);
    }else if (img.channels() == 3){
        cvtColor(img, tmp, CV_BGR2RGB);
        return QImage((uchar*)tmp.data, tmp.cols, tmp.rows, tmp.channels() * img.cols, QImage::Format_RGB888);
    }else{
        return QImage();
    }
}

Mat& FImage::get_origin(){
    return origin_;
}

Mat& FImage::get_image(){
    return image_;
}

QImage FImage::get_qimage_image(){
    return get_qimage(image_);
}

QImage FImage::get_qimage_origin(){
    return get_qimage(origin_);
}

void FImage::set_image(Mat image){
    image.copyTo(image_);
}


Mat& FImage::get_opencv_image_3channels(){
    if (is_gray_){
        cvtColor(gray_img_, image_, CV_GRAY2RGB);
        need_sync_ = true;
    }
    return image_;
}

void FImage::turn_gray(){
    if (!is_gray_){
        cvtColor(image_, gray_img_, CV_RGB2GRAY);
        is_gray_ = true;
    }
}

Mat& FImage::get_opencv_image_gray(){
    if (!is_gray_){
        cvtColor(image_, gray_img_, CV_RGB2GRAY);
        need_sync_ = true;
    }
    return gray_img_;
}

void FImage::sync_changes(){
    if (is_gray_){
        cvtColor(image_, gray_img_, CV_RGB2GRAY);
        need_sync_ = false;
    }else{
        cvtColor(gray_img_, image_, CV_GRAY2RGB);
        need_sync_ = false;
    }
}

