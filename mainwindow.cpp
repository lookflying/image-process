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
    create_tool_box();
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

void MainWindow::create_tool_box(){
    tool_box_ = new QToolBox(tab_1_);
    tool_box_->setObjectName(QString::fromUtf8("toolBar"));
    tool_box_->setGeometry(QRect(0,
                                 0,
                                 width() * 2 / 7,
                                 height() - menu_bar_->height() -  main_tool_bar_->height() - status_bar_->height() - 30));
//    tool_box_->setFrameShape(QFrame::Box);
//    tool_box_->setLineWidth(1);
    tool_page_1_ = new QWidget();
    tool_page_1_->setObjectName(QString::fromUtf8("toolPage1"));
    tool_page_1_->setGeometry(QRect(0, 0, tool_box_->width() , 80));
    tool_box_->addItem(tool_page_1_, QString::fromUtf8("Page 1"));
    tool_page_2_ = new QWidget();
    tool_page_2_->setObjectName(QString::fromUtf8("toolPage2"));
    tool_page_2_->setGeometry(QRect(0, 0, tool_box_->width(), 80));
    tool_box_->addItem(tool_page_2_, QString::fromUtf8("Page 2"));
    tool_page_3_ = new QWidget();
    tool_page_3_->setObjectName(QString::fromUtf8("toolPage3"));
    tool_page_3_->setGeometry(QRect(0, 0, tool_box_->width(), 80));
    tool_box_->addItem(tool_page_3_, QString::fromUtf8("Page 3"));
    tool_page_4_ = new QWidget();
    tool_page_4_->setObjectName(QString::fromUtf8("toolPage4"));
    tool_page_4_->setGeometry(QRect(0, 0, tool_box_->width(), 80));
    tool_box_->addItem(tool_page_4_, QString::fromUtf8("Page 4"));
}

void MainWindow::create_tab_widget(){
    tab_widget_ = new QTabWidget(central_widget_);
    tab_widget_->setObjectName(QString::fromUtf8("tabWidget"));
    tab_widget_->setGeometry(QRect(0,
                                   main_tool_bar_->height(),
                                   width() * 2 / 7,
                                   height() - menu_bar_->height() - main_tool_bar_->height() - status_bar_->height()));
    tab_1_ = new QWidget();
    tab_1_->setObjectName(QString::fromUtf8("Tab1"));
    tab_widget_->addTab(tab_1_, QString::fromUtf8("tab1"));
    tab_2_ = new QWidget();
    tab_2_->setObjectName(QString::fromUtf8("Tab2"));
    tab_widget_->addTab(tab_2_, QString::fromUtf8("tab2"));
    tab_gray_ = new GrayScaleTransfromWidget(tab_widget_->width(), tab_widget_->height());
    tab_widget_->addTab(tab_gray_, QString::fromUtf8("Gray"));
}

void MainWindow::create_function_widget_1(){

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
