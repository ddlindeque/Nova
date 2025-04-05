#ifndef __SYSTEMH
#define __SYSTEMH

#include <ostream>
#include "bit.h"
#include "bus.h"
#include "register.h"
#include "incrementing_register.h"
#include "ring_counter.h"

namespace Nova
{
    struct System
    {
        static const size_t CONTROL_BUS_WIDTH = 11;
        typedef Bus<CONTROL_BUS_WIDTH> ControlBus;

        struct ControlLines
        {
            static const size_t MICROINSTRUCTIONCOUNTER_RESET = 0;

            static const size_t PC_READ = 1;
            static const size_t PC_WRITE = 2;
            static const size_t PC_INC = 3;
            static const size_t PC_ZERO = 4;

            static const size_t REG_A_READ = 5;
            static const size_t REG_A_WRITE = 6;

            static const size_t REG_B_READ = 7;
            static const size_t REG_B_WRITE = 8;

            static const size_t INSTRUCTION_REG_READ = 9;
            static const size_t INSTRUCTION_REG_WRITE = 10;

            static const size_t ADDRESS_LATCH_READ = 11;
            static const size_t ADDRESS_LATCH_WRITE = 12;
        };

        struct MicroInstructionAddress
        {
            RingCounter<5> counter;
            Bus<1> resetEnable;

            MicroInstructionAddress() : counter(resetEnable) {}

            auto connect(ControlBus &controlBus) -> void
            {
                resetEnable.connect([&controlBus](size_t)
                                    { return controlBus.getValue(ControlLines::MICROINSTRUCTIONCOUNTER_RESET); });
            }

            auto pulse() -> bool
            {
                return counter.pulse();
            }
        } microInstructionAddress; // Address of the next micro-instruction

        struct ProgramCounter
        {
            Bus<18> addressBus;

            IncrementingRegister<16> reg;
            Bus<1> readEnable;
            Bus<1> writeEnable;
            Bus<1> incrementEnable;
            Bus<1> zeroEnable;

            ProgramCounter(Bus<18> &addressBus) : reg(readEnable, writeEnable, incrementEnable, zeroEnable, addressBus) {}

            auto connect(ControlBus &controlBus) -> void
            {
                readEnable.connect([&controlBus](size_t)
                                   { return controlBus.getValue(ControlLines::PC_READ); });
                writeEnable.connect([&controlBus](size_t)
                                    { return controlBus.getValue(ControlLines::PC_WRITE); });
                incrementEnable.connect([&controlBus](size_t)
                                        { return controlBus.getValue(ControlLines::PC_INC); });
                zeroEnable.connect([&controlBus](size_t)
                                   { return controlBus.getValue(ControlLines::PC_ZERO); });
            }

            auto pulse() -> bool
            {
                return reg.pulse();
            }
        } pc; // Program Counter

        struct Register
        {
            Nova::Register<8> reg;
            Bus<1> readEnable;
            Bus<1> writeEnable;

            Register(Bus<8> &dataBus) : reg(readEnable, writeEnable, dataBus) {}

            auto pulse() -> bool
            {
                return reg.pulse();
            }
        };

        struct RegisterA : public Register
        {
            RegisterA(Bus<8> &dataBus) : Register(dataBus) {}

            auto connect(ControlBus &controlBus) -> void
            {
                readEnable.connect([&controlBus](size_t)
                                   { return controlBus.getValue(ControlLines::REG_A_READ); });
                writeEnable.connect([&controlBus](size_t)
                                    { return controlBus.getValue(ControlLines::REG_A_WRITE); });
            }
        } regA;

        struct RegisterB : public Register
        {
            RegisterB(Bus<8> &dataBus) : Register(dataBus) {}

            auto connect(ControlBus &controlBus) -> void
            {
                readEnable.connect([&controlBus](size_t)
                                   { return controlBus.getValue(ControlLines::REG_B_READ); });
                writeEnable.connect([&controlBus](size_t)
                                    { return controlBus.getValue(ControlLines::REG_B_WRITE); });
            }
        } regB;

        struct InstructionRegister : public Register
        {
            InstructionRegister(Bus<8> &dataBus) : Register(dataBus) {}

            auto connect(ControlBus &controlBus) -> void
            {
                readEnable.connect([&controlBus](size_t)
                                   { return controlBus.getValue(ControlLines::INSTRUCTION_REG_READ); });
                writeEnable.connect([&controlBus](size_t)
                                    { return controlBus.getValue(ControlLines::INSTRUCTION_REG_WRITE); });
            }
        } ir;

        ControlBus controlBus;

        Nova::Bus<18> addressBus;

        Nova::Bus<8> dataBus;

        System();
        System(const System &) = delete;
        System(System &&) = delete;
        auto operator=(const System &) -> System & = delete;
        auto operator=(System &&) -> System & = delete;

        auto connect() -> void
        {
            microInstructionAddress.connect(controlBus);
            pc.connect(controlBus);
            regA.connect(controlBus);
            regB.connect(controlBus);
            ir.connect(controlBus);
        }

        auto pulse() -> bool
        {
            if (!microInstructionAddress.pulse())
                return false;
            if (!pc.pulse())
                return false;
            if (!regA.pulse())
                return false;
            if (!regB.pulse())
                return false;
            if (!ir.pulse())
                return false;

            return true;
        }
    };

    auto operator<<(std::ostream &, const System &) -> std::ostream &;

}

#endif