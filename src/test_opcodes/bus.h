#ifndef __BUSH
#define __BUSH

#include <functional>
#include "bit.h"

namespace Nova
{
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
    };
}

#endif