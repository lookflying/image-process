#include "linearfunction.h"
#include <cassert>
#include <cstdio>
using namespace std;
LinearFunction::LinearFunction(int min_in, int max_in, int min_out, int max_out, int gran){
    assert(min_in < max_in && min_out <= max_out);
    min_in_ = min_in;
    max_in_ = max_in;
    min_out_ = min_out;
    max_out_ = max_out;
    data_.resize(max_in - min_in + 1);
    parameters_[min_in_] = min_out_;
    parameters_[max_out_] = min_out_;
    granularity_ = gran;
    for (unsigned int i = 0; i < data_.size(); ++i){
        data_[i] = min_out_;
    }
    ready_ = true;
}

LinearFunction::LinearFunction(){
    ready_ = false;
}

LinearFunction::~LinearFunction(){
    data_.clear();
    parameters_.clear();
}

void LinearFunction::set(int in, int out){
    assert(ready_);
    if (in < min_in_ || in > max_in_ + granularity_ -1|| out < min_out_ || out > max_out_)
        return;
    in = in / granularity_ * granularity_;
    if (parameters_.find(in) != parameters_.end() && parameters_[in] == out){
        return;
    }
    parameters_[in] = out;
    int pre_in = min_in_;
    int pre_out = parameters_[min_in_];
    int post_in = max_in_;
    int post_out = parameters_[min_out_];
    if (in == min_in_){
        map<int, int>::iterator it;
        it = parameters_.begin();
        it++;
        post_in = (*it).first;
        post_out = (*it).second;
        for (int i = 1; i <= post_in - in; ++i){
            data_[i] = out + (post_out - out) * i / (post_in - in);
        }
    }else if (in == max_in_){
        map<int, int>::reverse_iterator rit;
        rit = parameters_.rbegin();
        rit++;
        pre_in = (*rit).first;
        pre_out = (*rit).second;
        for (int i = pre_in - min_in_ ; i <= in - min_in_; ++i){
            data_[i] = pre_out + (out - pre_out) * (i -pre_in + min_in_)/ (in - pre_in);
        }
    }else{
        for (map<int, int>::iterator it = parameters_.begin(); it != parameters_.end(); ++it){
            if ((*it).first < in){
                pre_in = (*it).first;
                pre_out = (*it).second;
                continue;
            }
            if((*it).first > in){
                post_in = (*it).first;
                post_out = (*it).second;
                break;
            }
        }
        for (int i = pre_in - min_in_ + 1; i <= in - min_in_; ++i){
            data_[i] = pre_out + (out - pre_out) * (i - pre_in + min_in_) / (in - pre_in);
        }
        for (int i = in - min_in_ + 1; i < post_in - min_in_; ++i){
            data_[i] = out + (post_out - out) * (i - in + min_in_) / (post_in - in);
        }
    }

//    for ( unsigned int i = 0; i < data_.size() ;i ++){

//        printf("%3d %3d\n",i, data_[i]);
//    }
//    printf("\n");
//    fflush(stdout);

}

bool LinearFunction::get(int in, int& out){
    assert(ready_);
    if (in < min_in_ || in > max_in_ ){
        return false;
    }else{
        out = data_[in - min_in_];
        return true;
    }
}

void LinearFunction::remove(int in){
    assert(ready_);
    if (in == min_in_ || in == max_in_ || parameters_.find(in) == parameters_.end()){
        return;
    }else{
        parameters_.erase(in);
    }
    int pre_in = min_in_;
    int pre_out = parameters_[min_in_];
    int post_in = max_in_;
    int post_out = parameters_[max_out_];
    map<int, int>::iterator it;
    for (it = parameters_.begin(); it != parameters_.end(); ++it){
        if ((*it).first < in){
            pre_in = (*it).first;
            pre_out = (*it).second;
            continue;
        }
        if((*it).first > in){
            post_in = (*it).first;
            post_out = (*it).second;
            break;
        }
    }
    for (unsigned int i = (unsigned int)(pre_in - min_in_ + 1);
         i < (unsigned int)(post_in - min_in_);
         ++i){
        data_[i] = pre_out + (post_out - pre_out) * (i - pre_in + min_in_) / (post_in - pre_in);
    }

}
