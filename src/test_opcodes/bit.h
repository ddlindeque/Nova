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
        // We're little-endian, this means bit zero is the most-significant-bit
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

    template<size_t width>
    auto getBit(unsigned long value, size_t index) -> Bit
    {
        // We're little-endian, this means bit zero is the most-significant-bit
        // When index is zero, we need the most significant bit, which is 'width - 1'
        // when index is width-1, we need the least significant bit, which is '0'
        auto m = 1 << (width - 1 - index);
        if ((value & m) == 0)
        {
            return Bit::Low;
        }
        else
        {
            return Bit::High;
        }
    }
}

#endif