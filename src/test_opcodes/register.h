#ifndef __REGISTERH
#define __REGISTERH

#include <ostream>
#include "bit.h"
#include "bus.h"

namespace Nova
{

    template <size_t width>
    struct Register
    {
        Bit &readEnable;
        Bit &writeEnable;

        Bus<width> &dataBus;

        bool data[width];

        Register() = delete;
        Register(Bit &readEnable, Bit &writeEnable, Bus<width> &dataBus)
            : readEnable(readEnable), writeEnable(writeEnable), dataBus(dataBus)
        {
        }
        Register(const Register &) = delete;
        Register(Register &&) = delete;

        auto operator=(const Register &) -> Register & = delete;
        auto operator=(Register &&) -> Register & = delete;

        auto getValue() -> unsigned long int
        {
            unsigned long int result = data[0] ? 1 : 0;
            for (size_t i = 1; i < width; ++i)
            {
                result << 1;
                if (data[i])
                {
                    result |= 1;
                }
            }
            return result;
        }

        auto pulse() -> bool
        {
            switch (readEnable)
            {
            case Bit::Undefined: // data bus is undefined
                for (size_t i = 0; i < width; ++i)
                {
                    dataBus.bits[i] = Bit::Undefined;
                }
                break;
            case Bit::High: // Write data onto the bus
                if (writeEnable != Bit::Low)
                    return false;
                for (size_t i = 0; i < width; ++i)
                {
                    dataBus.bits[i] = data[i] ? Bit::High : Bit::Low;
                }
                break;
            }
            switch (writeEnable)
            {
            case Bit::Undefined:
                return false; // This is not a valid state
            case Bit::High:   // Read data from the bus
                for (size_t i = 0; i < width; ++i)
                {
                    switch (dataBus.bits[i])
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
            }
            return true;
        }
    };

}

#endif