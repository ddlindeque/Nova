#ifndef __BUSH
#define __BUSH

#include <functional>
#include <vector>
#include "bit.h"

namespace Nova
{

    template <size_t width>
    struct Bus
    {
        typedef std::function<Bit(size_t)> BusReader;

        std::vector<BusReader> busReaders;

        Bus() = default;
        Bus(const Bus &) = default;
        Bus(Bus &&) = default;

        auto operator=(const Bus &) -> Bus & = default;
        auto operator=(Bus &&) -> Bus & = default;

        auto connect(const BusReader &busReader) -> void
        {
            busReaders.push_back(busReader);
        }

        virtual auto getValue(size_t index) -> Bit
        {
            Bit output = Bit::Low;
            for (const auto &busReader : busReaders)
            {
                Bit input = busReader(index);
                if (output == Bit::Undefined || input == Bit::Undefined)
                {
                    output = Bit::Undefined;
                }
                else if (output == Bit::High || input == Bit::High)
                {
                    output = Bit::High;
                }
            }
            return output;
        }
    };

}

#endif