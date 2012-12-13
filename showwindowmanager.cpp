#include "showwindowmanager.h"
using namespace cv;
using namespace std;
ShowWindowManager::ShowWindowManager()
{
    action_ = NULL;
    ui_ = NULL;
    current_window_ == "";
}

ShowWindowManager::~ShowWindowManager(){
    for (map<string, ShowWindow*>::iterator it = windows_.begin(); it != windows_.end(); ++it){
        delete it->second;
    }
    windows_.clear();
}

void ShowWindowManager::on_notify(string name, cv::Rect area){
    if (action_ != NULL && ui_ != NULL && windows_.find(name) != windows_.end()){
//        Mat temp;
//        windows_[name]->get_image()(area).copyTo(temp);
//        (*action_)(temp, ui_, name);
        current_window_ = name;
        current_area_ = area;
        windows_[name]->get_image().copyTo(current_origin_);
    }
}



void ShowWindowManager::set_refresh_action(show_window_refresh_action *action){
    action_ = action;
}

void ShowWindowManager::set_ui(QWidget *ui){
    ui_ = ui;
}

void ShowWindowManager::show_window( Mat image, string name, bool create_new, bool preview){
    if (create_new || current_window_.compare("") == 0){
        if (windows_.find(name) != windows_.end()){
            windows_[name]->update_image(image);
        }else{
            windows_[name] = new ShowWindow(name, image, this);
        }
        current_window_ = name;
    }else{
        windows_[current_window_]->update_image(image);
    }
    if (!preview){
        image.copyTo(current_origin_);
    }
}


Mat ShowWindowManager::get_current_image(){
    if (current_window_.compare("") != 0 && windows_.find(current_window_) != windows_.end()){
        return windows_[current_window_]->get_image();
    }else{
        return Mat();
    }
}

Mat ShowWindowManager::get_current_origin(){
    if (current_origin_.empty()){
        return Mat();
    }else{
        return current_origin_;
    }
}

string ShowWindowManager::get_current_window_name(){
    return current_window_;
}
