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
    void start_draw(int x, int y);
    void stop_draw(int x, int y);
    void draw(int x, int y);
    cv::Mat get_image();
    cv::Mat get_overlay();
    void clear_overlay();
private:
    std::string window_name_;
    cv::Mat image_;
    cv::Mat overlay_;
    ShowWindowManager* manager_;
    cv::Rect area_;
    bool drawing_;
    int last_x_;
    int last_y_;


};

#endif // SHOWWINDOW_H
