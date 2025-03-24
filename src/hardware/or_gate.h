#ifndef _ORGATE_H
#define _ORGATE_H

#include "device.h"

namespace Nova {
namespace hardware {

class OrGate : public Device {
public:
    static const unsigned char PIN_A = 0;
    static const unsigned char PIN_B = 1;
    static const unsigned char PIN_DATA = 2;
public:
    OrGate() = default;
    OrGate(const OrGate&) = default;
    OrGate(OrGate &&) = default;

    OrGate& operator=(const OrGate&) = default;
    OrGate& operator=(OrGate&&) = default;

    virtual auto setInput(unsigned char pin, bool value, bool force = false) -> void override;

private:
    bool _a;
    bool _b;
};

}}

#endif // _ORGATE_H