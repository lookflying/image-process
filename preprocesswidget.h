#ifndef PREPROCESS_H
#define PREPROCESS_H

#include <QWidget>
#include <QToolBox>
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QSpinBox>
#include <QComboBox>

class PreprocessWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PreprocessWidget(int width, int height, QWidget *parent = 0);

    QToolBox * tool_box_;

    QWidget *tool_page_preprocess_;

    QLabel *label_turn_gray_;
    QPushButton *button_turn_gray_;

    QLabel *label_threshold_;
    QSlider *slider_threshold_;
    QSpinBox *spin_box_threshold_;
    QSlider *slider_threshold_optional_;
    QSpinBox *spin_box_threshold_optional_;
    QPushButton *button_threshold_;
    QComboBox *combo_box_threshold_;


signals:
    
public slots:
private:
    void create_widget();
    void create_page_preprocess();
    int page_height_;
};

#endif // PREPROCESS_H
