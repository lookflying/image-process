#include "preprocesswidget.h"

PreprocessWidget::PreprocessWidget(int width, int height, QWidget *parent):
    QWidget(parent)
{
    page_height_ = 200;
    resize(width, height * 8 / 9);
    create_widget();
    create_page_preprocess();
}

void PreprocessWidget::create_widget(){
    tool_box_ = new QToolBox(this);
    tool_box_->setGeometry(QRect(0, 0, width(), height()));
}

void PreprocessWidget::create_page_preprocess(){
    tool_page_preprocess_ = new QWidget();
    button_turn_gray_ = new QPushButton(tool_page_preprocess_);
    button_turn_gray_->setGeometry(QRect(width() / 3, 0, width() / 3, 24));
    button_turn_gray_->setText(QString::fromUtf8("&Turn Gray"));
    label_threshold_ = new QLabel(tool_page_preprocess_);
    label_threshold_->setGeometry(0, 28, width(), 24);
    label_threshold_->setText(QString::fromUtf8("Threshold"));
    slider_threshold_ = new QSlider(Qt::Horizontal, tool_page_preprocess_);
    slider_threshold_->setGeometry(QRect(0, 56, width() *3 / 4, 24));
    slider_threshold_->setRange(0, 255);
    slider_threshold_->setTickPosition(QSlider::TicksBothSides);
    spin_box_threshold_ = new QSpinBox(tool_page_preprocess_);
    spin_box_threshold_->setGeometry(QRect(width() *3 / 4, 56, width() / 4, 24));
    spin_box_threshold_->setRange(0, 255);
    connect(slider_threshold_, SIGNAL(valueChanged(int)),spin_box_threshold_, SLOT(setValue(int)));
    connect(spin_box_threshold_, SIGNAL(valueChanged(int)), slider_threshold_, SLOT(setValue(int)));
    slider_threshold_optional_ = new QSlider(Qt::Horizontal, tool_page_preprocess_);
    slider_threshold_optional_->setGeometry(QRect(0, 84, width() * 3 / 4, 24));
    slider_threshold_optional_->setRange(0, 255);
    slider_threshold_optional_->setTickPosition(QSlider::TicksBothSides);
    spin_box_threshold_optional_ = new QSpinBox(tool_page_preprocess_);
    spin_box_threshold_optional_->setGeometry(QRect(width() * 3 / 4, 84, width() / 4, 24));
    spin_box_threshold_optional_->setRange(0, 255);
    connect(slider_threshold_optional_, SIGNAL(valueChanged(int)),spin_box_threshold_optional_, SLOT(setValue(int)));
    connect(spin_box_threshold_optional_, SIGNAL(valueChanged(int)), slider_threshold_optional_, SLOT(setValue(int)));

    combo_box_threshold_ = new QComboBox(tool_page_preprocess_);
    combo_box_threshold_->setGeometry(width() / 13, 112, width() * 5 / 13, 24);
    combo_box_threshold_->addItem(QString::fromUtf8("ISODATA"));
    combo_box_threshold_->addItem(QString::fromUtf8("OTSU"));
    combo_box_threshold_->addItem(QString::fromUtf8("ENTROPY"));
    combo_box_threshold_->addItem(QString::fromUtf8("SOBEL_AREA"));
    button_threshold_ = new QPushButton(tool_page_preprocess_);
    button_threshold_->setGeometry(width() * 7 / 13, 112, width() * 5 / 13, 24);
    button_threshold_->setText(QString::fromUtf8("Auto"));
    tool_box_->addItem(tool_page_preprocess_, "Preprocess");

}
