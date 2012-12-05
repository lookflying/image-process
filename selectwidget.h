#ifndef SELECTWIDGET_H
#define SELECTWIDGET_H
#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QPaintEvent>
#include <opencv2/core/core.hpp>
#include "morphology.h"
class SelectWidget : public QWidget{
    Q_OBJECT
public:
    explicit SelectWidget(int x, int y, int width, int height, QWidget *parent = 0);
    void get_se_mat(cv::Mat &out);
    int get_max_row(){
        return max_rows_;
    }
    int get_max_col(){
        return max_cols_;
    }
public slots:
    void reset_widget(int rows, int cols, int type);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    int rows_;
    int cols_;
    int max_rows_;
    int max_cols_;
    int row_step_;
    int col_step_;
    int step_;
    cv::Mat se_mat_;
    bool pressed_;
    uchar value_now_;
    int x_;
    int y_;

    bool is_valid(int i, int j);
};
#endif // SELECTWIDGET_H
