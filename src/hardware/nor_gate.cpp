#include "nor_gate.h"

#include <iostream>

namespace Nova {
namespace hardware {

auto NorGate::setInput(unsigned char pin, bool value, bool force) -> void
{
    //std::cout << "NorGate::setInput - Setting pin " << static_cast<int>(pin) << " to " << value << std::endl;
    bool cur = !(_a || _b);
    switch(pin) {
        case PIN_A:
            _a = value;
            break;
        case PIN_B:
            _b = value;    
            break;
        default:
            std::cerr << "NorGate::setInput - Writing to illegal pin " << static_cast<int>(pin) << std::endl;
            exit(1);
            break;
    }
    bool v = !(_a || _b);
    if (force || cur != v) {
        updateOutput(PIN_DATA, v, force);
    }
}

}}