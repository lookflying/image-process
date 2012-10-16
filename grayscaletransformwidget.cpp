#include "grayscaletransformwidget.h"

GrayScaleTransformWidget::GrayScaleTransformWidget(int width, int height, QWidget *parent) :
    QWidget(parent)
{
    page_height_ = 200;
    this->resize(width, height * 5 / 6);
    create_widget();
    create_page_linear();
    create_page_non_linear();
    create_page_histogram();
}

void GrayScaleTransformWidget::create_widget(){
    tool_box_ = new QToolBox(this);
    tool_box_->setGeometry(QRect(0, 0, width(), height()));
}

void GrayScaleTransformWidget::create_page_linear(){
    tool_page_linear_ = new QWidget();
    tool_page_linear_->setGeometry(QRect(0, 0, width(), page_height_));
    label_input_ = new QLabel(tool_page_linear_);
    label_input_->setGeometry(QRect(0, 0, width(), 24));
    label_input_->setText(QString::fromUtf8("Input Range"));
    spin_box_input_1_ = new QSpinBox(tool_page_linear_);
    spin_box_input_1_->setGeometry(width() / 6, 24, width() / 3, 24);
    spin_box_input_1_->setMaximum(255);
    spin_box_input_1_->setMinimum(0);
    spin_box_input_2_ = new QSpinBox(tool_page_linear_);
    spin_box_input_2_->setGeometry(width() / 2, 24, width() / 3, 24);
    spin_box_input_2_->setMaximum(255);
    spin_box_input_2_->setMinimum(0);
    label_output_ = new QLabel(tool_page_linear_);
    label_output_->setGeometry(QRect(0, spin_box_input_1_->height() + label_input_->height(), width(), 24));
    label_output_->setText(QString::fromUtf8("Output Range"));
    spin_box_output_1_ = new QSpinBox(tool_page_linear_);
    spin_box_output_1_->setGeometry(width() / 6,
                                    spin_box_input_1_->height() + label_input_->height() + label_output_->height()
                                    , width() / 3, 24);
    spin_box_output_1_->setMaximum(255);
    spin_box_output_1_->setMinimum(0);
    spin_box_output_2_ = new QSpinBox(tool_page_linear_);
    spin_box_output_2_->setGeometry(width() / 2,
                                    spin_box_input_1_->height() + label_input_->height() + label_output_->height(),
                                    width() / 3, 24);
    spin_box_output_2_->setMaximum(255);
    spin_box_output_2_->setMinimum(0);
    button_linear_ = new QPushButton(tool_page_linear_);
    button_linear_->setGeometry(QRect(width() / 3,
                                spin_box_input_1_->height() + label_input_->height() + label_output_->height() + spin_box_output_1_->height(),
                                width() / 3,
                                24));
    button_linear_->setText(QString::fromUtf8("Transform"));
    tool_box_->addItem(tool_page_linear_, "Linear");
}

void GrayScaleTransformWidget::create_page_non_linear(){
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

void GrayScaleTransformWidget::create_page_histogram(){
    tool_page_histogram_ = new QWidget();
    tool_page_histogram_->setGeometry(QRect(0, 0, width(), page_height_));
    chart_histogram_ = new ChartWidget(tool_page_histogram_);
    chart_histogram_ ->setGeometry(0, 0, width(), page_height_ - 60);
    chart_histogram_->set_property(0, 255, 0, 255, ChartWidget::HISTOGRAM);
    button_show_ = new QPushButton(tool_page_histogram_);
    button_show_->setGeometry(QRect(width() / 3, chart_histogram_->height(), width() / 3, 24));
    button_show_->setText("Show");
    button_balance_ = new QPushButton(tool_page_histogram_);
    button_balance_->setGeometry(QRect(width() / 7, chart_histogram_->height() + button_show_->height(), width() *2 / 7, 24));
    button_balance_->setText("Balance");
    button_match_ = new QPushButton(tool_page_histogram_);
    button_match_->setGeometry(QRect(width() * 4 / 7, chart_histogram_->height() + button_show_->height(), width() * 2 / 7, 24));
    button_match_->setText("Match");
    tool_box_->addItem(tool_page_histogram_, QString::fromUtf8("Histogram"));
}
