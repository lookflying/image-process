#include "imageview.h"


#include <QDebug>
#include <QImageReader>


ImageView::ImageView(QWidget *parent) :
    QGraphicsView(parent)
{
    scene_ = new QGraphicsScene(this);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

}


bool ImageView::openImage(QString file_name){
    file_ = file_name;
    bool rst = image_data_.load(file_name);
    if (rst){
        show_image(image_data_.data());
    }
    return rst;
}

void ImageView::save_image(){
    image_data_.save(file_);
}

void ImageView::save_image_as(QString file_name){
    image_data_.save(file_name);
}

void ImageView::show_image(QImage img){
    mutex_.lock();
    scene_->clear();
    scene_->addPixmap(QPixmap::fromImage(img));
    setScene(scene_);
    repaint();
    mutex_.unlock();
}

void ImageView::refresh(){
     show_image(image_data_.data());
}

