#ifndef SHOWWINDOW_H
#define SHOWWINDOW_H
#include <string>
#include <opencv2/core/core.hpp>
class ShowWindowManager;
class ShowWindow
{
public:
    ShowWindow(std::string name, cv::Mat &image, ShowWindowManager* manager);
    ~ShowWindow();
    void notify_manager();
    void update_image(cv::Mat image);
    void preview(cv::Mat image);
    void show();
    cv::Mat get_image();
private:
    std::string window_name_;
    cv::Mat image_;
    ShowWindowManager* manager_;
    cv::Rect area_;

};

#endif // SHOWWINDOW_H
