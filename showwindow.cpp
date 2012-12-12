#include "showwindow.h"
#include "highgui.h"
#include "showwindowmanager.h"
using namespace cv;
static void on_mouse(int, int, int, int, void* p){
    ((ShowWindow*)p)->notify_manager();
}

ShowWindow::ShowWindow(std::string name, Mat &image, ShowWindowManager *manager)
{
    window_name_ = name;
    image.copyTo(image_);
    manager_ = manager;
    area_ = Rect(0, 0, image_.cols, image_.rows);
    namedWindow(window_name_);
    setMouseCallback(window_name_, on_mouse, (void*)this);
    imshow(window_name_, image_);
}
ShowWindow::~ShowWindow(){
    image_.release();
}


void ShowWindow::notify_manager(){
    manager_->on_notify(window_name_, area_);
}



Mat ShowWindow::get_image(){
    return image_;
}

void ShowWindow::update_image(Mat image){
    image.copyTo(image_);
    imshow(window_name_, image_);
}

void ShowWindow::preview(Mat image){
    imshow(window_name_, image);
}

void ShowWindow::show(){
    imshow(window_name_, image_);
}

