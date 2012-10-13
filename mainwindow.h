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

#include "imageview.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void open_file();
    void save_file();
    void close_file();
    void save_file_as();
    void quit();

private:
    void create_actions();
    void create_menus();
    void create_tool_bar();
    void create_status_bar();
    void create_image_view();
    void create_menu_bar();
    void create_tool_box();
    void create_tab_widget();
    QMenu *file_menu_;
    QMenu *edit_menu_;

    QToolBar *file_tool_bar_;
    QToolBar *edit_tool_bar_;

    QAction *file_open_act_;
    QAction *file_save_act_;
    QAction *file_save_as_act_;
    QAction *file_close_act_;
    QAction *quit_act_;

    ImageView *image_view_;
    QWidget *central_widget_;
    QMenuBar *menu_bar_;
    QToolBar *main_tool_bar_;
    QStatusBar *status_bar_;

    QTabWidget *tab_widght_;
    QWidget * tab_1_;
    QWidget * tab_2_;

    QToolBox *tool_box_;
    QWidget *tool_page_1_;
    QWidget *tool_page_2_;
    QWidget *tool_page_3_;
    QWidget *tool_page_4_;


};

#endif // MAINWINDOW_H
