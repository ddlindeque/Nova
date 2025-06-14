#ifndef __NOTH
#define __NOTH

#include "bus.h"
#include "bit.h"

namespace Nova
{
    template <size_t width>
    struct Not
    {
        Bus<width> &data;

        Not(Bus<width> &data)
            : data(data)
        {
        }

        auto operator()(size_t index) -> Bit
        {
            auto d = ~data.getRepresentedValue();
            return getBit<width>(d, index);
        }
    };

    template <size_t width>
    struct Notter : public Bus<width>
    {
        Notter() = delete;
        Notter(Bus<width> &data)
            : Bus<width>(Not<width>(data))
        {
        }
        Notter(const Notter &) = default;
        Notter(Notter &&) = default;

        auto operator=(const Notter &) -> Notter & = default;
        auto operator=(Notter &&) -> Notter & = default;
    };
}

#endif