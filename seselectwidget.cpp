#include "seselectwidget.h"
using namespace cv;
SESelectWidget::SESelectWidget(int x, int y, int width, int height, QWidget *parent):
    QWidget(parent)
{
    area_top_ = width;
    area_bottom_ = height;
    cols_ = 3;
    rows_ = 3;

    setGeometry(x, y, width, height);
    create_widget();
    connect_signal_slot();
}


void SESelectWidget::create_widget(){
    spin_box_col_ = new QSpinBox(this);
    spin_box_col_->setGeometry(QRect(width() / 20, 12, width() / 4, 24));
    spin_box_row_ = new QSpinBox(this);
    spin_box_row_->setGeometry(QRect(width() * 3 / 10, 12, width() / 4, 24));


    button_modify_ = new QPushButton(QString::fromUtf8("Modify"), this);
    button_modify_->setGeometry(QRect(width() * 3 / 5, 12, width() / 4, 24));

    area_top_ = 36;
    area_bottom_ = height();
    select_widget_ = new SelectWidget(0, area_top_, width(), area_bottom_ - area_top_ , this);
    spin_box_col_->setRange(cols_, select_widget_->get_max_col());
    spin_box_row_->setRange(rows_, select_widget_->get_max_row());
}

void SESelectWidget::connect_signal_slot(){
    connect(spin_box_col_, SIGNAL(valueChanged(int)), this, SLOT(reset_col(int)));
    connect(spin_box_row_, SIGNAL(valueChanged(int)), this, SLOT(reset_row(int)));
    connect(button_modify_, SIGNAL(clicked()), this, SLOT(modify()));
    connect(this, SIGNAL(reset_select_widget(int,int)), select_widget_, SLOT(reset_widget(int,int)));
}

bool SESelectWidget::is_in_area(int x, int y){
    return (x >=0 && x <= width() && y >= area_top_ && y < area_bottom_);
}



void SESelectWidget::reset_row(int row){
    rows_ = row;
}

void SESelectWidget::reset_col(int col){
    cols_ = col;
}

void SESelectWidget::modify(){
    emit reset_select_widget(rows_, cols_);
}
