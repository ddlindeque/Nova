#include "control_bus.h"

namespace Nova
{

    auto operator<<(std::ostream &s, const ControlBus &b) -> std::ostream &
    {
        return s << "MCLK_RESET=" << b.bits[ControlBus::MCLK_RESET]
                 << "ADDR_SELECT_PC=" << b.bits[ControlBus::ADDR_SELECT_PC]
                 << "; ADDR_SELECT_LATCH=" << b.bits[ControlBus::ADDR_SELECT_LATCH]
                 << ";MEM_SELECT_R_MEM=" << b.bits[ControlBus::MEM_SELECT_R_MEM]
                 << ";MEM_SELECT_W_IR=" << b.bits[ControlBus::MEM_SELECT_W_IR]
                 << ";PC_INCREMENT=" << b.bits[ControlBus::PC_INCREMENT]
                 << ";IR_WRITE=" << b.bits[ControlBus::IR_WRITE];
    }

}