#include "logfunction.h"
#include <cassert>
#include <cmath>


LogFunction::LogFunction(int min_in, int max_in, int min_out, int max_out, double a, double b, double c):
    Function(min_in, max_in, min_out, max_out)
{
    assert( c > 0 && c != 1 && b != 0);
    a_ = a;
    b_ = b;
    c_ = c;
    setValue(a_, b_, c_);
}

LogFunction::LogFunction()
{
}

void LogFunction::setValue(double a, double b, double c){
    if (!ready_)
        return;
    double bottom = b * log(c);
    for (unsigned int i = 0; i <data_.size(); ++i){
        int value = static_cast<int>(a + log(min_in_ + (int) i + 1) / bottom);
        if (value < min_out_)
            value = min_out_;
        else if(value > max_out_)
            value = max_out_;
        data_[i] = value;
    }
}
