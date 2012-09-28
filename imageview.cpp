#include "imageview.h"


#include <QDebug>


ImageView::ImageView(QWidget *parent) :
    QGraphicsView(parent)
{
    m_scene = new QGraphicsScene(this);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

}


void ImageView::openImage(QString file){
    this->m_file = file;
    bool rst = this->m_img.load(this->m_file);
    showImage(m_img);
}

void ImageView::saveImage(){

}

void ImageView::saveImageAs(QString file){

}

void ImageView::showImage(QImage img){
    this->m_mutex.lock();
    m_scene->clear();
    m_scene->addPixmap(QPixmap::fromImage(img));
    this->setScene(m_scene);
    this->m_mutex.unlock();
}


