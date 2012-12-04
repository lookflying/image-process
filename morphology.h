#ifndef MORPHOLOGY_H
#define MORPHOLOGY_H
#include <opencv2/core/core.hpp>
class Morphology
{
public:
    enum morphology_type{EROSION,
                         DILATION,
                         OPENING,
                         CLOSING,
                         DISTANCE_TRANSFORM,
                         SKELETONIZATION,
                         RESTORATION};
    static const uchar distance_metric_[];
    typedef int morphology_type_t;
    //assume to be binary image
    static void run(cv::Mat &src, cv::Mat &dst, morphology_type_t type, cv::Mat se, int center_x = -1, int center_y = - 1);
    static uchar erosion_action(cv::Mat& input, cv::Mat& se);
    static uchar dilation_action(cv::Mat& input, cv::Mat& se);
    enum structing_element_type{DISC,
                                CUBE,
                                CROSS};
    typedef int structing_element_type_t;

    static cv::Mat generate_structing_element(int width = 3, int height = 3, structing_element_type_t type = DISC);
    static void cut_black_edge(cv::Mat in, cv::Mat &out);
private:
};

#endif // MORPHOLOGY_H
