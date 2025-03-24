#include "not_gate.h"

#include <iostream>

namespace Nova {
namespace hardware {

auto NotGate::setInput(unsigned char pin, bool value, bool force) -> void
{
    //std::cout << "NotGate::setInput - Setting pin " << static_cast<int>(pin) << " to " << value << std::endl;
    bool cur = !_input;
    switch(pin) {
        case PIN_INPUT:
            _input = value;
            break;
        default:
            std::cerr << "NotGate::setInput - Writing to illegal pin " << static_cast<int>(pin) << std::endl;
            exit(1);
            break;
    }
    if (force || cur == _input) {
        updateOutput(PIN_DATA, !_input, force);
    }
}

}}