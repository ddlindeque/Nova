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

    template <size_t width>
    auto setBits(Bit bits[width], unsigned long value) -> void
    {
        size_t h = width;
        for (size_t i = 0; i < width; ++i)
        {
            --h;
            unsigned long m = 1 << h;
            if ((value & m) == m)
            {
                bits[i] = Bit::High;
            }
            else
            {
                bits[i] = Bit::Low;
            }
        }
    }
}

#endif