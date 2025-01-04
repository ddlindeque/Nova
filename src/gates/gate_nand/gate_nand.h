#ifndef GATES_NAND
#define GATES_NAND
#include <functional>

/*
Say /\/ is a resistor, and [ is a transistor (with collector at top), | and - are wires

         +---/\/--VCC
         |
         +--- Output = !(A & B)
         |
A--/\/--[
         |
B--/\/--[
         |
        GND 
*/

struct gate_nand {
    void operator()(bool input1, bool input2, const std::function<void(bool)> &callback) { callback(!(input1 && input2)); }
};
#endif