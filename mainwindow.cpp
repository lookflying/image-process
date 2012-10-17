#include "mainwindow.h"


#include <QFileDialog>

#include <QMenuBar>
#include <QDebug>

#include <QMessageBox>


#include "imageprocess.h"

#include "function.h"
#include "linearfunction.h"
#include "logfunction.h"
#include "exponentfunction.h"

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
    connect_signal_slot();
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

void MainWindow::connect_signal_slot(){
    connect(this, SIGNAL(refresh_image_view()), image_view_, SLOT(refresh()));
    connect(tab_gray_->button_linear_, SIGNAL(clicked()), this, SLOT(gray_linear_transform()));
    connect(tab_gray_->button_log_, SIGNAL(clicked()), this, SLOT(gray_log_transform()));
    connect(tab_gray_->button_exponent_, SIGNAL(clicked()), this, SLOT(gray_exponent_transform()));
    connect(tab_gray_->button_non_linear_do_, SIGNAL(clicked()), this, SLOT(gray_non_linear_do()));
    connect(tab_gray_->button_show_histogram_, SIGNAL(clicked()), this, SLOT(gray_histogram_display()));
    connect(tab_gray_->button_equalize_, SIGNAL(clicked()), this, SLOT(gray_histogram_equalization()));
    connect(tab_gray_->button_match_, SIGNAL(clicked()), this, SLOT(gray_histogram_match()));
    connect(tab_basic_->button_zoom_, SIGNAL(clicked()), this, SLOT(geometry_zoom()));
}

void MainWindow::save_file(){

}

void MainWindow::save_file_as(){

}

void MainWindow::close_file(){

}

void MainWindow::quit(){

}

void MainWindow::gray_linear_transform(){
    int min_x = tab_gray_->spin_box_input_1_->value();
    int max_x = tab_gray_->spin_box_input_2_->value();
    int min_y = tab_gray_->spin_box_output_1_->value();
    int max_y = tab_gray_->spin_box_output_2_->value();
    ImageProcess::gray_linear_transform(image_view_->image_data_, min_x, max_x, min_y, max_y);
    emit refresh_image_view();
}
void MainWindow::gray_log_transform(){
    gray_non_linear_transform(LOG);
}

void MainWindow::gray_exponent_transform(){
    gray_non_linear_transform(EXPONENT);
}

void MainWindow::gray_non_linear_do(){
    gray_non_linear_transform(DO);
}

void MainWindow::gray_non_linear_transform(non_linear_action action){
    double a = tab_gray_->spin_box_a_->value();
    double b = tab_gray_->spin_box_b_->value();
    double c = tab_gray_->spin_box_c_->value();
    switch (action){
    case LOG:
    {
        if (c <= 0 || c == 1 || c == 0)
            return;
        tab_gray_->chart_non_linear_->set_property(0, 255, 0, 255, ChartWidget::LOG, ChartWidget::LINE);
        LogFunction* fun;
        assert((fun = dynamic_cast<LogFunction*>(tab_gray_->chart_non_linear_->fun_)) != 0);
        fun->set_value(a, b, c);
        tab_gray_->chart_non_linear_->repaint();
        break;
    }
    case EXPONENT:
    {
        tab_gray_->chart_non_linear_->set_property(0, 255, 0, 255, ChartWidget::EXPONENT, ChartWidget::LINE);
        ExponentFunction* fun;
        assert((fun = dynamic_cast<ExponentFunction*>(tab_gray_->chart_non_linear_->fun_)) != 0);
        fun->set_value(a, b, c);
        tab_gray_->chart_non_linear_->repaint();
        break;
    }
    case DO:
    {
        if (tab_gray_->chart_non_linear_->fun_ != NULL){
            ImageProcess::gray_fun_transform(image_view_->image_data_, tab_gray_->chart_non_linear_->fun_);
            emit refresh_image_view();
        }
        break;
    }
    default:
        break;
    }
}

void MainWindow::gray_histogram_display(){
     Function *fun  = ImageProcess::get_gray_histogram(image_view_->image_data_, ImageProcess::FREQUENCE);
     if (!fun->ready()){
         delete fun;
         return;
     }
     Function *old = tab_gray_->chart_histogram_->fun_;
     if (old != NULL){
         delete old;
     }
     tab_gray_->chart_histogram_->fun_ = fun;
     tab_gray_->chart_histogram_->repaint();
}

void MainWindow::gray_histogram_equalization(){
    Function *fun  = ImageProcess::get_gray_histogram(image_view_->image_data_, ImageProcess::FREQUENCE);
    if (!fun->ready()){
        delete fun;
        return;
    }
    Function *equal = ImageProcess::get_histogram_equalization_fun(fun);
    if (!equal->ready()){
        delete equal;
        return;
    }
    ImageProcess::gray_fun_transform(image_view_->image_data_, equal);
    gray_histogram_display();
    emit refresh_image_view();
    delete equal;
    delete fun;
}

void MainWindow::gray_histogram_match(){
    Function *origin = ImageProcess::get_gray_histogram(image_view_->image_data_, ImageProcess::FREQUENCE);
    if (!origin->ready()){
        delete origin;
        return;
    }
    Function *target = tab_gray_->chart_histogram_->fun_;
    if (target == NULL)
        return;
    else if (!target->ready()){
        delete target;
        return;
    }
    Function *match = ImageProcess::get_histogram_match_fun(origin, target);
    if (!match->ready()){
        delete match;
        return;
    }
    ImageProcess::gray_fun_transform(image_view_->image_data_, match);
    gray_histogram_display();
    delete match;
    delete origin;
    emit refresh_image_view();


}

void MainWindow::geometry_zoom(){
    ImageProcess::zoom_type type = ImageProcess::Nearest;
    switch(tab_basic_->combo_zoom_->currentIndex()){
    case 0:
        type = ImageProcess::Nearest;
        break;
    case 1:
        type = ImageProcess::BILINEAR;
        break;
    case 2:
        type = ImageProcess::BICUBIC;
        break;
    }
    int percentage = tab_basic_->spin_box_zoom_->value();
    ImageProcess::geometry_zoom(image_view_->image_data_, percentage, type);
    emit refresh_image_view();
}
