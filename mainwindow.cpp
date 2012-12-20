#include "mainwindow.h"


#include <QFileDialog>

#include <QMenuBar>
#include <QDebug>

#include <QMessageBox>


#include "imageprocess.h"
#include "edgedetect.h"
#include "blur.h"
#include "morphology.h"

#include "function.h"
#include "linearfunction.h"
#include "logfunction.h"
#include "exponentfunction.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
using namespace std;
using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    if (objectName().isEmpty())
    setObjectName(QString::fromUtf8("MainWindow"));
    resize(800, 500);
    central_widget_ = new QWidget(this);
    central_widget_->setObjectName(QString::fromUtf8("centralWidget"));
    create_image();
    create_actions();
    create_menu_bar();
    create_menus();
    create_tool_bar();
    create_status_bar();
    create_image_view();
    create_tab_widget();
    create_show_window_manager();
    create_shortcut();
    setCentralWidget(central_widget_);
    connect_signal_slot();
    setMouseTracking(true);

}

MainWindow::~MainWindow()
{
    delete show_window_manager_;
}

void MainWindow::create_image(){
    image_ = new FImage();
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

    file_quit_act_ = new QAction(tr("&Quit"), this);
    file_quit_act_->setShortcut(QKeySequence::Quit);
    file_quit_act_->setStatusTip(tr("Quit the software"));
    connect(file_quit_act_, SIGNAL(triggered()), this, SLOT(quit()));

    edit_undo_act_ = new QAction(tr("&Undo"), this);
    edit_undo_act_->setShortcut(QKeySequence::Undo);
    edit_undo_act_->setStatusTip(tr("Undo last step"));
    connect(edit_undo_act_, SIGNAL(triggered()), this, SLOT(undo()));

    edit_redo_act_ = new QAction(tr("&Redo"), this);
    edit_redo_act_->setShortcut(QKeySequence::Redo);
    edit_redo_act_->setStatusTip(tr("Redo last step"));
    connect(edit_redo_act_, SIGNAL(triggered()), this, SLOT(redo()));

}

void MainWindow::create_menus(){
    file_menu_ = menu_bar_->addMenu(tr("F&ile"));
    file_menu_->addAction(file_open_act_);
    file_menu_->addAction(file_save_act_);
    file_menu_->addAction(file_save_act_);
    file_menu_->addAction(file_close_act_);
    file_menu_->addSeparator();
    file_menu_->addAction(file_quit_act_);

    edit_menu_ = menu_bar_->addMenu(tr("&Edit"));
    edit_menu_->addAction(edit_undo_act_);
    edit_menu_->addAction(edit_redo_act_);

}
void MainWindow::create_check_box(){
   //created in image view
}

void MainWindow::create_image_view(){
    image_view_ = new ImageView(central_widget_);
    image_view_->setObjectName(QString::fromUtf8("ImageView"));
    image_view_->setGeometry(QRect(width() * 2 / 7,
                                 main_tool_bar_->height(),
                                 width() * 5 / 7,
                                 height() - menu_bar_->height() - main_tool_bar_->height() - status_bar_->height()));
    check_box_create_new_window_ = new QCheckBox(central_widget_);
    check_box_create_new_window_->setText(QString::fromUtf8("&New Window Mode"));
    check_box_create_new_window_->setGeometry(QRect(600, image_view_->height() + image_view_->y(), 200, 24));
    check_box_create_new_window_->setChecked(false);
}

void MainWindow::create_status_bar(){
    status_bar_ = new QStatusBar(this);
    label_position_ = new QLabel(status_bar_);
    label_position_->setGeometry(QRect(0, 0, status_bar_->width(), status_bar_->height()));
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
    tab_widget_->addTab(tab_basic_, QString::fromUtf8("B&asic"));

    tab_gray_ = new GrayScaleTransformWidget(tab_widget_->width(), tab_widget_->height());
    tab_widget_->addTab(tab_gray_, QString::fromUtf8("&Gray"));

    tab_filter_ = new FilterWidget(tab_widget_->width(), tab_widget_->height());
    tab_widget_->addTab(tab_filter_, QString::fromUtf8("&Filter"));

    tab_preprocess_ = new PreprocessWidget(tab_widget_->width(), tab_widget_->height());
    tab_widget_->addTab(tab_preprocess_, QString::fromUtf8("&Pre"));


}


void MainWindow::open_file(){
    QString file_name = QFileDialog::getOpenFileName(this);
//    if (!image_view_->openImage(file_name)){
//        QMessageBox::warning(this, tr("Application"), tr("Can't open file %1:\n").arg(file_name));
//        return;
//    }

    if (!image_->load(file_name)){
        QMessageBox::warning(this, tr("Application"), tr("Can't open file %1:\n").arg(file_name));
        return;
    }
    show_window_manager_->show_window(image_->get_image(), file_name.toStdString(), true);


}

static void show_window_action(cv::Mat img, QWidget *ui, string){

    ((MainWindow*)ui)->image_->set_image(img);
    ((MainWindow*)ui)->image_view_->show_image(((MainWindow*)ui)->image_->get_qimage_image());
}

void MainWindow::create_shortcut(){
    short_cut_clear_ = new QShortcut(QKeySequence::Copy, this);
    connect(short_cut_clear_, SIGNAL(activated()), this, SLOT(show_window_clear_()));
}



void MainWindow::create_show_window_manager(){
    show_window_manager_ = new ShowWindowManager();
    show_window_manager_->set_ui(this);
    show_window_manager_->set_refresh_action(&show_window_action);
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
    connect(tab_basic_->button_rotate_, SIGNAL(clicked()), this, SLOT(geometry_rotate()));
    connect(tab_basic_->button_algebra_, SIGNAL(clicked()), this, SLOT(basic_algebra()));
    connect(tab_basic_->tool_button_algebra_, SIGNAL(clicked()), this, SLOT(basic_algebra_pic()));
    connect(image_view_, SIGNAL(mouse_position(int,int)), this, SLOT(status_show_position(int,int)));

    connect(tab_filter_->button_edge_detect_, SIGNAL(clicked()), this, SLOT(filter_edge_detect()));
    connect(tab_filter_->button_blur_, SIGNAL(clicked()), this, SLOT(filter_blur()));
    connect(tab_filter_->button_morphology_, SIGNAL(clicked()), this, SLOT(filter_morphology()));
    connect(tab_preprocess_->slider_threshold_, SIGNAL(valueChanged(int)), this, SLOT(pre_threshold()));
    connect(tab_preprocess_->button_threshold_, SIGNAL(clicked()), this, SLOT(pre_auto_threshold()));
    connect(tab_preprocess_->slider_threshold_optional_, SIGNAL(valueChanged(int)), this, SLOT(pre_dual_threshold()));
    connect(tab_preprocess_->button_turn_gray_, SIGNAL(clicked()), this, SLOT(pre_turn_gray()));
    connect(tab_filter_->button_mask_, SIGNAL(clicked()), this, SLOT(filter_morphology_mask()));
    connect(tab_filter_->slider_morphology_, SIGNAL(valueChanged(int)), this, SLOT(filter_morphology_watershed_mask()));
    connect(tab_preprocess_->button_split_overlay_, SIGNAL(clicked()), this, SLOT(pre_show_window_split_overlay()));
}

void MainWindow::save_file(){

}

void MainWindow::save_file_as(){

}

void MainWindow::close_file(){

}

void MainWindow::quit(){

}

void MainWindow::redo(){

}

void MainWindow::undo(){

}

void MainWindow::gray_linear_transform(){
    cv::Mat temp, se_mat;
    cv::Mat image = show_window_manager_->get_current_image();
    if(!image.empty()){
        if (image.channels() != 1){
            QMessageBox::warning(this, "Image Type Error", "Image is not single channel!");
        }else{
            int min_x = tab_gray_->spin_box_input_1_->value();
            int max_x = tab_gray_->spin_box_input_2_->value();
            int min_y = tab_gray_->spin_box_output_1_->value();
            int max_y = tab_gray_->spin_box_output_2_->value();
            ImageProcess::gray_linear_transform(image,
                                                temp,
                                                min_x, max_x, min_y, max_y);

            emit refresh_image_view();
            show_window_manager_->show_window(temp,
                                              __FUNCTION__ +                                               show_window_manager_->get_current_window_name(),
                                              check_box_create_new_window_->isChecked());
        }
    }

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
        cv::Mat temp;
        cv::Mat image = show_window_manager_->get_current_image();
        if(!image.empty()){
            if (image.channels() != 1){
                QMessageBox::warning(this, "Image Type Error", "Image is not single channel!");
            }else{

                if (tab_gray_->chart_non_linear_->fun_ != NULL){
                    ImageProcess::gray_fun_transform(image,
                                                     temp,
                                                     tab_gray_->chart_non_linear_->fun_);
                    show_window_manager_->show_window(temp,
                                                      __FUNCTION__ + show_window_manager_->get_current_window_name(),
                                                      check_box_create_new_window_->isChecked());
                }
            }
        }

        break;
    }
    default:
        break;
    }
}

void MainWindow::gray_histogram_display(){
     Function *fun  = ImageProcess::get_gray_histogram(
                 show_window_manager_->get_current_image(),
                 ImageProcess::FREQUENCE);
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
    cv::Mat temp;
    cv::Mat image = show_window_manager_->get_current_image();
    if(!image.empty()){
        if (image.channels() != 1){
            QMessageBox::warning(this, "Image Type Error", "Image is not single channel!");
        }else{
            Function *fun  = ImageProcess::get_gray_histogram(
                        image,
                        ImageProcess::FREQUENCE);
            if (!fun->ready()){
                delete fun;
                return;
            }
            Function *equal = ImageProcess::get_histogram_equalization_fun(fun);
            if (!equal->ready()){
                delete equal;
                return;
            }
            ImageProcess::gray_fun_transform(
                        image,
                        temp,
                        equal);
            show_window_manager_->show_window(temp,
                                              __FUNCTION__ + show_window_manager_->get_current_window_name(),
                                              check_box_create_new_window_->isChecked());
            gray_histogram_display();
            delete equal;
            delete fun;

        }
    }

}

void MainWindow::gray_histogram_match(){
    cv::Mat temp;
    cv::Mat image = show_window_manager_->get_current_image();
    if(!image.empty()){
        if (image.channels() != 1){
            QMessageBox::warning(this, "Image Type Error", "Image is not single channel!");
        }else{
            Function *origin = ImageProcess::get_gray_histogram(
                        image,
                        ImageProcess::FREQUENCE);
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
            ImageProcess::gray_fun_transform(image,
                                             temp,
                                             match);
            show_window_manager_->show_window(temp,
                                              __FUNCTION__ + show_window_manager_->get_current_window_name(),
                                              check_box_create_new_window_->isChecked());
            gray_histogram_display();
            delete match;
            delete origin;

        }
    }



}

void MainWindow::geometry_zoom(){
    ImageProcess::zoom_type type = ImageProcess::NEAREST;
    switch(tab_basic_->combo_zoom_->currentIndex()){
    case 0:
        type = ImageProcess::NEAREST;
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

void MainWindow::geometry_rotate(){
    cv::Mat temp;
    cv::Mat image = show_window_manager_->get_current_image();
    if(!image.empty()){
        if (image.type() != CV_8UC1 && image.type() != CV_8UC3){
            QMessageBox::warning(this, "Image Type Error", "Image type is not supported!");
        }else{
            ImageProcess::zoom_type type = tab_basic_->combo_zoom_->currentIndex();
            int degree = tab_basic_->spin_box_rotate_->value();
            ImageProcess::geometry_rotate(image, temp, degree, type);

            show_window_manager_->show_window(temp,
                                              __FUNCTION__ + show_window_manager_->get_current_window_name(),
                                              check_box_create_new_window_->isChecked());
        }
    }
}

void MainWindow::basic_algebra(){
   ImageProcess::algebra_type type = ImageProcess::ADD;
   switch(tab_basic_->combo_algebra_->currentIndex()){
   case 0:
       type = ImageProcess::ADD;
       break;
   case 1:
       type = ImageProcess::SUB;
       break;
   case 2:
       type = ImageProcess::MUL;
       break;
   case 3:
       type = ImageProcess::DIV;
   }
   FImage another;
   another.load(tab_basic_->label_algebra_pic_->text());
   ImageProcess::algebra(image_view_->image_data_, another, type);
   emit refresh_image_view();
}

void MainWindow::basic_algebra_pic(){
     QString file_name = QFileDialog::getOpenFileName(this);
     tab_basic_->label_algebra_pic_->setText(file_name);
}

void MainWindow::filter_morphology(){
    cv::Mat temp, se_mat;
    cv::Mat image = show_window_manager_->get_current_image();
    if(!image.empty()){
        if (image.channels() != 1){
            QMessageBox::warning(this, "Image Type Error", "Image is not single channel!");
        }else{
            tab_filter_->se_select_widget_morphology_->select_widget_->get_se_mat(se_mat);
            ImageProcess::morphology_transform(image,
                                               temp,
                                               this->tab_filter_->combo_box_morphology_->currentIndex(),
                                               se_mat,
                                               -1,
                                               -1);
            show_window_manager_->show_window(temp,
                                              __FUNCTION__ +                                               show_window_manager_->get_current_window_name(),
                                              check_box_create_new_window_->isChecked());
        }
    }
}

void MainWindow::filter_morphology_watershed_mask(){
    cv::Mat image = show_window_manager_->get_current_origin();
    if(!image.empty()){
        if (image.channels() != 1){
            QMessageBox::warning(this, "Image Type Error", "Image is not single channel!");
        }else{
            Mat se, seeds;
            tab_filter_->se_select_widget_morphology_->select_widget_->get_se_mat(se);
            Morphology::watershed_seeds(image, seeds, se, tab_filter_->slider_morphology_->value());
            seeds.copyTo(ImageProcess::morphology_mask());
            show_window_manager_->show_window(seeds, "watershed seeds", true, true);
        }
    }
}

void MainWindow::filter_morphology_mask(){
    cv::Mat image = show_window_manager_->get_current_image();
    if(!image.empty()){
        if (image.channels() != 1){
            QMessageBox::warning(this, "Image Type Error", "Image is not single channel!");
        }else{
            image.copyTo(ImageProcess::morphology_mask());
            show_window_manager_->show_window(ImageProcess::morphology_mask(),
                                              "mask",
                                              true);
        }
    }
}

void MainWindow::filter_blur(){
    cv::Mat temp;
    cv::Mat image = show_window_manager_->get_current_image();
    if(!image.empty()){
        if (image.channels() != 1){
            QMessageBox::warning(this, "Image Type Error", "Image is not single channel!");
        }else{
            ImageProcess::blur(image,
                               temp,
                               tab_filter_->combo_box_blur_->currentIndex(),
                               tab_filter_->spin_box_blur_size_->value(),
                               tab_filter_->double_spin_box_blur_sigma_->value());
            show_window_manager_->show_window(temp,
                                              __FUNCTION__ + show_window_manager_->get_current_window_name(),
                                              check_box_create_new_window_->isChecked());
        }
    }
}

void MainWindow::filter_edge_detect(){
    cv::Mat temp;
    cv::Mat image = show_window_manager_->get_current_image();
    if(!image.empty()){
        if (image.channels() != 1){
            QMessageBox::warning(this, "Image Type Error", "Image is not single channel!");
        }else{
            ImageProcess::edge_detect(image, temp, tab_filter_->combo_box_edge_detect_->currentIndex());
            show_window_manager_->show_window(temp,
                                              __FUNCTION__ + show_window_manager_->get_current_window_name(),
                                              check_box_create_new_window_->isChecked());
        }
    }
}

void MainWindow::pre_threshold(){
    cv::Mat temp;
    cv::Mat image = show_window_manager_->get_current_origin();
    if(!image.empty()){
        if (image.channels() != 1){
            QMessageBox::warning(this, "Image Type Error", "Image is not single channel!");
        }else{
            ImageProcess::threshold(image,
                                    temp,
                                    Miscellaneous::NORMAL_THRESHOLD,
                                    tab_preprocess_->slider_threshold_->value(),
                                    tab_preprocess_->slider_threshold_optional_->value());
            show_window_manager_->show_window(temp,
                                              __FUNCTION__ + show_window_manager_->get_current_window_name(),
                                              check_box_create_new_window_->isChecked(),
                                              true);
        }
    }
}

void MainWindow::pre_dual_threshold(){
    cv::Mat temp;
    cv::Mat image = show_window_manager_->get_current_origin();
    if(!image.empty()){
        if (image.channels() != 1){
            QMessageBox::warning(this, "Image Type Error", "Image is not single channel!");
        }else{
            ImageProcess::threshold(image,
                                    temp,
                                    Miscellaneous::DUAL_THRESHOLD,
                                    tab_preprocess_->slider_threshold_->value(),
                                    tab_preprocess_->slider_threshold_optional_->value());
            show_window_manager_->show_window(temp,
                                              __FUNCTION__ + show_window_manager_->get_current_window_name(),
                                              check_box_create_new_window_->isChecked(),
                                              true);
        }
    }
}

void MainWindow::pre_auto_threshold(){
    cv::Mat temp;
    cv::Mat image = show_window_manager_->get_current_image();
    if(!image.empty()){
        if (image.channels() != 1){
            QMessageBox::warning(this, "Image Type Error", "Image is not single channel!");
        }else{
            std::vector<double> p;
            p.push_back(0.5);
            unsigned char th = ImageProcess::auto_threshold(image,
                                                            temp,
                                                            tab_preprocess_->combo_box_threshold_->currentIndex(), p);
            tab_preprocess_->slider_threshold_->setValue(static_cast<int>(th));
            show_window_manager_->show_window(temp,
                                               __FUNCTION__ + show_window_manager_->get_current_window_name(),
                                              check_box_create_new_window_->isChecked(),
                                              true);
        }
    }
}

void MainWindow::pre_turn_gray(){
    Mat temp;
    Mat image = show_window_manager_->get_current_image();
    if (!image.empty()){
        if (image.channels() == 3){
            cvtColor(image, temp, CV_BGR2GRAY);
            show_window_manager_->show_window(temp,
                                               __FUNCTION__ + show_window_manager_->get_current_window_name(),
                                              check_box_create_new_window_->isChecked());
        }
    }else{
        QMessageBox::warning(this, "No Image File", "no image to process");
    }
}

void MainWindow::status_show_position(int x, int y){

    label_position_->setText(QString("(%1 , %2)").arg(x).arg(y));
}


void MainWindow::mouseMoveEvent(QMouseEvent *){
}

void MainWindow::show_window_clear_(){
    show_window_manager_->clear_drawing();
}

void MainWindow::pre_show_window_split_overlay(){
    Mat img = show_window_manager_->get_current_image();
    Mat overlay = show_window_manager_->get_current_overlay();
    if (img.empty() || overlay.empty()){
        QMessageBox::warning(this, "No Image File", "no image to process");
    }else{
        show_window_manager_->show_window(img, "origin" + show_window_manager_->get_current_window_name(), check_box_create_new_window_->isChecked());
        show_window_manager_->show_window(overlay, "overlay" + show_window_manager_->get_current_window_name(), true);
    }
}

void MainWindow::closeEvent(QCloseEvent *){
    exit(0);
}


