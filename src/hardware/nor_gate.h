#ifndef _NORGATE_H
#define _NORGATE_H

#include "device.h"

namespace Nova {
namespace hardware {

class NorGate : public Device {
public:
    static const unsigned char PIN_A = 0;
    static const unsigned char PIN_B = 1;
    static const unsigned char PIN_DATA = 2;
public:
    NorGate() = default;
    NorGate(const NorGate&) = default;
    NorGate(NorGate &&) = default;

    NorGate& operator=(const NorGate&) = default;
    NorGate& operator=(NorGate&&) = default;

    virtual auto setInput(unsigned char pin, bool value, bool force = false) -> void override;

private:
    bool _a;
    bool _b;
};

}}

#endif // _NORGATE_H