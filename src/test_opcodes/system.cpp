#include "system.h"

namespace Nova
{

    System::System()
        : mclk(controlBus.bits[ControlBus::MCLK_RESET]),
          pc(controlBus.bits[ControlBus::ADDR_SELECT_PC], controlBus.bits[ControlBus::PC_WRITE], addressBus),
          ir(Nova::ConstantBits::alwaysLow, controlBus.bits[ControlBus::IR_WRITE], dataBus)
    {
    }

    auto System::reset() -> void {
        controlBus.reset();
        addressBusSegment.reset();
        addressBus.reset();
        dataBus.reset();
    }

    auto System::pulse() -> bool
    {
        // rising edge
        reset();

        // setup control register
        switch (mclk.count)
        {
        case 0:
            fetch();
            break;
        case 1:
            // Check IR register and mclk to setup next control register
            switch(ir.getValue()) {
                case 0: // nop
                    nop();
                    break;
                case 1:
                    break;
            }
            break;
        }

        // pulse all the components
        if (!ir.pulse())
            return false;
        if (!pc.pulse())
            return false;

        // falling edge

        if (!mclk.pulse())
            return false;
    }

    auto System::fetch() -> void
    {
        controlBus.addressBusSelectPc();
        controlBus.dataBusSelectReadMemory();
        controlBus.dataBusSelectWriteInstructionRegister();
        controlBus.microClockIncrement();
    }

    auto System::nop() -> void
    {
        controlBus.pcIncrement();
        controlBus.microClockReset();
    }
}