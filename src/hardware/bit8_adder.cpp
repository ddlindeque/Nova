#include "bit8_adder.h"

#include <iostream>

namespace Nova {
namespace hardware {

Bit8Adder::Bit8Adder()
{
    _data0.registerListener(HalfAdder::PIN_CARRY, [this](bool value, bool force){ this->_data1.setInput(FullAdder::PIN_CIN, value, force); });
    _data1.registerListener(FullAdder::PIN_CARRY, [this](bool value, bool force){ this->_data2.setInput(FullAdder::PIN_CIN, value, force); });
    _data2.registerListener(FullAdder::PIN_CARRY, [this](bool value, bool force){ this->_data3.setInput(FullAdder::PIN_CIN, value, force); });
    _data3.registerListener(FullAdder::PIN_CARRY, [this](bool value, bool force){ this->_data4.setInput(FullAdder::PIN_CIN, value, force); });
    _data4.registerListener(FullAdder::PIN_CARRY, [this](bool value, bool force){ this->_data5.setInput(FullAdder::PIN_CIN, value, force); });
    _data5.registerListener(FullAdder::PIN_CARRY, [this](bool value, bool force){ this->_data6.setInput(FullAdder::PIN_CIN, value, force); });
    _data6.registerListener(FullAdder::PIN_CARRY, [this](bool value, bool force){ this->_data7.setInput(FullAdder::PIN_CIN, value, force); });
}

auto Bit8Adder::setInput(unsigned char pin, bool value, bool force) -> void
{
    switch(pin) {
        case PIN_A0:
            _data0.setInput(HalfAdder::PIN_A, value, force);
            break;
        case PIN_A1:
            _data1.setInput(FullAdder::PIN_A, value, force);
            break;
        case PIN_A2:
            _data2.setInput(FullAdder::PIN_A, value, force);
            break;
        case PIN_A3:
            _data3.setInput(FullAdder::PIN_A, value, force);
            break;
        case PIN_A4:
            _data4.setInput(FullAdder::PIN_A, value, force);
            break;
        case PIN_A5:
            _data5.setInput(FullAdder::PIN_A, value, force);
            break;
        case PIN_A6:
            _data6.setInput(FullAdder::PIN_A, value, force);
            break;
        case PIN_A7:
            _data7.setInput(FullAdder::PIN_A, value, force);
            break;
        case PIN_B0:
            _data0.setInput(HalfAdder::PIN_B, value, force);
            break;
        case PIN_B1:
            _data1.setInput(FullAdder::PIN_B, value, force);
            break;
        case PIN_B2:
            _data2.setInput(FullAdder::PIN_B, value, force);
            break;
        case PIN_B3:
            _data3.setInput(FullAdder::PIN_B, value, force);
            break;
        case PIN_B4:
            _data4.setInput(FullAdder::PIN_B, value, force);
            break;
        case PIN_B5:
            _data5.setInput(FullAdder::PIN_B, value, force);
            break;
        case PIN_B6:
            _data6.setInput(FullAdder::PIN_B, value, force);
            break;
        case PIN_B7:
            _data7.setInput(FullAdder::PIN_B, value, force);
            break;
        default:
            std::cerr << "Bit8Adder::setInput - Writing to illegal pin " << static_cast<int>(pin) << std::endl;
            exit(1);
            break;
    }
}

auto Bit8Adder::registerListener(unsigned char pin, const Listener &handler) -> void
{
    switch(pin) {
        case PIN_DATA0:
            _data0.registerListener(HalfAdder::PIN_DATA, handler);
            break;
        case PIN_DATA1:
            _data1.registerListener(FullAdder::PIN_DATA, handler);
            break;
        case PIN_DATA2:
            _data2.registerListener(FullAdder::PIN_DATA, handler);
            break;
        case PIN_DATA3:
            _data3.registerListener(FullAdder::PIN_DATA, handler);
            break;
        case PIN_DATA4:
            _data4.registerListener(FullAdder::PIN_DATA, handler);
            break;
        case PIN_DATA5:
            _data5.registerListener(FullAdder::PIN_DATA, handler);
            break;
        case PIN_DATA6:
            _data6.registerListener(FullAdder::PIN_DATA, handler);
            break;
        case PIN_DATA7:
            _data7.registerListener(FullAdder::PIN_DATA, handler);
            break;
        case PIN_CARRY:
            _data7.registerListener(FullAdder::PIN_CARRY, handler);
            break;
        default:
            std::cerr << "FullAdder::registerListener - Listening to illegal pin " << static_cast<int>(pin) << std::endl;
            exit(1);
            break;
    }
}

}}