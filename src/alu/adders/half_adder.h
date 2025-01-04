#ifndef ALU_ADDERS_HALF_ADDER
#define ALU_ADDERS_HALF_ADDER
#include <functional>

#include <gate_xor.h>
#include <gate_and.h>

/*
    A + B
    0 + 0 = 0 carry 0
    0 + 1 = 1 carry 0
    1 + 0 = 1 carry 0
    1 + 1 = 0 carry 1

    digit = A xor B
    carry = A and B
*/

struct half_adder
{
    void operator()(bool input1, bool input2, const std::function<void(bool, bool)> &callback) {
        bool digit, carry;
        gate_xor()(input1, input2, [&digit](const bool &r){digit = r;});
        gate_and()(input1, input2, [&carry](const bool &r){carry = r;});
        callback(digit, carry);
    }
};
#endif