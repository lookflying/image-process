#ifndef FIMAGE_H
#define FIMAGE_H

#include <opencv2/core/core.hpp>
#include <QImage>
class FImage
{
public:
    FImage();
    bool load(QString file_name);
    bool save(QString file_name);
    QImage data();
    static QImage get_qimage(cv::Mat& img);
    cv::Mat& get_opencv_image_3channels();
    cv::Mat& get_opencv_image_gray();
    void sync_changes();
    void use_gray();
private:
    cv::Mat img_;
    cv::Mat gray_img_;
    bool using_gray_;
    bool need_sync_;
};

#endif // FIMAGE_H
