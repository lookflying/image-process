#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QStatusBar>
#include <QToolBox>
#include <QWidget>
#include <QTabWidget>
#include <QLabel>
#include <QMouseEvent>
#include "imageview.h"
#include "grayscaletransformwidget.h"
#include "basicoperationwidget.h"
#include "filterwidget.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    enum non_linear_actions{LOG, EXPONENT, DO};
    typedef int non_linear_action ;
signals:
    void refresh_image_view();
private slots:
    void open_file();
    void save_file();
    void close_file();
    void save_file_as();
    void quit();

    void redo();
    void undo();

    void gray_linear_transform();
    void gray_non_linear_transform(non_linear_action action);
    void gray_log_transform();
    void gray_exponent_transform();
    void gray_non_linear_do();
    void gray_histogram_display();
    void gray_histogram_equalization();
    void gray_histogram_match();

    void geometry_zoom();
    void geometry_rotate();
    void basic_algebra();
    void basic_algebra_pic();

    void filter_edge_detect();
    void filter_blur();
    void filter_morphology();

    void status_show_position(int x, int y);
private:

    void create_actions();
    void create_menus();
    void create_tool_bar();
    void create_status_bar();
    void create_image_view();
    void create_menu_bar();
    void create_tool_box();
    void create_tab_widget();
    void connect_signal_slot();
    QMenu *file_menu_;
    QMenu *edit_menu_;

    QToolBar *file_tool_bar_;
    QToolBar *edit_tool_bar_;

    QAction *file_open_act_;
    QAction *file_save_act_;
    QAction *file_save_as_act_;
    QAction *file_close_act_;
    QAction *file_quit_act_;

    QAction *edit_undo_act_;
    QAction *edit_redo_act_;

    ImageView *image_view_;
    QWidget *central_widget_;
    QMenuBar *menu_bar_;
    QToolBar *main_tool_bar_;
    QStatusBar *status_bar_;
    QLabel *label_position_;//may delete

    QTabWidget *tab_widget_;

    GrayScaleTransformWidget *tab_gray_;

    BasicOperationWidget *tab_basic_;

    FilterWidget *tab_filter_;


protected:
    void mouseMoveEvent(QMouseEvent *);


};

#endif // MAINWINDOW_H
