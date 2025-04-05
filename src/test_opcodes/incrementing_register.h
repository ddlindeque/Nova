#ifndef __INCREMENTING_REGISTERH
#define __INCREMENTING_REGISTERH

#include "bit.h"
#include "bus.h"
#include "register.h"
#include "logic.h"

namespace Nova
{

    template <size_t width>
    struct IncrementingRegister : public Register<width>
    {
        Bus<1> &zeroEnabled;      // When enbabled, the register will zero
        Bus<1> &incrementEnabled; // When enabled, the register with increment by 1

        IncrementingRegister() = delete;
        IncrementingRegister(Bus<1> &readEnable, Bus<1> &writeEnable, Bus<1> &zeroEnabled, Bus<1> &incrementEnabled, Bus<width> &dataBus)
            : Register<width>(readEnable, writeEnable, dataBus), zeroEnabled(zeroEnabled), incrementEnabled(incrementEnabled)
        {
        }
        IncrementingRegister(const IncrementingRegister &) = delete;
        IncrementingRegister(IncrementingRegister &&) = delete;

        auto operator=(const IncrementingRegister &) -> IncrementingRegister & = delete;
        auto operator=(IncrementingRegister &&) -> IncrementingRegister & = delete;

        virtual auto pulse() -> bool override
        {
            auto we = Register<width>::writeEnable.getValue(0);
            auto ie = incrementEnabled.getValue(0);
            auto ze = zeroEnabled.getValue(0);
            if (we == Bit::Undefined || ie == Bit::Undefined || ze == Bit::Undefined)
            {
                return false;
            }
            if (we == Bit::High && ie == Bit::High)
                return false;
            if (we == Bit::High && ze == Bit::High)
                return false;
            if (ie == Bit::High && ze == Bit::High)
                return false;

            if (ie == Bit::High)
            {
                return increment<width>(Register<width>::data);
            }
            if (ze == Bit::High)
            {
                for (size_t i = 0; i < width; ++i)
                {
                    Register<width>::data[i] = Bit::Low;
                }
                return true;
            }
            return Register<width>::pulse();
        }
    };

}

#endif