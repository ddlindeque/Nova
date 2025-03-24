#ifndef _NXORGATE_H
#define _NXORGATE_H

#include "device.h"

namespace Nova {
namespace hardware {

class NxorGate : public Device {
public:
    static const unsigned char PIN_A = 0;
    static const unsigned char PIN_B = 1;
    static const unsigned char PIN_DATA = 2;
public:
    NxorGate() = default;
    NxorGate(const NxorGate&) = default;
    NxorGate(NxorGate &&) = default;

    NxorGate& operator=(const NxorGate&) = default;
    NxorGate& operator=(NxorGate&&) = default;

    virtual auto setInput(unsigned char pin, bool value, bool force = false) -> void override;

private:
    bool _a;
    bool _b;
};

}}

#endif // _NXORGATE_H