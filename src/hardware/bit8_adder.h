#ifndef _BIT8_ADDER_H
#define _BIT8_ADDER_H

#include "device.h"
#include "half_adder.h"
#include "full_adder.h"

namespace Nova {
namespace hardware {

class Bit8Adder : public Device {
public:
    static const unsigned char PIN_A0 = 0;
    static const unsigned char PIN_A1 = 1;
    static const unsigned char PIN_A2 = 2;
    static const unsigned char PIN_A3 = 3;
    static const unsigned char PIN_A4 = 4;
    static const unsigned char PIN_A5 = 5;
    static const unsigned char PIN_A6 = 6;
    static const unsigned char PIN_A7 = 7;

    static const unsigned char PIN_B0 = 8;
    static const unsigned char PIN_B1 = 9;
    static const unsigned char PIN_B2 = 10;
    static const unsigned char PIN_B3 = 11;
    static const unsigned char PIN_B4 = 12;
    static const unsigned char PIN_B5 = 13;
    static const unsigned char PIN_B6 = 14;
    static const unsigned char PIN_B7 = 15;

    static const unsigned char PIN_DATA0 = 16;
    static const unsigned char PIN_DATA1 = 17;
    static const unsigned char PIN_DATA2 = 18;
    static const unsigned char PIN_DATA3 = 19;
    static const unsigned char PIN_DATA4 = 20;
    static const unsigned char PIN_DATA5 = 21;
    static const unsigned char PIN_DATA6 = 22;
    static const unsigned char PIN_DATA7 = 23;

    static const unsigned char PIN_CARRY = 24;
public:
    Bit8Adder();
    Bit8Adder(const Bit8Adder&) = delete;
    Bit8Adder(Bit8Adder &&) = delete;

    Bit8Adder& operator=(const Bit8Adder&) = delete;
    Bit8Adder& operator=(Bit8Adder&&) = delete;

    virtual auto setInput(unsigned char pin, bool value, bool force = false) -> void override;
    virtual auto registerListener(unsigned char pin, const Listener &handler) -> void override;

private:
    HalfAdder _data0;
    FullAdder _data1;
    FullAdder _data2;
    FullAdder _data3;
    FullAdder _data4;
    FullAdder _data5;
    FullAdder _data6;
    FullAdder _data7;
};

}}

#endif // _BIT8_ADDER_H