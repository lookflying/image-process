#ifndef FILTERFORMWIDGET_H
#define FILTERFORMWIDGET_H

#include <QWidget>
#include <QToolBox>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include "seselectwidget.h"
class FilterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FilterWidget(int width, int height, QWidget *parent = 0);
    QToolBox *tool_box_;
    
    QWidget *tool_page_edge_detect_;
    QComboBox *combo_box_edge_detect_;
    QPushButton *button_edge_detect_;

    QWidget *tool_page_blur_;
    QComboBox *combo_box_blur_;
    QPushButton *button_blur_;
    QLabel *label_blur_size_;
    QSpinBox *spin_box_blur_size_;
    QLabel *label_blur_sigma_;
    QDoubleSpinBox *double_spin_box_blur_sigma_;

    QWidget *tool_page_morphology_;
    QComboBox *combo_box_morphology_;
    QPushButton *button_morphology_;
    SESelectWidget *se_select_widget_morphology_;
signals:
    
public slots:
    
private:
    void create_widget();
    void create_page_edge_detect();
    void create_page_blur();
    void create_page_morphology();
    int page_height_;
};

#endif // FILTERFORMWIDGET_H
