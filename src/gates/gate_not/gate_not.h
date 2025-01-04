#ifndef GATES_NOT
#define GATES_NOT
#include <functional>

/*
A  Not
0  1
1  0

A A Nand(A,A)
0 0 1
1 1 0
*/

#include <gate_nand.h>

struct gate_not {
    void operator()(bool input, const std::function<void(bool)> &callback) { 
        gate_nand()(input, input, callback);
    }
};
#endif