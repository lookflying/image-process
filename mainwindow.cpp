#include "mainwindow.h"


#include <QFileDialog>

#include <QMenuBar>
#include <QDebug>

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    if (objectName().isEmpty())
    setObjectName(QString::fromUtf8("MainWindow"));
    resize(800, 500);
    central_widget_ = new QWidget(this);
    central_widget_->setObjectName(QString::fromUtf8("centralWidget"));

    create_actions();
    create_menu_bar();
    create_menus();
    create_tool_bar();
    create_status_bar();
    create_image_view();
    create_tab_widget();
    setCentralWidget(central_widget_);
    show();
}

MainWindow::~MainWindow()
{
}

void MainWindow::create_actions(){
    file_open_act_ = new QAction(tr("&Open"), this);
    file_open_act_->setShortcut(QKeySequence::Open);
    file_open_act_->setStatusTip(tr("Open an image to process"));
    connect(file_open_act_, SIGNAL(triggered()), this, SLOT(open_file()));

    file_save_act_ = new QAction(tr("&Save"), this);
    file_save_act_->setShortcut(QKeySequence::Save);
    file_save_act_->setStatusTip(tr("Save changes to the file"));
    connect(file_save_act_, SIGNAL(triggered()), this, SLOT(save_file()));

    file_save_as_act_ = new QAction(tr("S&ave as"), this);
    file_save_as_act_->setShortcut(QKeySequence::SaveAs);
    file_save_as_act_->setStatusTip(tr("Save changes to another file"));
    connect(file_save_as_act_, SIGNAL(triggered()), this, SLOT(save_file_as()));

    file_close_act_ = new QAction(tr("&Close"), this);
    file_close_act_->setShortcut(QKeySequence::Close);
    file_close_act_->setStatusTip(tr("Close current file"));
    connect(file_close_act_, SIGNAL(triggered()), this, SLOT(close_file()));

    quit_act_ = new QAction(tr("&Quit"), this);
    quit_act_->setShortcut(QKeySequence::Quit);
    quit_act_->setStatusTip(tr("Quit the software"));
    connect(quit_act_, SIGNAL(triggered()), this, SLOT(quit()));

}

void MainWindow::create_menus(){
    file_menu_ = menu_bar_->addMenu(tr("&File"));
    file_menu_->addAction(file_open_act_);
    file_menu_->addAction(file_save_act_);
    file_menu_->addAction(file_save_act_);
    file_menu_->addAction(file_close_act_);
    file_menu_->addSeparator();
    file_menu_->addAction(quit_act_);

}
void MainWindow::create_image_view(){
    image_view_ = new ImageView(central_widget_);
    image_view_->setObjectName(QString::fromUtf8("ImageView"));
    image_view_->setGeometry(QRect(width() * 2 / 7,
                                 main_tool_bar_->height(),
                                 width() * 5 / 7,
                                 height() - menu_bar_->height() - main_tool_bar_->height() - status_bar_->height()));
}

void MainWindow::create_status_bar(){
    status_bar_ = new QStatusBar(this);
    status_bar_->setObjectName(QString::fromUtf8("statusBar"));
    setStatusBar(status_bar_);
}

void MainWindow::create_tool_bar(){
    main_tool_bar_ = new QToolBar(this);
    main_tool_bar_->setObjectName(QString::fromUtf8("mainToolBar"));
    addToolBar(Qt::TopToolBarArea, main_tool_bar_);
}

void MainWindow::create_menu_bar(){
    menu_bar_ = new QMenuBar(this);
    menu_bar_->setObjectName(QString::fromUtf8("menuBar"));
    menu_bar_->setGeometry(QRect(0, 0, width(), 25));
}



void MainWindow::create_tab_widget(){
    tab_widget_ = new QTabWidget(central_widget_);
    tab_widget_->setObjectName(QString::fromUtf8("tabWidget"));
    tab_widget_->setGeometry(QRect(0,
                                   main_tool_bar_->height(),
                                   width() * 2 / 7,
                                   height() - menu_bar_->height() - main_tool_bar_->height() - status_bar_->height()));


    tab_basic_ = new BasicOperationWidget(tab_widget_->width(), tab_widget_->height());
    tab_widget_->addTab(tab_basic_, QString::fromUtf8("Basic"));

    tab_gray_ = new GrayScaleTransformWidget(tab_widget_->width(), tab_widget_->height());
    tab_widget_->addTab(tab_gray_, QString::fromUtf8("Gray"));
}


void MainWindow::open_file(){
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!image_view_->openImage(fileName)){
        QMessageBox::warning(this, tr("Application"), tr("Can't open file %1:\n").arg(fileName));
        return;
    }

}

void MainWindow::save_file(){

}

void MainWindow::save_file_as(){

}

void MainWindow::close_file(){

}

void MainWindow::quit(){

}
