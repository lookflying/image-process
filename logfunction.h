#ifndef LOGFUNCTION_H
#define LOGFUNCTION_H
#include "function.h"
class LogFunction : public Function
{
public:
    static const int e = 2.71828;
    LogFunction(int min_in, int max_in, int min_out, int max_out, double a = 0, double b = 1, double c = e);
    LogFunction();
    void setValue(double a, double b, double c);
private:
    double a_;
    double b_;
    double c_;
};

#endif // LOGFUNCTION_H
