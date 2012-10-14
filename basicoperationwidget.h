#ifndef BASICOPERATIONWIDGET_H
#define BASICOPERATIONWIDGET_H

#include <QWidget>
#include <QToolBox>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QSpinBox>
#include <QToolButton>

class BasicOperationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BasicOperationWidget(int width, int height, QWidget *parent = 0);
    
signals:
    
public slots:

private:
    void create_widget();
    void create_page_algebra();
    void create_page_geometry();

    int page_height_;

    QToolBox *tool_box_;

    QWidget *tool_page_algebra_;
    QLabel *label_algebra_;
    QComboBox *combo_algebra_;
    QToolButton *tool_button_algebra_;
    QLabel *label_algebra_pic_;
    QPushButton *button_algebra_;

    QWidget *tool_page_geometry_;
    QLabel *label_zoom_;
    QComboBox *combo_zoom_;
    QSpinBox *spin_box_zoom_;
    QLabel *label_rotate_;
    QSpinBox *spin_box_rotate_;
    
};

#endif // BASICOPERATIONWIDGET_H
