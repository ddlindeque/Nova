#ifndef _XORGATE_H
#define _XORGATE_H

#include "device.h"

namespace Nova {
namespace hardware {

class XorGate : public Device {
public:
    static const unsigned char PIN_A = 0;
    static const unsigned char PIN_B = 1;
    static const unsigned char PIN_DATA = 2;
public:
    XorGate() = default;
    XorGate(const XorGate&) = default;
    XorGate(XorGate &&) = default;

    XorGate& operator=(const XorGate&) = default;
    XorGate& operator=(XorGate&&) = default;

    virtual auto setInput(unsigned char pin, bool value, bool force = false) -> void override;

private:
    bool _a;
    bool _b;
};

}}

#endif // _XORGATE_H