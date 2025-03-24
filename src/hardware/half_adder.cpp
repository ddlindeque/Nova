#include "half_adder.h"

#include <iostream>

namespace Nova {
namespace hardware {

#ifdef HALF_ADDER_BY_CONSTRUCTION

auto HalfAdder::setInput(unsigned char pin, bool value, bool force) -> void
{
    switch(pin) {
        case PIN_A:
            _xor.setInput(XorGate::PIN_A, value, force);
            _and.setInput(AndGate::PIN_A, value, force);
            break;
        case PIN_B:
            _xor.setInput(XorGate::PIN_B, value, force);
            _and.setInput(AndGate::PIN_B, value, force);
            break;
        default:
            std::cerr << "HalfAdder::setInput - Writing to illegal pin " << static_cast<int>(pin) << std::endl;
            exit(1);
            break;
    }
}

auto HalfAdder::registerListener(unsigned char pin, const Listener &handler) -> void
{
    switch(pin) {
        case PIN_DATA:
            _xor.registerListener(XorGate::PIN_DATA, handler);
            break;
        case PIN_CARRY:
            _and.registerListener(AndGate::PIN_DATA, handler);
            break;
        default:
            std::cerr << "HalfAdder::registerListener - Listening to illegal pin " << static_cast<int>(pin) << std::endl;
            exit(1);
            break;
    }
}

#else

auto HalfAdder::setInput(unsigned char pin, bool value, bool force) -> void
{
    //std::cout << "HalfAdder::setInput - Setting pin " << static_cast<int>(pin) << " to " << value << std::endl;
    bool cur_data = _a ^ _b, cur_carry = _a && _b;
    switch(pin) {
        case PIN_A:
            _a = value;
            break;
        case PIN_B:
            _b = value;    
            break;
        default:
            std::cerr << "HalfAdder::setInput - Writing to illegal pin " << static_cast<int>(pin) << std::endl;
            exit(1);
            break;
    }
    bool new_data = _a ^ _b, new_carry = _a && _b;
    if (force || cur_data != new_data) {
        updateOutput(PIN_DATA, new_data, force);
    }
    if (force || cur_carry != new_carry) {
        updateOutput(PIN_CARRY, new_carry, force);
    }
}

#endif // HALF_ADDER_BY_CONSTRUCTION

}}