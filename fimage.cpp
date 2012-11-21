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
    bool ret;
    img_ = imread(file_name.toStdString());
    is_gray_ = false;

//   Mat test = Mat::zeros(3, 4, CV_8UC1);
//   test.at<uchar>(2, 2) = 255;

//   for (int i = 0; i < 3; ++i){
//       for (int j = 0; j < 4; ++j){
//           printf("%d\t", (int)(*(test.data + i * 4 + j)));
//       }
//       printf("\n");
//   }
//   printf("----------------\n");
//   const uchar a[] = {
//       0, 0, 0, 0,
//       0, 1, 1, 3,
//       3, 4, 6, 35,
//   };
//   test = Mat(3, 4, CV_8UC1, (uchar*)a);

//   for (int i = 0; i < 3; ++i){
//       for (int j = 0; j < 4; ++j){
//           printf("%d\t", (int)(*(test.data + i * 4 + j)));
//       }
//       printf("\n");
//   }
//   fflush(stdout);
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
    if (need_sync_)
        sync_changes();
    return get_display_image();
}
QImage FImage::get_display_image(){
    if (is_gray_){
        cvtColor(gray_img_, img_, CV_GRAY2RGB);
    }
    return QImage((uchar*)img_.data, img_.cols, img_.rows, img_.channels() * img_.cols, QImage::Format_RGB888);

}

QImage FImage::get_qimage(Mat &img){
    if (img.channels() == 1){
        static Mat tmp;
        cvtColor(img, tmp, CV_GRAY2RGB);
        return QImage((uchar*)tmp.data, tmp.cols, tmp.rows, tmp.channels() * img.cols, QImage::Format_RGB888);
    }else if (img.channels() == 3){
         return QImage((uchar*)img.data, img.cols, img.rows, img.channels() * img.cols, QImage::Format_RGB888);
    }else{
        return QImage();
    }
}

Mat& FImage::get_opencv_image_3channels(){
    if (is_gray_){
        cvtColor(gray_img_, img_, CV_GRAY2RGB);
        need_sync_ = true;
    }
    return img_;
}

void FImage::turn_gray(){
    if (!is_gray_){
        cvtColor(img_, gray_img_, CV_RGB2GRAY);
        is_gray_ = true;
    }
}

Mat& FImage::get_opencv_image_gray(){
    if (!is_gray_){
        cvtColor(img_, gray_img_, CV_RGB2GRAY);
        need_sync_ = true;
    }
    return gray_img_;
}

void FImage::sync_changes(){
    if (is_gray_){
        cvtColor(img_, gray_img_, CV_RGB2GRAY);
        need_sync_ = false;
    }else{
        cvtColor(gray_img_, img_, CV_GRAY2RGB);
        need_sync_ = false;
    }
}

