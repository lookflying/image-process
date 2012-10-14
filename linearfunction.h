#ifndef LINEARFUNCTION_H
#define LINEARFUNCTION_H

#include <map>
#include <vector>

class LinearFunction
{
public:
    explicit LinearFunction();
    explicit LinearFunction(int min_in, int max_in, int min_out, int max_out, int gran = 1);
    ~LinearFunction();
    void set(int in, int out);
    bool get(int in, int& out);
    void remove(int in);
private:
    int min_in_;
    int max_in_;
    int min_out_;
    int max_out_;
    int granularity_;
    std::map<int, int> parameters_;
    std::vector<int> data_;
    bool ready_;
};

#endif // LINEARFUNCTION_H
