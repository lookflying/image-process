#include "function.h"
#include <cassert>
#include <cstring>
#include <cstdio>
using namespace std;
Function::Function(){
    ready_ = false;
}

Function::Function(int min_in, int max_in, int min_out, int max_out)
{
    assert(min_in < max_in && min_out <= max_out);
    min_in_ = min_in;
    max_in_ = max_in;
    min_out_ = min_out;
    max_out_ = max_out;
    data_.resize(max_in - min_in + 1);
    for (unsigned int i = 0; i < data_.size(); ++i){
        data_[i] = min_out_;
    }
    ready_ = true;

}

Function::~Function(){
    data_.clear();
}

void Function::set(int in, int out){
    assert(ready_);
     if (in < min_in_ || in > max_in_ || out < min_out_ || out > max_out_)
         return;
     data_[in] = out;
}

int Function::get(int in){
    assert(ready_);
    assert(in >= min_in_ && in <= max_in_);
    return data_[in];
}
