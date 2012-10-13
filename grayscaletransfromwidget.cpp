#include "grayscaletransfromwidget.h"

GrayScaleTransfromWidget::GrayScaleTransfromWidget(int width, int height, QWidget *parent) :
    QWidget(parent)
{
    page_height_ = 80;
    this->resize(width, height / 2);
    create_widget();
    create_page_linear();
    create_page_non_linear();
}

void GrayScaleTransfromWidget::create_widget(){
    tool_box_ = new QToolBox(this);
    tool_box_->setGeometry(QRect(0, 0, width(), height()));
}

void GrayScaleTransfromWidget::create_page_linear(){
    tool_page_linear_ = new QWidget();
    tool_page_linear_->setGeometry(QRect(0, 0, width(), page_height_));
    label_input_ = new QLabel(tool_page_linear_);
    label_input_->setGeometry(QRect(0, 0, width(), 24));
    label_input_->setText(QString::fromUtf8("Input Range"));
    spin_box_input_1_ = new QSpinBox(tool_page_linear_);
    spin_box_input_1_->setGeometry(width() / 5, 24, width() / 5, 24);
    spin_box_input_2_ = new QSpinBox(tool_page_linear_);
    spin_box_input_2_->setGeometry(width() * 3 / 5, 24, width() / 5, 24);
    label_output_ = new QLabel(tool_page_linear_);
    label_output_->setGeometry(QRect(0, spin_box_input_1_->height() + label_input_->height(), width(), 24));
    label_output_->setText(QString::fromUtf8("Output Range"));
    spin_box_output_1_ = new QSpinBox(tool_page_linear_);
    spin_box_output_1_->setGeometry(width() / 5,
                                    spin_box_input_1_->height() + label_input_->height() + label_output_->height()
                                    , width() / 5, 24);
    spin_box_output_2_ = new QSpinBox(tool_page_linear_);
    spin_box_output_2_->setGeometry(width() * 3 / 5,
                                    spin_box_input_1_->height() + label_input_->height() + label_output_->height(),
                                    width() / 5, 24);
    button_linear_ = new QPushButton(tool_page_linear_);
    button_linear_->setGeometry(QRect(width() / 3,
                                spin_box_input_1_->height() + label_input_->height() + label_output_->height() + spin_box_output_1_->height(),
                                width() / 3,
                                24));
    button_linear_->setText(QString::fromUtf8("Transform"));
    tool_box_->addItem(tool_page_linear_, "Linear");
}

void GrayScaleTransfromWidget::create_page_non_linear(){
    tool_page_non_linear_ = new QWidget();
    tool_page_non_linear_->setGeometry(QRect(0, 0, width(), page_height_));
    label_a_ = new QLabel(tool_page_non_linear_);
    label_a_->setGeometry(width() / 4, 0, width() / 4, 24);
    label_a_->setText(QString::fromUtf8("a = "));
    spin_box_a_ = new QDoubleSpinBox(tool_page_non_linear_);
    spin_box_a_->setGeometry(width() / 2, 0, width() / 4, 24);
    label_b_ = new QLabel(tool_page_non_linear_);
    label_b_->setGeometry(width() / 4, label_a_->height(), width() / 4, 24);
    label_b_->setText(QString::fromUtf8("b = "));
    spin_box_b_ = new QDoubleSpinBox(tool_page_non_linear_);
    spin_box_b_->setGeometry(width() / 2, label_a_->height(), width() / 4, 24);
    label_c_ = new QLabel(tool_page_non_linear_);
    label_c_->setGeometry(width() / 4, label_a_->height() + label_b_->height(), width() / 4, 24);
    label_c_->setText(QString::fromUtf8("c = "));
    spin_box_c_ = new QDoubleSpinBox(tool_page_non_linear_);
    spin_box_c_->setGeometry(width() / 2, label_a_->height() + label_b_->height(), width() / 4, 24);
    button_log_ = new QPushButton(tool_page_non_linear_);
    button_log_->setGeometry(width() / 9,
                             label_a_->height() + label_b_->height() + label_c_->height(),
                             width() / 3,
                             24);
    button_log_->setText(QString::fromUtf8("Log"));
    button_exponent_ = new QPushButton(tool_page_non_linear_);
    button_exponent_->setGeometry(width() * 5 / 9,
                             label_a_->height() + label_b_->height() + label_c_->height(),
                             width() / 3,
                             24);
    button_exponent_->setText(QString::fromUtf8("Exponent"));
    tool_box_->addItem(tool_page_non_linear_, QString::fromUtf8("Non Linear"));

}
