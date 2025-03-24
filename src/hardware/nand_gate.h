#ifndef _NANDGATE_H
#define _NANDGATE_H

#include "device.h"

namespace Nova {
namespace hardware {

class NandGate : public Device {
public:
    static const unsigned char PIN_A = 0;
    static const unsigned char PIN_B = 1;
    static const unsigned char PIN_DATA = 2;
public:
    NandGate() = default;
    NandGate(const NandGate&) = default;
    NandGate(NandGate &&) = default;

    NandGate& operator=(const NandGate&) = default;
    NandGate& operator=(NandGate&&) = default;

    virtual auto setInput(unsigned char pin, bool value, bool force = false) -> void override;

private:
    bool _a;
    bool _b;
};

}}

#endif // _NANDGATE_H