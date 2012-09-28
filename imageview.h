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
    void openImage(QString file);
    void saveImage();
    void saveImageAs(QString file);
public:
    void showImage(QImage img);

private:

    QGraphicsScene* m_scene;
    QMutex m_mutex;
    QString m_file;
    QImage m_img;




};

#endif // IMAGEVIEW_H
