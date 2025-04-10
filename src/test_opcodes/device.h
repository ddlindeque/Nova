#ifndef __DEVISEH
#define __DEVISEH

namespace Nova
{

    struct Devise
    {
        Devise() = default;
        Devise(const Devise&) = default;
        Devise(Devise&&) = default;
        virtual ~Devise() = default;
        auto operator=(const Devise&) -> Devise& = default;
        auto operator=(Devise&&) -> Devise& = default;

        virtual auto pulse() -> bool = 0;
    };

}

#endif