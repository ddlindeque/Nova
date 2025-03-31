#ifndef __SYSTEMH
#define __SYSTEMH

#include "bit.h"
#include "bus.h"
#include "control_bus.h"
#include "register.h"
#include "counter.h"

namespace Nova {

struct System {
    ControlBus controlBus;
    Bus<2> addressBusSegment;
    Bus<16> addressBus;
    Bus<8> dataBus;

    // Components
    Counter mclk;
    Register<8> ir;
    Register<16> pc;

    System();
    System(const System&) = delete;
    System(System&&) = delete;
    auto operator=(const System&) -> System& = delete;
    auto operator=(System&&) -> System& = delete;

    auto reset() -> void;
    auto pulse() -> bool;

private:
    auto fetch() -> void;
    auto nop() -> void;    
};


}

#endif