#include "bit.h"

namespace Nova
{
    auto operator<<(std::ostream &s, const Bit &b) -> std::ostream &
    {
        switch (b)
        {
        case Bit::Undefined:
            return s << 'U';
        case Bit::High:
            return s << 'H';
        case Bit::Low:
            return s << 'L';
        default:
            return s << 'E';
        }
    }
}
