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
        Bus<1> &carry;

        Add(Bus<width> &dataA, Bus<width> &dataB, Bus<1> &carry)
            : dataA(dataA), dataB(dataB), carry(carry)
        {
        }

        auto operator()(size_t index) -> Bit
        {
            auto a = dataA.getRepresentedValue();
            auto b = dataB.getRepresentedValue();
            auto c = carry.getRepresentedValue();
            return getBit<width>(a + b + c, index);
        }
    };

    template <size_t width>
    struct Adder : public Bus<width>
    {
        Adder() = delete;
        Adder(Bus<width> &dataA, Bus<width> &dataB, Bus<1> &carry)
            : Bus<width>(Add<width>(dataA, dataB, carry))
        {
        }
        Adder(const Adder &) = default;
        Adder(Adder &&) = default;

        auto operator=(const Adder &) -> Adder & = default;
        auto operator=(Adder &&) -> Adder & = default;
    };
}

#endif