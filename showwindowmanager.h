#ifndef SHOWWINDOWMANAGEMENT_H
#define SHOWWINDOWMANAGEMENT_H
#include <map>
#include <string>
#include <showwindow.h>
#include <QWidget>

typedef void show_window_refresh_action(cv::Mat img, QWidget *ui, std::string window_name);
class ShowWindowManager
{
public:
    ShowWindowManager();
    ~ShowWindowManager();
    void on_notify(std::string name, cv::Rect area);
    void set_refresh_action(show_window_refresh_action *action);
    void set_ui(QWidget *ui);
    void show_window(cv::Mat image, std::string name = "", bool create_new = false, bool preview = false);
    cv::Mat get_current_image();
    cv::Mat get_current_origin();
    std::string get_current_window_name();
private:
    std::map<std::string, ShowWindow*> windows_;
    show_window_refresh_action *action_;
    QWidget *ui_;
    std::string current_window_;
    cv::Rect current_area_;
    cv::Mat current_origin_;//for the process which needs preview
};

#endif // SHOWWINDOWMANAGEMENT_H
