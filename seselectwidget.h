#ifndef SETSTRUCTURINGELEMENTFORM_H
#define SETSTRUCTURINGELEMENTFORM_H

#include <QWidget>
#include <QSpinBox>
#include <QPushButton>

class SESelectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SESelectWidget(int width, int height, QWidget *parent = 0);
    

    QSpinBox spin_box_width_;
    QSpinBox spin_box_height_;
    QPushButton button_modify_;

signals:
public slots:

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent * event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    
private:
    void create_widget();


    int min_width_;
    int min_height_;
};

#endif // SETSTRUCTURINGELEMENTFORM_H
