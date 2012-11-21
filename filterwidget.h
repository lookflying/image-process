#ifndef FILTERFORMWIDGET_H
#define FILTERFORMWIDGET_H

#include <QWidget>
#include <QToolBox>

class FilterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FilterWidget(int width, int height, QWidget *parent = 0);
    QToolBox *tool_box_;
    
    QWidget *tool_page_edge_detect_;

    QWidget *tool_page_blur_;

signals:
    
public slots:
    
private:
    void create_widget();
    void create_page_edge_detect();
    void create_page_blur();
    int page_height_;
};

#endif // FILTERFORMWIDGET_H
