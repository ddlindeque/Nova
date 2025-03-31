#ifndef __BUSH
#define __BUSH

#include <ostream>
#include "bit.h"

namespace Nova
{

    template <size_t width>
    struct Bus
    {
        Bit bits[width];

        Bus()
        {
            reset();
        }
        Bus(const Bus &) = default;
        Bus(Bus &&) = default;

        auto operator=(const Bus &) -> Bus & = default;
        auto operator=(Bus &&) -> Bus & = default;

        auto reset() -> void
        {
            for (size_t i = 0; i < width; ++i)
                bits[i] = Bit::Undefined;
        }

        friend auto operator<<(std::ostream &s, const Bus &b) -> std::ostream &
        {
            for (size_t i = 0; i < width; ++i)
                s << b.bits[i];

            return s;
        }
    };

}

#endif