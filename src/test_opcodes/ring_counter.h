#ifndef __RINGCOUNTERH
#define __RINGCOUNTERH

#include <ostream>
#include "bit.h"
#include "bus.h"

namespace Nova
{

    template <size_t width>
    struct RingCounter
    {
        Bus<1> &resetEnable;
        size_t current_index;

        RingCounter() = delete;
        RingCounter(Bus<1> &resetEnable)
            : resetEnable(resetEnable)
        {
            // Some random start (require reset)
            current_index = 423427 % width;
        }
        RingCounter(const RingCounter &) = delete;
        RingCounter(RingCounter &&) = delete;

        auto operator=(const RingCounter &) -> RingCounter & = delete;
        auto operator=(RingCounter &&) -> RingCounter & = delete;

        auto getValue(size_t index) const -> Bit
        {
            return index == current_index ? Bit::High : Bit::Low;
        }

        auto pulse() -> bool
        {
            switch (resetEnable.getValue(0))
            {
            case Bit::High:
                current_index = 0;
                return true;
            case Bit::Low:
                ++current_index;
                current_index %= width;
                return true;
            default:
                return false;
            }
        }

        friend auto operator<<(std::ostream &s, const RingCounter<width> &r) -> std::ostream &
        {
            s << "RingCounter[";
            for (size_t i = 0; i < width; ++i)
            {
                s << r.getValue(i);
            }

            return s << ']';
        }
    };
}

#endif