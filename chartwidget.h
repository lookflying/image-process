#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include "function.h"
class ChartWidget : public QWidget
{
    Q_OBJECT
public:
    typedef int chart_type;
    typedef int fun_type;
    enum chart_types{LINE, HISTOGRAM};
    enum fun_types{TABLE, LINEAR, LOG, EXPONENT};
    explicit ChartWidget(QWidget *parent = 0);
    void set_property(int x_min = 0,
                      int x_max = 255,
                      int y_min = 0,
                      int y_max = 255,
                      fun_type ft = TABLE,
                      chart_type ct = LINE);

    Function *fun_;
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
    chart_type chart_type_;
    fun_type fun_type_;
    bool pressed_;
    bool continous_;
};

#endif // CHARTWIDGET_H
