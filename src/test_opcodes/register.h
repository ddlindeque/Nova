#ifndef __REGISTERH
#define __REGISTERH

#include <ostream>
#include <random>

#include "bit.h"
#include "bus.h"

namespace Nova
{

    template <size_t width>
    struct Register
    {
        Bus<1> &readEnable;  // When enabled, the register can be 'read'
        Bus<1> &writeEnable; // When enabled, the register will 'save' the value on the input pins during the clock pulse
        Bus<width> &dataBus;

        Bit data[width];

        Register() = delete;
        Register(Bus<1> &readEnable, Bus<1> &writeEnable, Bus<width> &dataBus)
            : readEnable(readEnable), writeEnable(writeEnable), dataBus(dataBus)
        {
        }
        Register(const Register &) = delete;
        Register(Register &&) = delete;

        auto operator=(const Register &) -> Register & = delete;
        auto operator=(Register &&) -> Register & = delete;

        auto getValue(size_t index) const -> Bit
        {
            switch (readEnable.getValue(0))
            {
            case Bit::High:
                switch (writeEnable.getValue(0))
                {
                case Bit::Low:
                    return data[index];
                default:
                    return Bit::Undefined;
                }
            case Bit::Low:
                switch (writeEnable.getValue(0))
                {
                case Bit::Low:
                    return Bit::Low;
                default:
                    return Bit::Undefined;
                }
            default:
                return Bit::Undefined;
            }
        }

        virtual auto pulse() -> bool
        {
            switch (writeEnable.getValue(0))
            {
            case Bit::Undefined:
                return false; // This is not a valid state
            case Bit::High:   // Read data from the bus
                if (readEnable.getValue(0) != Bit::Low)
                {
                    return false;
                }
                for (size_t i = 0; i < width; ++i)
                {
                    switch (dataBus.getValue(i))
                    {
                    case Bit::Undefined: // Cannot read undefined
                        return false;
                    case Bit::High:
                        data[i] = Bit::High;
                        break;
                    case Bit::Low:
                        data[i] = Bit::Low;
                        break;
                    }
                }
                return true;
            default: // When LOW, we do not 'save' anything (we ignore the readEnable line)
                return true;
            }
        }

        friend auto operator<<(std::ostream &s, const Register<width> &r) -> std::ostream &
        {
            s << "Register[";
            for (size_t i = 0; i < width; ++i)
            {
                s << r.data[i];
            }

            return s << ']';
        }
    };

}

#endif