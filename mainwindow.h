#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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


private:
    void createActions();
    void createMenus();
    void createToolBar();
    void createStatusBar();
    void createImageView();
    void createMenuBar();
    QMenu *fileMenu;
    QMenu *editMenu;

    QToolBar *fileToolBar;
    QToolBar *editToolBar;

    QAction *fileOpenAct;
    QAction *fileSaveAct;
    QAction *fileSaveAsAct;
    QAction *fileCloseAct;
    QAction *fileQuitAct;

    ImageView *imageView;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;


};

#endif // MAINWINDOW_H
