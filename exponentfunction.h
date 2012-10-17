#ifndef EXPONENTFUNCTION_H
#define EXPONENTFUNCTION_H

#include "function.h"
class ExponentFunction : public Function
{
public:
    ExponentFunction(int min_in, int max_in, int min_out, int max_out, double a = 0, double b = 0, double c = 0);
    ExponentFunction();
    void setValue(double a, double b, double c);
private:
    double a_;
    double b_;
    double c_;
};

#endif // EXPONENTFUNCTION_H
