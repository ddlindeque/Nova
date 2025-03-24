#ifndef _NOTGATE_H
#define _NOTGATE_H

#include "device.h"

namespace Nova {
namespace hardware {

class NotGate : public Device {
public:
    static const unsigned char PIN_INPUT = 0;
    static const unsigned char PIN_DATA = 1;
public:
    NotGate() = default;
    NotGate(const NotGate&) = default;
    NotGate(NotGate &&) = default;

    NotGate& operator=(const NotGate&) = default;
    NotGate& operator=(NotGate&&) = default;

    virtual auto setInput(unsigned char pin, bool value, bool force = false) -> void override;

private:
    bool _input;
};

}}

#endif // _NOTGATE_H