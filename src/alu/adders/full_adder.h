#ifndef ALU_ADDERS_FULL_ADDER
#define ALU_ADDERS_FULL_ADDER
#include <functional>

#include <gate_xor.h>
#include <gate_and.h>
#include <gate_or.h>

/*
    (with C = previous carry)
    C + A + B
    0 + 0 + 0 = 0 carry 0
    0 + 0 + 1 = 1 carry 0
    0 + 1 + 0 = 1 carry 0
    0 + 1 + 1 = 0 carry 1    (carry = !CAB)
    1 + 0 + 0 = 1 carry 0
    1 + 0 + 1 = 0 carry 1    (carry = C(A|B))
    1 + 1 + 0 = 0 carry 1
    1 + 1 + 1 = 1 carry 1

    a b c  a xor b xor c  digit
    0 0 0     0     0       0
    0 0 1     0     1       1
    0 1 0     1     1       1
    0 1 1     1     0       0
    1 0 0     1     1       1
    1 0 1     1     0       0
    1 1 0     0     0       0
    1 1 1     0     1       1

    digit = A xor B xor C

    carry = (A & B) | ((A xor B) & C)
*/

struct full_adder
{
    void operator()(bool input1, bool input2, bool prev_carry, const std::function<void(bool, bool)> &callback) {
        bool axorb;
        gate_xor()(input1, input2, [&axorb](const bool &r) { axorb=r; });
        bool digit;
        gate_xor()(axorb, prev_carry, [&digit](const bool &r) {digit = r;});

        bool aandb;
        gate_and()(input1, input2, [&aandb](const bool &r) { aandb=r; });
        bool axorbandc;
        gate_and()(axorb, prev_carry, [&axorbandc](const bool &r){ axorbandc=r; });

        gate_or()(aandb, axorbandc, [&digit, &callback](const bool &r){callback(digit, r);});
    }
};
#endif