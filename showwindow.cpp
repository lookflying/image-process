#include "showwindow.h"
#include "highgui.h"
#include "showwindowmanager.h"
using namespace cv;
static void on_mouse(int event, int x, int y, int, void* p){
    ShowWindow* window = (ShowWindow*) p;
    if (event == CV_EVENT_LBUTTONDOWN){
        window->notify_manager();
        window->start_draw(x, y);
    }else if (event == CV_EVENT_LBUTTONUP){
        window->stop_draw(x, y);
    }else if (event == CV_EVENT_MOUSEMOVE){
        window->draw(x, y);
        window->show();
    }
}

ShowWindow::ShowWindow(std::string name, Mat &image, ShowWindowManager *manager)
{
    window_name_ = name;
    drawing_ = false;
    image.copyTo(image_);
    manager_ = manager;
    area_ = Rect(0, 0, image_.cols, image_.rows);
    namedWindow(window_name_);
    setMouseCallback(window_name_, on_mouse, (void*)this);
    imshow(window_name_, image_);
    overlay_ = Mat(image_.rows, image_.cols, CV_8UC3, Scalar(0, 0, 0));
    last_x_ = last_y_ = -1;
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

Mat ShowWindow::get_overlay(){
    return overlay_;
}

void ShowWindow::update_image(Mat image){
    image.copyTo(image_);
    imshow(window_name_, image_);
}

void ShowWindow::preview(Mat image){
    imshow(window_name_, image);
}

void ShowWindow::show(){
    imshow(window_name_, max(image_, overlay_));
}

void ShowWindow::start_draw(int x, int y){
    last_x_ = -1;
    last_y_ = -1;
    drawing_ = true;

}

void ShowWindow::stop_draw(int x, int y){
	drawing_ = false;
}

void ShowWindow::draw(int x, int y){
	if (drawing_){
		if (last_x_ < 0 || last_y_ < 0){
			last_x_ = x;
			last_y_ = y;
		}
		if (x < image_.cols && x >=0 && y < image_.rows && y >= 0){
			line(overlay_, Point(last_x_, last_y_), Point(x, y), Scalar(255, 255, 255), 4);
			last_x_ = x;
			last_y_ = y;
		}

	}
}


