#include "full_adder.h"

#include <iostream>

namespace Nova {
namespace hardware {

/*

a   b   cin     data    carry       a^b     (a^b)^cin   a&b     (a^b)&cin
0   0   0       0       0           0       0           0       0
0   0   1       1       0           0       1           0       0
0   1   0       1       0           1       1           0       0
0   1   1       0       1           1       0           0       1
1   0   0       1       0           1       1           0       0
1   0   1       0       1           1       0           0       1
1   1   0       0       1           0       0           1       0
1   1   1       1       1           0       1           1       0



*/

#ifdef FULL_ADDER_BY_CONSTRUCTION

FullAdder::FullAdder()
{
    // register the callbacks
    _a_xor_b.registerListener(XorGate::PIN_DATA, [this](bool value, bool force) { 
        this->_a_xor_b_xor_cin.setInput(XorGate::PIN_A, value, force);
        this->_a_xor_b_and_cin.setInput(AndGate::PIN_A, value, force);
    });
    _a_and_b.registerListener(AndGate::PIN_DATA, [this](bool value, bool force) {
        this->__a_xor_b_and_cin__or__a_and_b.setInput(OrGate::PIN_B, value, force);
    });
    _a_xor_b_and_cin.registerListener(AndGate::PIN_DATA, [this](bool value, bool force) {
        this->__a_xor_b_and_cin__or__a_and_b.setInput(OrGate::PIN_A, value, force);
    });
}

auto FullAdder::setInput(unsigned char pin, bool value, bool force) -> void
{
    switch(pin) {
        case PIN_A:
            _a_xor_b.setInput(XorGate::PIN_A, value, force);
            _a_and_b.setInput(AndGate::PIN_A, value, force);
            break;
        case PIN_B:
            _a_xor_b.setInput(XorGate::PIN_B, value, force);
            _a_and_b.setInput(AndGate::PIN_B, value, force);
            break;
        case PIN_CIN:
            _a_xor_b_xor_cin.setInput(XorGate::PIN_B, value, force);
            _a_xor_b_and_cin.setInput(AndGate::PIN_B, value, force);
            break;
        default:
            std::cerr << "FullAdder::setInput - Writing to illegal pin " << static_cast<int>(pin) << std::endl;
            exit(1);
            break;
    }
}

auto FullAdder::registerListener(unsigned char pin, const Listener &handler) -> void
{
    switch(pin) {
        case PIN_DATA:
            _a_xor_b_xor_cin.registerListener(XorGate::PIN_DATA, handler);
            break;
        case PIN_CARRY:
            __a_xor_b_and_cin__or__a_and_b.registerListener(OrGate::PIN_DATA, handler);
            break;
        default:
            std::cerr << "FullAdder::registerListener - Listening to illegal pin " << static_cast<int>(pin) << std::endl;
            exit(1);
            break;
    }
}

#else

auto FullAdder::setInput(unsigned char pin, bool value, bool force) -> void
{
    //std::cout << "FullAdder::setInput - Setting pin " << static_cast<int>(pin) << " to " << value << std::endl;
    bool cur_axorb = _a ^ _b;
    bool cur_data = cur_axorb ^ _cin, cur_carry = (cur_axorb && _cin) || (_a && _b);
    switch(pin) {
        case PIN_A:
            _a = value;
            break;
        case PIN_B:
            _b = value;    
            break;
        case PIN_CIN:
            _cin = value;
            break;
        default:
            std::cerr << "FullAdder::setInput - Writing to illegal pin " << static_cast<int>(pin) << std::endl;
            exit(1);
            break;
    }
    bool new_axorb = _a ^ _b;
    bool new_data = new_axorb ^ _cin, new_carry = (new_axorb && _cin) || (_a && _b);
    if (force || cur_data != new_data) {
        updateOutput(PIN_DATA, new_data, force);
    }
    if (force || cur_carry != new_carry) {
        updateOutput(PIN_CARRY, new_carry, force);
    }
}

#endif // FULL_ADDER_BY_CONSTRUCTION

}}