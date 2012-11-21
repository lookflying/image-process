#include "filterwidget.h"
#include "edgedetect.h"
#include "blur.h"
#include "morphology.h"

FilterWidget::FilterWidget(int width, int height, QWidget *parent) :
    QWidget(parent)
{

    page_height_ = 200;
    resize(width, height * 8 / 9);
    create_widget();
    create_page_edge_detect();
    create_page_blur();
    create_page_morphology();
}

void FilterWidget::create_widget(){
    tool_box_ = new QToolBox(this);
    tool_box_->setGeometry(QRect(0, 0, width(), height()));
}

void FilterWidget::create_page_edge_detect(){
    tool_page_edge_detect_ = new QWidget();
    tool_page_edge_detect_->setGeometry(QRect(0, 0, width(), height()));
    combo_box_edge_detect_ = new QComboBox(tool_page_edge_detect_);
    combo_box_edge_detect_->setGeometry(QRect(width() / 6, 12, width() * 2 / 3, 24));
    combo_box_edge_detect_->insertItem(EdgeDetect::ROBERTS, QString::fromUtf8("ROBERTS"));
    combo_box_edge_detect_->insertItem(EdgeDetect::SOBEL, QString::fromUtf8("SOBEL"));
    combo_box_edge_detect_->insertItem(EdgeDetect::PREWITT, QString::fromUtf8("PREWITT"));

    button_edge_detect_ = new QPushButton(QString::fromUtf8("Detect"), tool_page_edge_detect_);
    button_edge_detect_->setGeometry(QRect(width() / 3, 40, width() / 3, 24));


    tool_box_->addItem(tool_page_edge_detect_, QString::fromUtf8("Edge Detect"));
}

void FilterWidget::create_page_blur(){
    tool_page_blur_ = new QWidget();
    tool_page_blur_->setGeometry(QRect(0, 0, width(), height()));

    combo_box_blur_ = new QComboBox(tool_page_blur_);
    combo_box_blur_->setGeometry(QRect(width() / 6, 12, width() * 2 / 3, 24));
    combo_box_blur_->insertItem(Blur::GAUSSIAN, QString::fromUtf8("GAUSSIAN"));
    combo_box_blur_->insertItem(Blur::MEDIAN, QString::fromUtf8("MEDIAN"));
    combo_box_blur_->insertItem(Blur::MEAN, QString::fromUtf8("MEAN"));
    label_blur_size_ = new QLabel(QString::fromUtf8("size"), tool_page_blur_);
    label_blur_size_->setGeometry(0, 40, width() / 7, 24);
    spin_box_blur_size_ = new QSpinBox(tool_page_blur_);
    spin_box_blur_size_->setGeometry(QRect(width() / 7, 40, width() * 2 / 7, 24));
    spin_box_blur_size_->setRange(1, 100);
    spin_box_blur_size_->setSingleStep(2);
    label_blur_sigma_ = new QLabel(QString::fromUtf8("sigma"), tool_page_blur_);
    label_blur_sigma_->setGeometry(QRect(width() * 3 / 7, 40, width() * 3 / 14, 24));
    double_spin_box_blur_sigma_ = new QDoubleSpinBox(tool_page_blur_);
    double_spin_box_blur_sigma_->setGeometry(QRect(width() * 9 / 14, 40, width() * 2 / 7, 24));
    double_spin_box_blur_sigma_->setRange(0.01, 10.0);
    double_spin_box_blur_sigma_->setSingleStep(0.01);

    button_blur_ = new QPushButton(QString::fromUtf8("Blur"), tool_page_blur_);
    button_blur_->setGeometry(QRect(width() / 3, 68, width() / 3, 24));
    tool_box_->addItem(tool_page_blur_, QString::fromUtf8("Blur"));
}

void FilterWidget::create_page_morphology(){
    tool_page_morphology_ = new QWidget();
    tool_page_morphology_->setGeometry(QRect(0, 0, width(), height()));
    combo_box_morphology_ = new QComboBox(tool_page_morphology_);
    combo_box_morphology_->setGeometry(QRect(width() / 9, 12, width() * 7 / 9, 24));
    combo_box_morphology_->insertItem(Morphology::EROSION, QString::fromUtf8("EROSION"));
    combo_box_morphology_->insertItem(Morphology::DILATION, QString::fromUtf8("DILATION"));
    combo_box_morphology_->insertItem(Morphology::OPENING, QString::fromUtf8("OPENING"));
    combo_box_morphology_->insertItem(Morphology::CLOSING, QString::fromUtf8("CLOSING"));
    combo_box_morphology_->insertItem(Morphology::DISTANCE_TRANSFORM, QString::fromUtf8("DISTANCE_TRANSFORM"));
    combo_box_morphology_->insertItem(Morphology::SKELETONIZATION, QString::fromUtf8("SKELETONIZATION"));
    combo_box_morphology_->insertItem(Morphology::RESTORATION, QString::fromUtf8("RESTORATION"));
    button_morphology_ = new QPushButton(QString::fromUtf8("Transform"), tool_page_morphology_);
    button_morphology_->setGeometry(QRect(width() / 3, 40, width() / 3, 24));
    tool_box_->addItem(tool_page_morphology_, QString::fromUtf8("Morphology"));
}
