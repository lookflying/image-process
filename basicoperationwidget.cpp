#include "basicoperationwidget.h"

BasicOperationWidget::BasicOperationWidget(int width, int height, QWidget *parent) :
    QWidget(parent)
{
    page_height_ = 200;
    this->resize(width, height * 5 / 6);
    create_widget();
    create_page_algebra();
    create_page_geometry();
}

void BasicOperationWidget::create_widget(){
    tool_box_ = new QToolBox(this);
    tool_box_->setGeometry(QRect(0, 0, width(), height()));
}

void BasicOperationWidget::create_page_algebra(){
    tool_page_algebra_ = new QWidget();
    tool_page_algebra_->setGeometry(QRect(0, 0, width(), page_height_));
    label_algebra_ = new QLabel(tool_page_algebra_);
    label_algebra_->setGeometry(QRect(width() / 6, 0, width() / 3, 24));
    label_algebra_->setText(QString::fromUtf8("Algebra:"));
    combo_algebra_ = new QComboBox(tool_page_algebra_);
    combo_algebra_->setGeometry(QRect(width() / 2, 0, width() / 3, 24));
    combo_algebra_->insertItem(0, QString::fromUtf8("Add"));
    combo_algebra_->insertItem(1, QString::fromUtf8("Subtract"));
    combo_algebra_->insertItem(2, QString::fromUtf8("Multiply"));
    combo_algebra_->insertItem(3, QString::fromUtf8("Divide"));
    tool_button_algebra_ = new QToolButton(tool_page_algebra_);
    tool_button_algebra_->setGeometry(QRect(width() / 6,
                                            label_algebra_->height(),
                                            width() / 2,
                                            24));
    tool_button_algebra_->setText("another pic");
    label_algebra_pic_ = new QLabel(tool_page_algebra_);
    label_algebra_pic_->setGeometry(QRect(0,
                                          label_algebra_->height() + tool_button_algebra_->height(),
                                          width(),
                                          24));
    button_algebra_ = new QPushButton(tool_page_algebra_);
    button_algebra_->setGeometry(QRect(width() / 2,
                                       label_algebra_->height() + tool_button_algebra_->height() + label_algebra_pic_->height(),
                                       width() / 3,
                                       24));
    button_algebra_->setText(QString::fromUtf8("Do"));
    tool_box_->addItem(tool_page_algebra_, QString::fromUtf8("Algebra"));
}

void BasicOperationWidget::create_page_geometry(){
    tool_page_geometry_ = new QWidget();
    tool_page_geometry_->setGeometry(QRect(0, 0, width(), page_height_));
    combo_zoom_ = new QComboBox(tool_page_geometry_);
    combo_zoom_->setGeometry(0, 0, width(), 24);
    combo_zoom_->insertItem(0, QString::fromUtf8("Nearest Neighbour Interpolation"));
    combo_zoom_->insertItem(1, QString::fromUtf8("Bilinear Interpolation"));
    combo_zoom_->insertItem(2, QString::fromUtf8("Bicubic Interpolation"));
    label_zoom_ = new QLabel(tool_page_geometry_);
    label_zoom_->setGeometry(QRect(width() / 6, combo_zoom_->height(), width() / 3, 24));
    label_zoom_->setText(QString::fromUtf8("Zoom"));
    spin_box_zoom_ = new QSpinBox(tool_page_geometry_);
    spin_box_zoom_->setGeometry(QRect(width() / 2, combo_zoom_->height(), width() / 3, 24));
    tool_box_->addItem(tool_page_geometry_, QString::fromUtf8("Geometry"));
}
