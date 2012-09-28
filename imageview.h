#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMutex>



class ImageView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit ImageView(QWidget *parent = 0);
    
signals:
    
public slots:
    bool openImage(QString fileName);
    void saveImage();
    void saveImageAs(QString fileName);
public:
    void showImage(QImage *img);

private:

    QGraphicsScene *scene;
    QMutex mutex;
    QString file;
    QImage *image;




};

#endif // IMAGEVIEW_H
