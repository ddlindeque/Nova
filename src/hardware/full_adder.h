#ifndef _FULLADDER_H
#define _FULLADDER_H

#include "device.h"
#include "construct.h"

#ifdef FULL_ADDER_BY_CONSTRUCTION

#include "xor_gate.h"
#include "and_gate.h"
#include "or_gate.h"

#endif // FULL_ADDER_BY_CONSTRUCTION

namespace Nova {
namespace hardware {

class FullAdder : public Device {
public:
    static const unsigned char PIN_A = 0;
    static const unsigned char PIN_B = 1;
    static const unsigned char PIN_CIN = 2;
    static const unsigned char PIN_DATA = 3;
    static const unsigned char PIN_CARRY = 4;
public:
#ifdef FULL_ADDER_BY_CONSTRUCTION
    FullAdder();
    FullAdder(const FullAdder&) = delete;
    FullAdder(FullAdder &&) = delete;

    FullAdder& operator=(const FullAdder&) = delete;
    FullAdder& operator=(FullAdder&&) = delete;
#else
    FullAdder() = default;
    FullAdder(const FullAdder&) = default;
    FullAdder(FullAdder &&) = default;

    FullAdder& operator=(const FullAdder&) = default;
    FullAdder& operator=(FullAdder&&) = default;
#endif //FULL_ADDER_BY_CONSTRUCTION

    virtual auto setInput(unsigned char pin, bool value, bool force = false) -> void override;

#ifdef FULL_ADDER_BY_CONSTRUCTION
    virtual auto registerListener(unsigned char pin, const Listener &handler) -> void override;
#endif // FULL_ADDER_BY_CONSTRUCTION

private:
#ifdef FULL_ADDER_BY_CONSTRUCTION
    XorGate _a_xor_b;
    XorGate _a_xor_b_xor_cin;
    
    AndGate _a_and_b;
    AndGate _a_xor_b_and_cin;
    OrGate __a_xor_b_and_cin__or__a_and_b;
#else
    bool _a;
    bool _b;
    bool _cin;
#endif // FULL_ADDER_BY_CONSTRUCTION
};

}}

#endif // _FULLADDER_H