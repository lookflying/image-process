#ifndef GRAYSCALETRANSFROMWIDGET_H
#define GRAYSCALETRANSFROMWIDGET_H

#include <QWidget>
#include <QToolBox>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QDoubleSpinBox>
#include "chartwidget.h"
class GrayScaleTransfromWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GrayScaleTransfromWidget(int width, int height, QWidget *parent = 0);
    
signals:
    
public slots:

private:
    void create_widget();
    void create_page_linear();
    void create_page_non_linear();
    void create_page_histogram();

    int page_height_;

    QToolBox *tool_box_;

    QWidget *tool_page_linear_;
    QLabel *label_input_;
    QLabel *label_output_;
    QSpinBox *spin_box_input_1_;
    QSpinBox *spin_box_input_2_;
    QSpinBox *spin_box_output_1_;
    QSpinBox *spin_box_output_2_;
    QPushButton *button_linear_;

    QWidget *tool_page_non_linear_;
    QLabel *label_a_;
    QLabel *label_b_;
    QLabel *label_c_;
    QDoubleSpinBox *spin_box_a_;
    QDoubleSpinBox *spin_box_b_;
    QDoubleSpinBox *spin_box_c_;
    QPushButton *button_log_;
    QPushButton *button_exponent_;

    QWidget *tool_page_histogram_;
    ChartWidget *chart_hitogram_;


    
};

#endif // GRAYSCALETRANSFROMWIDGET_H
