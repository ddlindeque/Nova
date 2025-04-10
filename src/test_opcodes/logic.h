#ifndef __LOGICH
#define __LOGICH

#include <stddef.h>

namespace Nova
{

    template <size_t width>
    auto inc(bool reg[width]) -> void
    {
        for (size_t i = 0; i < width; ++i)
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

}

#endif