#ifndef __LOGICH
#define __LOGICH

#include <stddef.h>

namespace Nova
{
    template <size_t width>
    auto inc(bool reg[width]) -> void
    {
        for (size_t i = width - 1; i >= 0; --i)
        {
            if (reg[i])
            {
                reg[i] = false;
            }
            else
            {
                reg[i] = true;
                return;
            }
        }
    }

    template <size_t width>
    auto dec(bool reg[width]) -> void
    {
        for (size_t i = width - 1; i >= 0; --i)
        {
            if (reg[i])
            {
                reg[i] = false;
                return;
            }
            else
            {
                reg[i] = true;
            }
        }
    }

}

#endif