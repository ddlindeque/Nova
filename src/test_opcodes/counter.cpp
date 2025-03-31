#include "counter.h"

namespace Nova
{

    Counter::Counter(Bit &reset)
        : reset(reset)
    {
    }

    auto Counter::pulse() -> bool
    {
        switch (reset)
        {
        case Bit::High:
            count = 0;
            return true;
        case Bit::Low:
            ++count;
            return true;
        default:
            return false;
        }
    }

    auto operator<<(std::ostream &s, const Counter &b) -> std::ostream &
    {
        return s << b.count;
    }

}