#ifndef __COUNTERH
#define __COUNTERH

#include <ostream>
#include "bit.h"

namespace Nova
{

    struct Counter
    {
        Bit &reset;

        size_t count;

        Counter(Bit &reset);

        auto pulse() -> bool;
    };

    auto operator<<(std::ostream &, const Counter &) -> std::ostream &;

}

#endif