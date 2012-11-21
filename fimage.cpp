#include "fimage.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QDebug>

using namespace cv;
FImage::FImage()
{
    using_gray_ = false;
}

void FImage::use_gray(){
    cvtColor(img_, gray_img_, CV_RGB2GRAY);
    using_gray_ = true;
}

bool FImage::load(QString file_name){
    bool ret;
    img_ = imread(file_name.toStdString());
    using_gray_ = false;

//    Mat test = Mat::zeros(3, 4, CV_32FC1);
//    qDebug()<<QString("test.element size = %1, length of float %2, length of double %3").arg(test.elemSize()).arg(sizeof(float)).arg(sizeof(double));
    ret = !img_.empty();
    if (ret){
        cvtColor(img_, img_, CV_BGR2RGB);
    }
    return ret;
}

bool FImage::save(QString file_name){
    return imwrite(file_name.toStdString(), img_);
}


QImage FImage::data(){
    if (using_gray_){
        return get_qimage(gray_img_);
    }else{
        return get_qimage(img_);
    }
}

QImage FImage::get_qimage(Mat &img){
    if (img.channels() == 1){
        Mat tmp;
        cvtColor(img, tmp, CV_GRAY2RGB);
        return QImage((uchar*)tmp.data, tmp.cols, tmp.rows, tmp.channels() * img.cols, QImage::Format_RGB888);
    }else if (img.channels() == 3){
         return QImage((uchar*)img.data, img.cols, img.rows, img.channels() * img.cols, QImage::Format_RGB888);
    }else{
        return QImage();
    }
}

Mat& FImage::get_opencv_image_3channels(){
    if (using_gray_){
        cvtColor(gray_img_, img_, CV_GRAY2RGB);
        need_sync_ = true;
    }
    return img_;
}

Mat& FImage::get_opencv_image_gray(){
    if (!using_gray_){
        cvtColor(img_, gray_img_, CV_RGB2GRAY);
        need_sync_ = true;
    }
    return gray_img_;
}

void FImage::sync_changes(){
    if (using_gray_){
        cvtColor(img_, gray_img_, CV_RGB2GRAY);
        need_sync_ = false;
    }else{
        cvtColor(gray_img_, img_, CV_GRAY2RGB);
        need_sync_ = false;
    }
}

