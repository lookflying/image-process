#include "filterwidget.h"

FilterWidget::FilterWidget(int width, int height, QWidget *parent) :
    QWidget(parent)
{

    page_height_ = 200;
    resize(width, height * 8 / 9);
    create_widget();
    create_page_edge_detect();
    create_page_blur();
}

void FilterWidget::create_widget(){
    tool_box_ = new QToolBox(this);
    tool_box_->setGeometry(QRect(0, 0, width(), height()));
}

void FilterWidget::create_page_edge_detect(){
    tool_page_edge_detect_ = new QWidget();
    tool_page_edge_detect_->setGeometry(QRect(0, 0, width(), height()));


    tool_box_->addItem(tool_page_edge_detect_, QString::fromUtf8("Edge Detect"));
}

void FilterWidget::create_page_blur(){
    tool_page_blur_ = new QWidget();
    tool_page_blur_->setGeometry(QRect(0, 0, width(), height()));

    tool_box_->addItem(tool_page_blur_, QString::fromUtf8("Blur"));
}
