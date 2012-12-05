#include "selectwidget.h"

using namespace cv;
SelectWidget::SelectWidget(int x, int y, int width, int height, QWidget *parent):
    QWidget(parent){
    setGeometry(x, y, width - 3, height);
    max_rows_ = height / 5;
    max_cols_ = width / 5;
    reset_widget(3, 3);
    pressed_ = false;
    setMouseTracking(true);
}
void SelectWidget::get_se_mat(cv::Mat &out){
    out = se_mat_;
}

void SelectWidget::reset_widget(int rows, int cols){
    rows_ = rows;
    cols_ = cols;
    row_step_ = (height() - 1) / rows_;
    col_step_ = (width() - 1 )  / cols_;
    se_mat_ = Mat(rows_, cols_, CV_8UC1, Scalar(0));
    repaint();
}

void SelectWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setBackgroundMode(Qt::OpaqueMode);
    painter.setPen(Qt::black);
    painter.setBackground(Qt::blue);
    for (int i = 0; i < rows_; ++i){
        for (int j = 0; j < cols_; ++j){
            painter.drawRect(j * col_step_, i * row_step_, col_step_, row_step_);
            if (se_mat_.at<uchar>(i, j) != 0){
                QRect rect(j * col_step_, i * row_step_, col_step_, row_step_);
                painter.fillRect(rect, Qt::blue);
            }
        }
    }
}


void SelectWidget::mousePressEvent(QMouseEvent *event){
    pressed_ = true;
    x_ = event->x();
    y_ = event->y();
    int i = y_ / row_step_, j = x_ / col_step_;
    if(is_valid(i, j)){
        se_mat_.at<uchar>(i, j) = ~se_mat_.at<uchar>(i, j);
        value_now_ = se_mat_.at<uchar>(i, j);
        repaint();
    }
//    qDebug()<<event->pos();
}

void SelectWidget::mouseMoveEvent(QMouseEvent *event){
    x_ = event->x();
    y_ = event->y();
    static int old_i, old_j;
    int i = y_ / row_step_, j = x_ / col_step_;
    if (pressed_){
        if (is_valid(i, j) && (i != old_i || j != old_j)){
            if (se_mat_.at<uchar>(i, j) != value_now_){
                se_mat_.at<uchar>(i, j) = value_now_;
                repaint();
            }
        }
    }
    old_i = i;
    old_j = j;

}

void SelectWidget::mouseReleaseEvent(QMouseEvent *event){
    pressed_ = false;
//    int i = y_ / row_step_, j = x_ / col_step_;

//    repaint();
}

bool SelectWidget::is_valid(int i, int j){
    return i >= 0 && i < rows_ && j >=0 && j < cols_;
}
