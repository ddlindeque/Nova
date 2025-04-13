#ifndef __RAMH
#define __RAMH

#include <ostream>
#include <stdlib.h>
#include <memory>
#include <vector>

#include "bit.h"
#include "bus.h"
#include "device.h"
#include "register.h"

namespace Nova
{
    template <size_t dataBusSize, size_t addressBusSize, size_t bytes>
    struct Ram : public Devise
    {
        Bus<1> &writeEnable;
        Bus<addressBusSize> &addressBus;

        std::vector<std::unique_ptr<Bus<1>>> addressSelect;
        std::vector<std::unique_ptr<Register<dataBusSize>>> data;

        Ram() = delete;
        Ram(Bus<1> &writeEnable, Bus<dataBusSize> &dataBus, Bus<addressBusSize> &addressBus)
            : writeEnable(writeEnable), addressBus(addressBus)
        {
            for (size_t i = 0; i < bytes; ++i)
            {
                addressSelect.push_back(std::make_unique<Bus<1>>([this, i](size_t)
                                                                 {
                        unsigned long addr = this->addressBus.getRepresentedValue();
                        return addr == i && this->writeEnable.getValue(0) == Bit::High ? Bit::High : Bit::Low; }));
                data.push_back(std::make_unique<Register<dataBusSize>>(*addressSelect.back(), dataBus));
            }
        }
        Ram(const Ram &) = delete;
        Ram(Ram &&) = default;

        auto operator=(const Ram &) -> Ram & = delete;
        auto operator=(Ram &&) -> Ram & = default;

        auto getValue(size_t index) const -> Bit
        {
            unsigned long addr = addressBus.getRepresentedValue();
            return data[addr]->getValue(index);
        }

        auto pulse() -> bool override
        {
            for (size_t i = 0; i < bytes; ++i)
            {
                if (!data[i]->pulse())
                {
                    return false;
                }
            }
            return true;
        }
    };

}

#endif // __RAMH