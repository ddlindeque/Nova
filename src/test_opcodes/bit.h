#ifndef __BITH
#define __BITH

#include <ostream>

namespace Nova
{

    enum class Bit
    {
        Undefined,
        Low,
        High
    };

    auto operator<<(std::ostream &, const Bit &) -> std::ostream &;

    struct ConstantBits {
        static Bit alwaysLow;
        static Bit alwaysHigh;
    };
}

#endif