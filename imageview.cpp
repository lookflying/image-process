#include "imageview.h"


#include <QDebug>
#include <QImageReader>


ImageView::ImageView(QWidget *parent) :
    QGraphicsView(parent)
{
    scene = new QGraphicsScene(this);
    image = new QImage();
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

}


bool ImageView::openImage(QString fileName){
    qDebug()<<fileName;
    qDebug()<<QImageReader::supportedImageFormats();
    this->file = file;
    this->image = new QImage();
    bool rst = this->image->load(this->file, "BMP");
    qDebug()<<rst<<" "<< fileName.right(fileName.length() - fileName.lastIndexOf("."))<<" "<<fileName.length()<<" "<<fileName.lastIndexOf(".");
    if (rst){
        showImage(image);
    }
    return rst;
}

void ImageView::saveImage(){

}

void ImageView::saveImageAs(QString fileName){

}

void ImageView::showImage(QImage *img){
    this->mutex.lock();
    scene->clear();
    scene->addPixmap(QPixmap::fromImage(*img));
    this->setScene(scene);
    this->repaint();
    this->mutex.unlock();
}


