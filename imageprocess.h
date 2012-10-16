#ifndef IMAGEPROCESS_H
#define IMAGEPROCESS_H
#include "fimage.h"
#include "function.h"
#include "linearfunction.h"
class ImageProcess
{
public:
    ImageProcess();
    void gray_linear_transform(FImage &in, FImage &out, int x_min, int x_max, int y_min, int y_max);
    void gray_log_transform(FImage &in, FImage &out, double a, double b, double c);
    void gray_exponent_transform(FImage &in, FImage &out, double a, double b, double c);
private:
};

#endif // IMAGEPROCESS_H
