#ifndef GATES_OR
#define GATES_OR
#include <functional>

/*
Say /\/ is a resistor, and [ is a transistor (with collector at top), | and - are wires

             +---+---VCC
             |   |
A--/\/------[    |
             |   |
         +---|---+
         |   |
B--/\/--[    |
         |   |
         +---+---Output
         |
         +---/\/--GND
*/

struct gate_or {
    void operator()(bool input1, bool input2, const std::function<void(bool)> &callback) { callback(input1 || input2); }
};
#endif