#ifndef FUNCTION_H
#define FUNCTION_H

#include <vector>
class Function
{
public:
    Function();
    Function(int min_in, int max_in, int min_out, int max_out);
    ~Function();
    void set(int in, int out);
    int get(int in);
protected:
    int min_in_;
    int max_in_;
    int min_out_;
    int max_out_;
    bool ready_;
    std::vector<int> data_;
private:


};

#endif // FUNCTION_H
