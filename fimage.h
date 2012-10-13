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
private:
    cv::Mat img_;
};

#endif // FIMAGE_H