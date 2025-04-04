#ifndef __CONTROL_BUSH
#define __CONTROL_BUSH

#include <ostream>

#include "bit.h"
#include "bus.h"

namespace Nova {

struct ControlBus : public Bus<8> {

    static const unsigned char MCLK_RESET = 0;

    static const unsigned char ADDR_SELECT_PC = 1;
    static const unsigned char ADDR_SELECT_LATCH = 2;

    static const unsigned char MEM_SELECT_R_MEM = 3;

    static const unsigned char MEM_SELECT_W_IR = 4;

    static const unsigned char PC_INCREMENT = 5;
    static const unsigned char PC_WRITE = 6;

    static const unsigned char IR_WRITE = 7;

    auto microClockReset() { bits[MCLK_RESET] = Bit::High; }
    auto microClockIncrement() { bits[MCLK_RESET] = Bit::Low; }

    auto addressBusSelectPc() { bits[ADDR_SELECT_PC] = Bit::High; bits[ADDR_SELECT_LATCH] = Bit::Low; }
    auto addressBusSelectAddressLatch() { bits[ADDR_SELECT_PC] = Bit::Low; bits[ADDR_SELECT_LATCH] = Bit::High; }

    auto dataBusSelectReadMemory() { bits[MEM_SELECT_R_MEM] = Bit::High; }

    auto dataBusSelectWriteInstructionRegister() { bits[MEM_SELECT_W_IR] = Bit::High; }

    auto pcIncrement() { bits[PC_INCREMENT] = Bit::High; }
    auto pcWrite() { bits[PC_WRITE] = Bit::High; }

    auto writeIR() { bits[IR_WRITE] = Bit::High; }
};

auto operator<<(std::ostream&, const ControlBus&) -> std::ostream&;

}

#endif