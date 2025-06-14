#ifndef __ADDERH
#define __ADDERH

#include "bus.h"
#include "bit.h"

namespace Nova
{
    template <size_t width>
    struct Add
    {
        Bus<width> &dataA;
        Bus<width> &dataB;

        Add(Bus<width> &dataA, Bus<width> &dataB)
            : dataA(dataA), dataB(dataB)
        {
        }

        auto operator()(size_t index) -> Bit
        {
            auto a = dataA.getRepresentedValue();
            auto b = dataB.getRepresentedValue();
            return getBit<width>(a + b, index);
        }
    };

    template <size_t width>
    struct Adder : public Bus<width>
    {
        Adder() = delete;
        Adder(Bus<width> &dataA, Bus<width> &dataB)
            : Bus<width>(Add<width>(dataA, dataB))
        {
        }
        Adder(const Adder &) = default;
        Adder(Adder &&) = default;

        auto operator=(const Adder &) -> Adder & = default;
        auto operator=(Adder &&) -> Adder & = default;
    };
}

#endif