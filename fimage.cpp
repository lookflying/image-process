#include "fimage.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
FImage::FImage()
{
}

bool FImage::load(QString file_name){
    bool ret;
    img_ = imread(file_name.toStdString());
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
    return get_qimage(img_);
}

QImage FImage::get_qimage(Mat &img){
    if (img.channels() == 3){
         return QImage((uchar*)img.data, img.cols, img.rows, img.channels() * img.cols, QImage::Format_RGB888);
    }else{
        return QImage((uchar*)img.data, img.cols, img.rows, img.channels() * img.cols, QImage::Format_Mono);
    }
    return QImage();
}

Mat& FImage::get_opencv_image(){
    return img_;
}
