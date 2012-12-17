#ifndef MORPHOLOGY_H
#define MORPHOLOGY_H
#include <opencv2/core/core.hpp>
class Morphology
{
public:
    enum morphology_type{EROSION_BINARY,
                         DILATION_BINARY,
                         OPENING_BINARY,
                         CLOSING_BINARY,
                         DISTANCE_TRANSFORM,
                         SKELETONIZATION,
                         RESTORATION,
                         CONDITIONAL_DILATION,
                         EROSION_GRAYSCALE,
                         DILATION_GRAYSCALE,
                         OPENING_GRAYSCALE,
                         CLOSING_GRAYSCALE,
                         EDGE_STANDARD,
                         EDGE_EXTERNAL,
                         EDGE_INTERNAL,
                         GRAYSCALE_RECONSTRUCTION,
                         GRADIENT,
                         GRADIENT_EXTERNAL,
                         GRADIENT_INTERNAL,
                         WATERSHED
                        };
    static const uchar distance_metric_[];
    typedef int morphology_type_t;
    //assume to be binary image
    static void run(cv::Mat &src, cv::Mat &dst, morphology_type_t type, cv::Mat se, cv::Mat mask, int center_x = -1, int center_y = - 1);
    static uchar erosion_action_binary(cv::Mat& input, cv::Mat& se);
    static uchar dilation_action_binary(cv::Mat& input, cv::Mat& se);
    static uchar erosion_action_grayscale(cv::Mat& input, cv::Mat& se);
    static uchar dilation_action_grayscale(cv::Mat& input, cv::Mat& se);
    static uchar watershed_action_flood(cv::Mat &input, cv::Mat &input2, cv::Mat& se);
    static int watershed_action_find_minimum(cv::Mat &input, cv::Mat &input2, cv::Mat& se);

    enum structing_element_type{DISC,
                                CUBE,
                                CROSS};
    typedef int structing_element_type_t;

    static cv::Mat generate_structing_element(int width = 3, int height = 3, structing_element_type_t type = DISC);
    static void cut_black_edge(cv::Mat in, cv::Mat &out);
private:
};

#endif // MORPHOLOGY_H
