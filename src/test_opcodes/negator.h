#ifndef __NEGATORH
#define __NEGATORH

#include "bus.h"
#include "bit.h"

namespace Nova
{
    template <size_t width>
    struct Negate
    {
        Bus<width> &data;

        Negate(Bus<width> &data)
            : data(data)
        {
        }

        auto operator()(size_t index) -> Bit
        {
            auto d = ~data.getRepresentedValue();
            return getBit<width>(d + 1, index);
        }
    };

    template <size_t width>
    struct Negator : public Bus<width>
    {
        Negator() = delete;
        Negator(Bus<width> &data)
            : Bus<width>(Negate<width>(data))
        {
        }
        Negator(const Negator &) = default;
        Negator(Negator &&) = default;

        auto operator=(const Negator &) -> Negator & = default;
        auto operator=(Negator &&) -> Negator & = default;
    };
}

#endif