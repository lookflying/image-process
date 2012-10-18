#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMutex>
#include <QMouseEvent>
#include "fimage.h"


class ImageView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit ImageView(QWidget *parent = 0);
    
signals:
    void mouse_position(int x, int y);
public slots:
    bool openImage(QString fileName);
    void save_image();
    void save_image_as(QString fileName);
    void refresh();
public:
    void show_image(QImage img);
    FImage image_data_;
protected:
//    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
//    void mouseReleaseEvent(QMouseEvent *event);
private:

    QGraphicsScene *scene_;
    QMutex mutex_;
    QString file_;




};

#endif // IMAGEVIEW_H
