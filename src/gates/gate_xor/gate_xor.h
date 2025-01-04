#ifndef GATES_XOR
#define GATES_XOR
#include <functional>

/*
A  B  XOR
0  0  0
0  1  1
1  0  1
1  1  1

X = !(A&B)

A B X
0 0 1
0 1 1
1 0 1
1 1 0

Y = !(A&X)

A B X Y
0 0 1 1
0 1 1 1
1 0 1 0
1 1 0 1

Z = !(B&X)

A B X Z
0 0 1 1
0 1 1 0
1 0 1 1
1 1 0 1

Output = !(Y&Z)

A B Y Z Output
0 0 1 1 0
0 1 1 0 1
1 0 0 1 1
1 1 1 1 0
*/

#include <gate_nand.h>

struct gate_xor {
    void operator()(bool input1, bool input2, const std::function<void(bool)> &callback) { 
        bool x, y, z;
        gate_nand()(input1, input2, [&x](const auto &r){x = r;});
        gate_nand()(input1, x, [&y](const auto &r){y = r;});
        gate_nand()(input2, x, [&z](const auto &r){z = r;});
        gate_nand()(y,z, callback);
    }
};
#endif