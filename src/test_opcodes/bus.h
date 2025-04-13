#ifndef __BUSH
#define __BUSH

#include <functional>
#include "bit.h"

namespace Nova
{
    // Note that we only suppor little-endian, this means bit zero is the most-significant-bit
    template <size_t width>
    struct Bus
    {
        typedef std::function<Bit(size_t)> ReadBit;

        ReadBit readBits;

        Bus() = delete;
        explicit Bus(const ReadBit &readBits) : readBits(readBits) {}
        Bus(const Bus &) = default;
        Bus(Bus &&) = default;

        auto operator=(const Bus &) -> Bus & = default;
        auto operator=(Bus &&) -> Bus & = default;

        auto getValue(size_t index) const -> Bit
        {
            return readBits(index);
        }

        auto getRepresentedValue() const -> unsigned long
        {
            unsigned long x = 0;
            for (size_t i = 0; i < width; ++i)
            {
                x <<= 1;
                if (getValue(i) == Bit::High)
                {
                    x |= 1;
                }
            }
            return x;
        }
    };
}

#endif