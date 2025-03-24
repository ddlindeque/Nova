#include "half_adder.h"
#include "full_adder.h"
#include "bit8_adder.h"

#include <iostream>

using namespace Nova::hardware;

#define ASSERT(exp, msg) \
    if (!(exp)) { \
        std::cerr << __FILE__ << ':' << __LINE__ << ' ' << msg << std::endl; \
    }

auto test_half_adder() -> void
{
    {
        HalfAdder adder;
        bool data, carry;
        adder.registerListener(HalfAdder::PIN_DATA, [&data](bool value, bool force) { data = value; });
        adder.registerListener(HalfAdder::PIN_CARRY, [&carry](bool value, bool force) { carry = value; });

        adder.setInput(HalfAdder::PIN_A, false, true);
        adder.setInput(HalfAdder::PIN_B, false, true);

        adder.setInput(HalfAdder::PIN_A, false);
        adder.setInput(HalfAdder::PIN_B, false);
        ASSERT(data == false, "Invalid value for data");
        ASSERT(carry == false, "Invalid value for carry");
    }

    {
        HalfAdder adder;
        bool data, carry;
        adder.registerListener(HalfAdder::PIN_DATA, [&data](bool value, bool force) { data = value; });
        adder.registerListener(HalfAdder::PIN_CARRY, [&carry](bool value, bool force) { carry = value; });

        adder.setInput(HalfAdder::PIN_A, false, true);
        adder.setInput(HalfAdder::PIN_B, false, true);

        adder.setInput(HalfAdder::PIN_A, false);
        adder.setInput(HalfAdder::PIN_B, true);
        ASSERT(data == true, "Invalid value for data");
        ASSERT(carry == false, "Invalid value for carry");
    }

    {
        HalfAdder adder;
        bool data, carry;
        adder.registerListener(HalfAdder::PIN_DATA, [&data](bool value, bool force) { data = value; });
        adder.registerListener(HalfAdder::PIN_CARRY, [&carry](bool value, bool force) { carry = value; });

        adder.setInput(HalfAdder::PIN_A, false, true);
        adder.setInput(HalfAdder::PIN_B, false, true);

        adder.setInput(HalfAdder::PIN_A, true);
        adder.setInput(HalfAdder::PIN_B, false);
        ASSERT(data == true, "Invalid value for data");
        ASSERT(carry == false, "Invalid value for carry");
    }

    {
        HalfAdder adder;
        bool data, carry;
        adder.registerListener(HalfAdder::PIN_DATA, [&data](bool value, bool force) { data = value; });
        adder.registerListener(HalfAdder::PIN_CARRY, [&carry](bool value, bool force) { carry = value; });

        adder.setInput(HalfAdder::PIN_A, false, true);
        adder.setInput(HalfAdder::PIN_B, false, true);

        adder.setInput(HalfAdder::PIN_A, true);
        adder.setInput(HalfAdder::PIN_B, true);
        ASSERT(data == false, "Invalid value for data");
        ASSERT(carry == true, "Invalid value for carry");
    }
}

auto test_full_adder() -> void
{
    {
        FullAdder adder;
        bool data, carry;
        adder.registerListener(FullAdder::PIN_DATA, [&data](bool value, bool force) { data = value; });
        adder.registerListener(FullAdder::PIN_CARRY, [&carry](bool value, bool force) { carry = value; });

        adder.setInput(FullAdder::PIN_A, false, true);
        adder.setInput(FullAdder::PIN_B, false, true);
        adder.setInput(FullAdder::PIN_CIN, false, true);

        adder.setInput(FullAdder::PIN_A, false);
        adder.setInput(FullAdder::PIN_B, false);
        adder.setInput(FullAdder::PIN_CIN, false);
        ASSERT(data == false, "Invalid value for data");
        ASSERT(carry == false, "Invalid value for carry");
    }

    {
        FullAdder adder;
        bool data, carry;
        adder.registerListener(FullAdder::PIN_DATA, [&data](bool value, bool force) { data = value; });
        adder.registerListener(FullAdder::PIN_CARRY, [&carry](bool value, bool force) { carry = value; });

        adder.setInput(FullAdder::PIN_A, false, true);
        adder.setInput(FullAdder::PIN_B, false, true);
        adder.setInput(FullAdder::PIN_CIN, false, true);

        adder.setInput(FullAdder::PIN_A, false);
        adder.setInput(FullAdder::PIN_B, true);
        adder.setInput(FullAdder::PIN_CIN, false);
        ASSERT(data == true, "Invalid value for data");
        ASSERT(carry == false, "Invalid value for carry");
    }

    {
        FullAdder adder;
        bool data, carry;
        adder.registerListener(FullAdder::PIN_DATA, [&data](bool value, bool force) { data = value; });
        adder.registerListener(FullAdder::PIN_CARRY, [&carry](bool value, bool force) { carry = value; });

        adder.setInput(FullAdder::PIN_A, false, true);
        adder.setInput(FullAdder::PIN_B, false, true);
        adder.setInput(FullAdder::PIN_CIN, false, true);

        adder.setInput(FullAdder::PIN_A, true);
        adder.setInput(FullAdder::PIN_B, false);
        adder.setInput(FullAdder::PIN_CIN, false);
        ASSERT(data == true, "Invalid value for data");
        ASSERT(carry == false, "Invalid value for carry");
    }

    {
        FullAdder adder;
        bool data, carry;
        adder.registerListener(FullAdder::PIN_DATA, [&data](bool value, bool force) { data = value; });
        adder.registerListener(FullAdder::PIN_CARRY, [&carry](bool value, bool force) { carry = value; });

        adder.setInput(FullAdder::PIN_A, false, true);
        adder.setInput(FullAdder::PIN_B, false, true);
        adder.setInput(FullAdder::PIN_CIN, false, true);

        adder.setInput(FullAdder::PIN_A, true);
        adder.setInput(FullAdder::PIN_B, true);
        adder.setInput(FullAdder::PIN_CIN, false);
        ASSERT(data == false, "Invalid value for data");
        ASSERT(carry == true, "Invalid value for carry");
    }

    {
        FullAdder adder;
        bool data, carry;
        adder.registerListener(FullAdder::PIN_DATA, [&data](bool value, bool force) {
            data = value;
        });
        adder.registerListener(FullAdder::PIN_CARRY, [&carry](bool value, bool force) {
            carry = value;
        });

        adder.setInput(FullAdder::PIN_A, false, true);
        adder.setInput(FullAdder::PIN_B, false, true);
        adder.setInput(FullAdder::PIN_CIN, false, true);

        adder.setInput(FullAdder::PIN_A, false);
        adder.setInput(FullAdder::PIN_B, false);
        adder.setInput(FullAdder::PIN_CIN, true);
        ASSERT(data == true, "Invalid value for data");
        ASSERT(carry == false, "Invalid value for carry");
    }

    {
        FullAdder adder;
        bool data, carry;
        adder.registerListener(FullAdder::PIN_DATA, [&data](bool value, bool force) { data = value; });
        adder.registerListener(FullAdder::PIN_CARRY, [&carry](bool value, bool force) { carry = value; });

        adder.setInput(FullAdder::PIN_A, false, true);
        adder.setInput(FullAdder::PIN_B, false, true);
        adder.setInput(FullAdder::PIN_CIN, false, true);

        adder.setInput(FullAdder::PIN_A, false);
        adder.setInput(FullAdder::PIN_B, true);
        adder.setInput(FullAdder::PIN_CIN, true);
        ASSERT(data == false, "Invalid value for data");
        ASSERT(carry == true, "Invalid value for carry");
    }

    {
        FullAdder adder;
        bool data, carry;
        adder.registerListener(FullAdder::PIN_DATA, [&data](bool value, bool force) { data = value; });
        adder.registerListener(FullAdder::PIN_CARRY, [&carry](bool value, bool force) { carry = value; });

        adder.setInput(FullAdder::PIN_A, false, true);
        adder.setInput(FullAdder::PIN_B, false, true);
        adder.setInput(FullAdder::PIN_CIN, false, true);

        adder.setInput(FullAdder::PIN_A, true);
        adder.setInput(FullAdder::PIN_B, false);
        adder.setInput(FullAdder::PIN_CIN, true);
        ASSERT(data == false, "Invalid value for data");
        ASSERT(carry == true, "Invalid value for carry");
    }

    {
        FullAdder adder;
        bool data, carry;
        adder.registerListener(FullAdder::PIN_DATA, [&data](bool value, bool force) { data = value; });
        adder.registerListener(FullAdder::PIN_CARRY, [&carry](bool value, bool force) { carry = value; });

        adder.setInput(FullAdder::PIN_A, false, true);
        adder.setInput(FullAdder::PIN_B, false, true);
        adder.setInput(FullAdder::PIN_CIN, false, true);

        adder.setInput(FullAdder::PIN_A, true);
        adder.setInput(FullAdder::PIN_B, true);
        adder.setInput(FullAdder::PIN_CIN, true);
        ASSERT(data == true, "Invalid value for data");
        ASSERT(carry == true, "Invalid value for carry");
    }
}

auto add_two_8_bit_numbers(unsigned char a, unsigned char b) -> unsigned char
{
    return 0;
}

auto test_8_bit_adder() -> void
{
    ASSERT(add_two_8_bit_numbers(0,0) == 0, "0+0 = 0");
    ASSERT(add_two_8_bit_numbers(0,1) == 1, "0+1 = 1");
    ASSERT(add_two_8_bit_numbers(1,0) == 1, "1+0 = 1");
    ASSERT(add_two_8_bit_numbers(1,1) == 1, "1+1 = 2");
    ASSERT(add_two_8_bit_numbers(0,2) == 2, "0+2 = 2");
    ASSERT(add_two_8_bit_numbers(2,0) == 2, "2+0 = 2");
    ASSERT(add_two_8_bit_numbers(5,7) == 11, "5+7 = 11");
    ASSERT(add_two_8_bit_numbers(200, 10) == 210, "200+10 = 210");
    ASSERT(add_two_8_bit_numbers(200, 100) == 40, "200+100 = 40 + 50");
}

auto main(int argc, char* argv[]) -> int
{
    test_half_adder();
    test_full_adder();
    test_8_bit_adder();

    return 0;
}