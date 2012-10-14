#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include "linearfunction.h"

class ChartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChartWidget(int w, int h, QWidget *parent = 0);
    enum chart_types{LINE, HISTOGRAM};
    typedef int chart_type;
    void set_property(int width,
                      int height,
                      int x_min = 0,
                      int x_max = 255,
                      int y_min = 0,
                      int y_max = 255,
                      chart_type type = LINE);
signals:
    
public slots:
    
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    int x_max_;
    int x_min_;
    int y_max_;
    int y_min_;
    int w_ ;
    int h_;
    int range_x_;
    int range_y_;
    chart_type type_;
    LinearFunction fun;
    bool pressed_;
    bool continous_;
};

#endif // CHARTWIDGET_H
