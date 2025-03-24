#ifndef _ANDGATE_H
#define _ANDGATE_H

#include "device.h"

namespace Nova {
namespace hardware {

class AndGate : public Device {
public:
    static const unsigned char PIN_A = 0;
    static const unsigned char PIN_B = 1;
    static const unsigned char PIN_DATA = 2;
public:
    AndGate() = default;
    AndGate(const AndGate&) = default;
    AndGate(AndGate &&) = default;

    AndGate& operator=(const AndGate&) = default;
    AndGate& operator=(AndGate&&) = default;

    virtual auto setInput(unsigned char pin, bool value, bool force = false) -> void override;

private:
    bool _a;
    bool _b;
};

}}

#endif // _ANDGATE_H