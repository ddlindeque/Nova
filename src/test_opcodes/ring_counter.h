#ifndef __RINGCOUNTERH
#define __RINGCOUNTERH

#include <ostream>
#include <stdlib.h>
#include <time.h>

#include "bit.h"
#include "bus.h"
#include "device.h"

namespace Nova
{

    template <size_t width>
    struct RingCounter : public Devise
    {
        Bus<1> &incrementEnable;
        Bus<1> &zeroEnable;

        bool data[width];

        RingCounter() = delete;
        RingCounter(Bus<1> &incrementEnable, Bus<1> &zeroEnable)
            : incrementEnable(incrementEnable), zeroEnable(zeroEnable)
        {
            // Randomise the register
            srand(time(NULL));
            for (size_t i = 0; i < width; ++i)
            {
                data[i] = (rand() % 2) == 0 ? false : true;
            }
        }
        RingCounter(const RingCounter &) = default;
        RingCounter(RingCounter &&) = default;

        auto operator=(const RingCounter &) -> RingCounter & = default;
        auto operator=(RingCounter &&) -> RingCounter & = default;

        auto getValue(size_t index) const -> Bit
        {
            return data[index] ? Bit::High : Bit::Low;
        }

        auto pulse() -> bool override
        {
            switch (incrementEnable.getValue(0))
            {
            case Bit::Undefined:
                return false; // This is not a valid state
            case Bit::High:   // Increment the register
                if (zeroEnable.getValue(0) != Bit::Low)
                {
                    return false;
                }
                for (size_t i = 0; i < width - 1; i++)
                {
                    if (data[i])
                    {
                        data[i] = false;
                        data[i + 1] = true;
                        return true;
                    }
                }
                if (data[width - 1])
                {
                    data[width - 1] = false;
                    data[0] = true;
                    return true;
                }
                return false;
            default:
                switch (zeroEnable.getValue(0))
                {
                case Bit::Undefined:
                    return false;
                case Bit::High:
                    data[0] = true;
                    for (size_t i = 1; i < width; ++i)
                    {
                        data[i] = false;
                    }
                    return true;
                default:
                    return true;
                }
            }
        }

        friend auto operator<<(std::ostream &s, const RingCounter &reg) -> std::ostream &
        {
            for (size_t i = 0; i < width; ++i)
            {
                s << reg.getValue(i);
            }
            return s;
        }
    };

}

#endif // __RINGCOUNTERH