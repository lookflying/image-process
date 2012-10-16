#ifndef LINEARFUNCTION_H
#define LINEARFUNCTION_H

#include "function.h"
#include <map>
#include <vector>

class LinearFunction:public Function
{
public:
    explicit LinearFunction();
    explicit LinearFunction(int min_in, int max_in, int min_out, int max_out, int gran = 1);
    ~LinearFunction();
    void set(int in, int out);
//    bool get(int in, int& out);
    void remove(int in);
private:
    int granularity_;
    std::map<int, int> parameters_;
};

#endif // LINEARFUNCTION_H
