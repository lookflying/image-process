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
    void restore();
    static QImage get_qimage(cv::Mat& img);
    QImage get_display_image();
    cv::Mat& get_origin();
    cv::Mat& get_image();
    QImage get_qimage_origin();
    QImage get_qimage_image();
    void set_image(cv::Mat image);

    QImage data()__attribute__ ((deprecated));
    cv::Mat& get_opencv_image_3channels()__attribute__ ((deprecated));
    cv::Mat& get_opencv_image_gray()__attribute__ ((deprecated));
    void sync_changes()__attribute__ ((deprecated));
    void turn_gray()__attribute__ ((deprecated));
    void turn_binary()__attribute__ ((deprecated));
private:
    cv::Mat origin_;
    cv::Mat image_;
    cv::Mat gray_img_ __attribute__ ((deprecated));
    bool is_gray_;
    bool is_binary_;
    bool need_sync_;
};

#endif // FIMAGE_H
