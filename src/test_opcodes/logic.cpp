#include "logic.h"

namespace Nova
{

    auto notBit(const Bit &b) -> Bit
    {
        if (b == Bit::Undefined)
            return Bit::Undefined;
        return b == Bit::High ? Bit::Low : Bit::High;
    }

    auto andBit(const Bit &b1, const Bit &b2) -> Bit
    {
        if (b1 == Bit::Undefined || b2 == Bit::Undefined)
            return Bit::Undefined;
        return b1 == Bit::High && b2 == Bit::High ? Bit::High : Bit::Low;
    }

    auto orBit(const Bit &b1, const Bit &b2) -> Bit
    {
        if (b1 == Bit::Undefined || b2 == Bit::Undefined)
            return Bit::Undefined;
        return b1 == Bit::High && b2 == Bit::High ? Bit::High : Bit::Low;
    }

}