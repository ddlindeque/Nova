#ifndef __LOGICH
#define __LOGICH

#include "bit.h"

namespace Nova
{

    auto notBit(const Bit &b1, const Bit &b2) -> Bit;
    auto andBit(const Bit &b1, const Bit &b2) -> Bit;
    auto orBit(const Bit &b1, const Bit &b2) -> Bit;

    template <size_t width>
    auto increment(Bit bits[width]) -> bool
    {
        bool carry = true;
        for (size_t i = 0; i < width; ++i)
        {
            if (!carry)
            {
                return true;
            }
            switch (bits[i])
            {
            case Bit::High:
                carry = true;
                bits[i] = Bit::Low;
                break;
            case Bit::Low:
                carry = false;
                bits[i] = Bit::High;
                break;
            case Bit::Undefined:
                return false;
            }
        }
        return true;
    }

}

#endif