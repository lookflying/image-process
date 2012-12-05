#ifndef SETSTRUCTURINGELEMENTFORM_H
#define SETSTRUCTURINGELEMENTFORM_H

#include <QWidget>
#include <QSpinBox>
#include <QPushButton>
#include "selectwidget.h"
#include <opencv2/core/core.hpp>
#include <QDebug>
#include <QMouseEvent>
#include <QComboBox>
class SESelectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SESelectWidget(int x, int y, int width, int height, QWidget *parent = 0);
    

    QSpinBox *spin_box_col_;
    QSpinBox *spin_box_row_;
    QComboBox *combo_box_se_;
    QPushButton *button_modify_;
    SelectWidget *select_widget_;

signals:
    void reset_select_widget(int rows, int cols, int type);
public slots:
    void reset_row(int row);
    void reset_col(int col);
    void modify();
protected:


private:
    void create_widget();
    void connect_signal_slot();
    bool is_in_area(int x, int y);

    int area_top_;
    int area_bottom_;

    int rows_;
    int cols_;




};



#endif // SETSTRUCTURINGELEMENTFORM_H
