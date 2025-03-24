#ifndef _HALFADDER_H
#define _HALFADDER_H

#include "device.h"
#include "construct.h"

#ifdef HALF_ADDER_BY_CONSTRUCTION

#include "xor_gate.h"
#include "and_gate.h"

#endif // HALF_ADDER_BY_CONSTRUCTION

namespace Nova {
namespace hardware {

class HalfAdder : public Device {
public:
    static const unsigned char PIN_A = 0;
    static const unsigned char PIN_B = 1;
    static const unsigned char PIN_DATA = 2;
    static const unsigned char PIN_CARRY = 3;
public:
    HalfAdder() = default;
    HalfAdder(const HalfAdder&) = default;
    HalfAdder(HalfAdder &&) = default;

    HalfAdder& operator=(const HalfAdder&) = default;
    HalfAdder& operator=(HalfAdder&&) = default;

    virtual auto setInput(unsigned char pin, bool value, bool force = false) -> void override;

#ifdef HALF_ADDER_BY_CONSTRUCTION
    virtual auto registerListener(unsigned char pin, const Listener &handler) -> void override;
#endif // HALF_ADDER_BY_CONSTRUCTION

private:
#ifdef HALF_ADDER_BY_CONSTRUCTION
    XorGate _xor;
    AndGate _and;
#else
    bool _a;
    bool _b;
#endif // HALF_ADDER_BY_CONSTRUCTION
};

}}

#endif // _HALFADDER_H