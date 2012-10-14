#include "chartwidget.h"
#include <QDebug>
ChartWidget::ChartWidget(int w, int h, QWidget *parent):
    QWidget(parent)
{
    set_property(w, h);
    pressed_ = false;
    continous_ = false;
}

void ChartWidget::paintEvent(QPaintEvent *){
    QPainter painter(this);

    w_ = width() - 32;
    h_ = height() - 12;
    range_x_ = x_max_ - x_min_;
    range_y_ = y_max_ - y_min_;
    painter.setPen(Qt::black);
    painter.drawLine(24, 0, 24, h_);
    painter.drawLine(24, h_, width(), h_);
    painter.drawText(0, 12, QString("%1").arg(y_max_));
    painter.drawText(0, h_, QString("%1").arg(y_min_));
    painter.drawText(24, height(), QString("%1").arg(x_min_));
    painter.drawText(w_, height(), QString("%1").arg(x_max_));
    if (type_ == LINE){
        for (int x = x_min_ ; x <= x_max_; ++x){
            int y;
            if(fun.get(x, y)){
                painter.drawPoint(24 + (x - x_min_) * w_ / range_x_, (y_max_ - y) * h_ / range_y_);
            }
        }
    }else if (type_ == HISTOGRAM){

    }
}

void ChartWidget::mousePressEvent(QMouseEvent * event){
    pressed_ = true;
    int in = (event->x() - 24) * range_x_ / w_;
    int out = y_max_ - event->y() * range_y_ / h_;
    fun.set(in, out);
    repaint();
}

void ChartWidget::mouseMoveEvent(QMouseEvent *event){
    int in = (event->x() - 24) * range_x_ / w_;
    int out = y_max_ - event->y() * range_y_ / h_;
    static int last_in;
    if (pressed_){
        if (continous_){
            if (last_in < in){
                for (int i = last_in + 1; i <= in; ++i){
                    fun.set(i, out);
                }
            }else{
                for (int i = in; i < last_in; ++i){
                    fun.set(i, out);
                }
            }
        }else{
            fun.set(in, out);
        }
        last_in = in;
        continous_ = true;
        repaint();
    }else{
        continous_ = false;
    }
}

void ChartWidget::mouseReleaseEvent(QMouseEvent *){
    pressed_ = false;
    continous_ = false;
}

void ChartWidget::set_property(int width, int height, int x_min, int x_max, int y_min, int y_max, chart_type type){
    resize(width, height);
    x_min_ = x_min;
    x_max_ = x_max;
    y_min_ = y_min;
    y_max_ = y_max;
    type_ = type;
    fun = LinearFunction(x_min, x_max, y_min, y_max, 1);
    repaint();
}
