#ifndef __REGISTERH
#define __REGISTERH

#include <ostream>
#include <stdlib.h>
#include <time.h>

#include "bit.h"
#include "bus.h"
#include "device.h"
#include "logic.h"

namespace Nova
{

    template <size_t width>
    struct Register : public Devise
    {
        Bus<1> &writeEnable;
        Bus<width> &dataBus;

        bool data[width];

        Register() = delete;
        Register(Bus<1> &writeEnable, Bus<width> &dataBus)
            : writeEnable(writeEnable), dataBus(dataBus)
        {
            // Randomise the register
            srand(time(NULL));
            for (size_t i = 0; i < width; ++i)
            {
                data[i] = (rand() % 2) == 0 ? false : true;
            }
        }
        Register(const Register &) = default;
        Register(Register &&) = default;

        auto operator=(const Register &) -> Register & = default;
        auto operator=(Register &&) -> Register & = default;

        auto getValue(size_t index) const -> Bit
        {
            return data[index] ? Bit::High : Bit::Low;
        }

        auto pulse() -> bool override
        {
            switch (writeEnable.getValue(0))
            {
            case Bit::Undefined:
                return false; // This is not a valid state
            case Bit::High:   // Read data from the bus
                for (size_t i = 0; i < width; ++i)
                {
                    switch (dataBus.getValue(i))
                    {
                    case Bit::Undefined: // Cannot read undefined
                        return false;
                    case Bit::High:
                        data[i] = true;
                        break;
                    case Bit::Low:
                        data[i] = false;
                        break;
                    }
                }
                return true;
            default:
                return true;
            }
        }

        friend auto operator<<(std::ostream &s, const Register &reg) -> std::ostream &
        {
            for (size_t i = 0; i < width; ++i)
            {
                s << reg.getValue(i);
            }
            return s;
        }
    };

    template <size_t width>
    struct IncrementableRegister : public Register<width>
    {
        Bus<1> &incrementEnable;

        IncrementableRegister() = delete;
        IncrementableRegister(Bus<1> &incrementEnable, Bus<1> &writeEnable, Bus<width> &dataBus)
            : Register<width>(writeEnable, dataBus), incrementEnable(incrementEnable)
        {
        }
        IncrementableRegister(const IncrementableRegister &) = default;
        IncrementableRegister(IncrementableRegister &&) = default;

        auto operator=(const IncrementableRegister &) -> IncrementableRegister & = delete;
        auto operator=(IncrementableRegister &&) -> IncrementableRegister & = delete;

        auto pulse() -> bool override
        {
            unsigned char c = 0;
            if (Register<width>::writeEnable.getValue(0) != Bit::Low)
            {
                ++c;
            }
            if (incrementEnable.getValue(0) != Bit::Low)
            {
                ++c;
            }
            if (c > 1)
            {
                return false;
            }

            switch (incrementEnable.getValue(0))
            {
            case Bit::Undefined:
                return false;
            case Bit::High:
                inc<width>(Register<width>::data);
                return true;
            default:
                return Register<width>::pulse();
            }
        }
    };

    template <size_t width>
    struct IncrementableDecrementableRegister : public IncrementableRegister<width>
    {
        Bus<1> &decrementEnable;

        IncrementableDecrementableRegister() = delete;
        IncrementableDecrementableRegister(Bus<1> &incrementEnable, Bus<1> &decrementEnable, Bus<1> &writeEnable, Bus<width> &dataBus)
            : IncrementableRegister<width>(incrementEnable, writeEnable, dataBus), decrementEnable(decrementEnable)
        {
        }
        IncrementableDecrementableRegister(const IncrementableDecrementableRegister &) = default;
        IncrementableDecrementableRegister(IncrementableDecrementableRegister &&) = default;

        auto operator=(const IncrementableDecrementableRegister &) -> IncrementableDecrementableRegister & = delete;
        auto operator=(IncrementableDecrementableRegister &&) -> IncrementableDecrementableRegister & = delete;

        auto pulse() -> bool override
        {
            unsigned char c = 0;
            if (Register<width>::writeEnable.getValue(0) != Bit::Low)
            {
                ++c;
            }
            if (IncrementableRegister<width>::incrementEnable.getValue(0) != Bit::Low)
            {
                ++c;
            }
            if (decrementEnable.getValue(0) != Bit::Low)
            {
                ++c;
            }
            if (c > 1)
            {
                return false;
            }

            switch (decrementEnable.getValue(0))
            {
            case Bit::Undefined:
                return false;
            case Bit::High:
                dec<width>(Register<width>::data);
                return true;
            default:
                return IncrementableRegister<width>::pulse();
            }
        }
    };

}

#endif