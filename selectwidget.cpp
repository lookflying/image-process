#include "selectwidget.h"
#include <QInputDialog>

using namespace cv;
SelectWidget::SelectWidget(int x, int y, int width, int height, QWidget *parent):
    QWidget(parent){
    setGeometry(x, y, width - 3, height);
    max_rows_ = height / 5;
    max_cols_ = width / 5;
    reset_widget(3, 3, Morphology::DISC);
    pressed_ = false;
    setMouseTracking(true);
}
void SelectWidget::get_se_mat(cv::Mat &out){
    se_mat_.copyTo(out);
}

void SelectWidget::reset_widget(int rows, int cols, int type){
    rows_ = rows;
    cols_ = cols;
    row_step_ = (height() - 1) / rows_;
    col_step_ = (width() - 1 )  / cols_;
    se_mat_ = Morphology::generate_structing_element(cols, rows, type);
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
                painter.fillRect(rect, QColor(0, 0, 255, static_cast<int>(se_mat_.at<uchar>(i, j))));
            }
        }
    }
}


void SelectWidget::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::RightButton){
        pressed_ = true;
        x_ = event->x();
        y_ = event->y();
        int i = y_ / row_step_, j = x_ / col_step_;
        if(is_valid(i, j)){
            if (se_mat_.at<uchar>(i, j) == 0){
                se_mat_.at<uchar>(i, j) = 255;
            }else if (se_mat_.at<uchar>(i, j) == 255){
                se_mat_.at<uchar>(i, j) = 0;
            }
            value_now_ = se_mat_.at<uchar>(i, j);
            repaint();
        }
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
    if (event->button() == Qt::RightButton){
        pressed_ = false;
    }
}

void SelectWidget::mouseDoubleClickEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton){
        bool ok;
        x_ = event->x();
        y_ = event->y();
        int i = y_ / row_step_, j = x_ / col_step_;
        if (is_valid(i, j)){
            int value = QInputDialog::getInt(this, QString::fromUtf8("(%0,%1)").arg(j).arg(i), "Value", static_cast<int>(se_mat_.at<uchar>(i, j)), 0, 255, 1, &ok);
            if (ok){
                se_mat_.at<uchar>(i, j) = static_cast<uchar>(value);
            }
        }
    }
}

bool SelectWidget::is_valid(int i, int j){
    return i >= 0 && i < rows_ && j >=0 && j < cols_;
}
