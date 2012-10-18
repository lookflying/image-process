#include "chartwidget.h"
#include "linearfunction.h"
#include "logfunction.h"
#include "exponentfunction.h"
#include <QDebug>
ChartWidget::ChartWidget(QWidget *parent):
    QWidget(parent)
{
    pressed_ = false;
    continous_ = false;
    in_cur_ = out_cur_ = 0;
    fun_ = NULL;
    setMouseTracking(true);
}

ChartWidget::~ChartWidget(){
    if (fun_ != NULL){
        delete fun_;
    }
}

void ChartWidget::paintEvent(QPaintEvent *){
    QPainter painter(this);
    fun_->get_range(x_min_, x_max_, y_min_, y_max_);
    w_ = width() - 32;
    h_ = height() - 30;
    range_x_ = x_max_ - x_min_;
    range_y_ = y_max_ - y_min_;
    painter.setPen(Qt::black);
    painter.drawLine(24, 0, 24, h_);
    painter.drawLine(24, h_, width(), h_);
    painter.drawText(0, 12, QString("%1").arg(y_max_));
    painter.drawText(0, h_, QString("%1").arg(y_min_));
    painter.drawText(24, height() - 18, QString("%1").arg(x_min_));
    painter.drawText(w_, height() - 18, QString("%1").arg(x_max_));
    if (chart_type_ == LINE){
        for (int x = x_min_ ; x <= x_max_; ++x){
            int y = fun_->get(x);
            painter.drawPoint(24 + (x - x_min_) * w_ / range_x_, (y_max_ - y) * h_ / range_y_);

        }
    }else if (chart_type_ == HISTOGRAM){
        for (int x = x_min_ ; x <= x_max_; ++x){
            int y = fun_->get(x);
            painter.drawLine(24 + (x - x_min_) * w_ / range_x_,
                             (y_max_ - y) * h_ / range_y_,
                             24 + (x - x_min_) * w_ / range_x_,
                             h_);

        }
    }
    painter.drawText(0, height() - 6, QString("(%1 , %2)").arg(in_cur_).arg(out_cur_));
}

void ChartWidget::mousePressEvent(QMouseEvent * event){
    pressed_ = true;
    int in = (event->x() - 24) * range_x_ / w_;
    int out = y_max_ - event->y() * range_y_ / h_;
    fun_->set(in, out);
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
                    fun_->set(i, out);
                }
            }else{
                for (int i = in; i < last_in; ++i){
                    fun_->set(i, out);
                }
            }
        }else{
            fun_->set(in, out);
        }
        last_in = in;
        continous_ = true;
        repaint();
    }else{
        continous_ = false;
    }
    if (in < x_min_ || in > x_max_ || out < y_min_ || out > y_max_){
        return;
    } else{
        in_cur_ = in;
        out_cur_ = out;
        repaint();
    }
}

void ChartWidget::mouseReleaseEvent(QMouseEvent *){
    pressed_ = false;
    continous_ = false;
}

void ChartWidget::set_property( int x_min, int x_max, int y_min, int y_max, fun_type ft, chart_type ct){
    x_min_ = x_min;
    x_max_ = x_max;
    y_min_ = y_min;
    y_max_ = y_max;
    chart_type_ = ct;
    fun_type_ = ft;
    if (fun_ != NULL){
        delete fun_;
    }
    if (fun_type_ == LINEAR){
        fun_ = new LinearFunction(x_min, x_max, y_min, y_max);
    }else if (ft == LOG){
        fun_ = new LogFunction(x_min, x_max, y_min, y_max);
    }else if (ft == EXPONENT){
        fun_ = new ExponentFunction(x_min, x_max, y_min, y_max);
    }else{
        fun_ = new Function(x_min, x_max, y_min, y_max);
    }
    repaint();
}
