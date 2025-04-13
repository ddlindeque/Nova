#include "tests.h"

#include <sstream>
#include <iostream>

#undef NDEBUG

#include <assert.h>

#include "bit.h"
#include "logic.h"
#include "register.h"
#include "ring_counter.h"
#include "ram.h"

namespace Nova
{
    auto runBitsTests() -> void
    {
        std::cout << "Running bit tests..." << std::endl;
        {
            Bit b = Bit::High;
            std::stringstream stm;
            stm << b;
            assert(stm.str() == "H");
        }

        {
            Bit b = Bit::Low;
            std::stringstream stm;
            stm << b;
            assert(stm.str() == "L");
        }

        {
            Bit b = Bit::Undefined;
            std::stringstream stm;
            stm << b;
            assert(stm.str() == "U");
        }
        std::cout << "bit tests complete" << std::endl;
    }

    auto runLogicTests() -> void
    {
        std::cout << "Running Logic tests..." << std::endl;
        {
            // 00 => 01
            bool r1[2] = {false, false};
            Nova::inc<2>(r1);
            assert(r1[0] == false);
            assert(r1[1] == true);
        }
        {
            // 01 => 10
            bool r1[2] = {false, true};
            Nova::inc<2>(r1);
            assert(r1[0] == true);
            assert(r1[1] == false);
        }
        {
            // 10 => 11
            bool r1[2] = {true, false};
            Nova::inc<2>(r1);
            assert(r1[0] == true);
            assert(r1[1] == true);
        }
        {
            // 11 => 00
            bool r1[2] = {true, true};
            Nova::inc<2>(r1);
            assert(r1[0] == false);
            assert(r1[1] == false);
        }
        {
            // 00 => 11
            bool r1[2] = {false, false};
            Nova::dec<2>(r1);
            assert(r1[0] == true);
            assert(r1[1] == true);
        }
        {
            // 01 => 00
            bool r1[2] = {false, true};
            Nova::dec<2>(r1);
            assert(r1[0] == false);
            assert(r1[1] == false);
        }
        {
            // 10 => 01
            bool r1[2] = {true, false};
            Nova::dec<2>(r1);
            assert(r1[0] == false);
            assert(r1[1] == true);
        }
        {
            // 11 => 10
            bool r1[2] = {true, true};
            Nova::dec<2>(r1);
            assert(r1[0] == true);
            assert(r1[1] == false);
        }
        std::cout << "Logic tests complete" << std::endl;
    }

    auto runRegisterTests() -> void
    {
        std::cout << "Running Register tests..." << std::endl;

        {
            Bit we = Bit::Undefined;
            Bit data[] = {Bit::Undefined, Bit::Undefined, Bit::Undefined, Bit::Undefined, Bit::Undefined, Bit::Undefined, Bit::Undefined, Bit::Undefined};
            Bus<1> writeEnabled([&we](size_t)
                                { return we; });
            Bus<8> dataBus([&data](size_t i)
                           { return data[i]; });
            Register<8> reg(writeEnabled, dataBus);

            assert(reg.pulse() == false);
        }

        {
            Bit we = Bit::Undefined;
            Bit data[] = {Bit::Undefined, Bit::Undefined, Bit::Undefined, Bit::Undefined, Bit::Undefined, Bit::Undefined, Bit::Undefined, Bit::Undefined};
            Bus<1> writeEnabled([&we](size_t)
                                { return we; });
            Bus<8> dataBus([&data](size_t i)
                           { return data[i]; });
            Register<8> reg(writeEnabled, dataBus);

            we = Bit::High;
            data[0] = Bit::Low;
            data[1] = Bit::Low;
            data[2] = Bit::High;
            data[3] = Bit::Low;
            data[4] = Bit::Low;
            data[5] = Bit::Low;
            data[6] = Bit::Low;
            data[7] = Bit::Low;
            assert(reg.pulse() == true);

            assert(reg.getValue(1) == Bit::Low);
            assert(reg.getValue(2) == Bit::High);
            assert(reg.getValue(5) == Bit::Low);

            we = Bit::Low;
            data[5] = Bit::High;
            assert(reg.pulse() == true);

            assert(reg.getValue(5) == Bit::Low);

            we = Bit::High;
            assert(reg.pulse() == true);

            assert(reg.getValue(5) == Bit::High);
        }

        {
            Bit we = Bit::Undefined, ie = Bit::Undefined;
            Bit data[] = {Bit::Undefined, Bit::Undefined, Bit::Undefined, Bit::Undefined, Bit::Undefined, Bit::Undefined, Bit::Undefined, Bit::Undefined};
            Bus<1> writeEnabled([&we](size_t)
                                { return we; }),
                incrementEnable([&ie](size_t)
                                { return ie; });
            Bus<8> dataBus([&data](size_t i)
                           { return data[i]; });
            IncrementableRegister<8> reg(incrementEnable, writeEnabled, dataBus);

            we = Bit::High;
            ie = Bit::Low;
            data[0] = Bit::Low;
            data[1] = Bit::Low;
            data[2] = Bit::High;
            data[3] = Bit::Low;
            data[4] = Bit::Low;
            data[5] = Bit::Low;
            data[6] = Bit::Low;
            data[7] = Bit::Low;
            assert(reg.pulse() == true);

            assert(reg.getValue(1) == Bit::Low);
            assert(reg.getValue(2) == Bit::High);
            assert(reg.getValue(5) == Bit::Low);

            we = Bit::Low;
            data[5] = Bit::High;
            assert(reg.pulse() == true);

            assert(reg.getValue(5) == Bit::Low);

            ie = Bit::High;
            assert(reg.pulse() == true);
            assert(reg.getValue(7) == Bit::High);
        }

        {
            Bit we = Bit::Undefined, ie = Bit::Undefined, de = Bit::Undefined;
            Bit data[] = {Bit::Undefined, Bit::Undefined, Bit::Undefined, Bit::Undefined, Bit::Undefined, Bit::Undefined, Bit::Undefined, Bit::Undefined};
            Bus<1> writeEnabled([&we](size_t)
                                { return we; }),
                incrementEnable([&ie](size_t)
                                { return ie; }),
                decrementEnable([&de](size_t)
                                { return de; });
            Bus<8> dataBus([&data](size_t i)
                           { return data[i]; });
            IncrementableDecrementableRegister<8> reg(incrementEnable, decrementEnable, writeEnabled, dataBus);

            we = Bit::High;
            ie = Bit::Low;
            de = Bit::Low;
            data[0] = Bit::Low;
            data[1] = Bit::Low;
            data[2] = Bit::High;
            data[3] = Bit::Low;
            data[4] = Bit::Low;
            data[5] = Bit::Low;
            data[6] = Bit::Low;
            data[7] = Bit::Low;
            assert(reg.pulse() == true);

            assert(reg.getValue(1) == Bit::Low);
            assert(reg.getValue(2) == Bit::High);
            assert(reg.getValue(5) == Bit::Low);

            we = Bit::Low;
            data[5] = Bit::High;
            assert(reg.pulse() == true);

            assert(reg.getValue(5) == Bit::Low);

            ie = Bit::High;
            assert(reg.pulse() == true);
            assert(reg.getValue(7) == Bit::High);

            ie = Bit::Low;
            de = Bit::High;
            assert(reg.pulse() == true);
            assert(reg.getValue(7) == Bit::Low);
        }

        std::cout << "Register tests complete" << std::endl;
    }

    auto runRingCounterTests() -> void
    {
        std::cout << "Running ring counter tests..." << std::endl;
        {
            Bit ie = Bit::Low, ze = Bit::Low;
            Bus<1> incrementEnable([&ie](size_t)
                                   { return ie; }),
                zeroEnable([&ze](size_t)
                           { return ze; });
            RingCounter<3> rc(incrementEnable, zeroEnable);

            ze = Bit::High;
            assert(rc.pulse() == true);
            assert(rc.getValue(0) == Bit::High);
            assert(rc.getValue(1) == Bit::Low);
            assert(rc.getValue(2) == Bit::Low);
        }

        {
            Bit ie = Bit::Low, ze = Bit::Low;
            Bus<1> incrementEnable([&ie](size_t)
                                   { return ie; }),
                zeroEnable([&ze](size_t)
                           { return ze; });
            RingCounter<3> rc(incrementEnable, zeroEnable);

            ze = Bit::High;
            assert(rc.pulse() == true);
            ze = Bit::Low;
            assert(rc.pulse() == true);
            assert(rc.getValue(0) == Bit::High);
            assert(rc.getValue(1) == Bit::Low);
            assert(rc.getValue(2) == Bit::Low);
        }

        {
            Bit ie = Bit::Low, ze = Bit::Low;
            Bus<1> incrementEnable([&ie](size_t)
                                   { return ie; }),
                zeroEnable([&ze](size_t)
                           { return ze; });
            RingCounter<3> rc(incrementEnable, zeroEnable);

            ze = Bit::High;
            assert(rc.pulse() == true);
            ze = Bit::Low;
            ie = Bit::High;
            assert(rc.pulse() == true);
            assert(rc.getValue(0) == Bit::Low);
            assert(rc.getValue(1) == Bit::High);
            assert(rc.getValue(2) == Bit::Low);
            assert(rc.pulse() == true);
            assert(rc.getValue(0) == Bit::Low);
            assert(rc.getValue(1) == Bit::Low);
            assert(rc.getValue(2) == Bit::High);
            assert(rc.pulse() == true);
            assert(rc.getValue(0) == Bit::High);
            assert(rc.getValue(1) == Bit::Low);
            assert(rc.getValue(2) == Bit::Low);
            assert(rc.pulse() == true);
            assert(rc.getValue(0) == Bit::Low);
            assert(rc.getValue(1) == Bit::High);
            assert(rc.getValue(2) == Bit::Low);
            ie = Bit::Low;
            assert(rc.pulse() == true);
            assert(rc.getValue(0) == Bit::Low);
            assert(rc.getValue(1) == Bit::High);
            assert(rc.getValue(2) == Bit::Low);
            ze = Bit::High;
            assert(rc.pulse() == true);
            assert(rc.getValue(0) == Bit::High);
            assert(rc.getValue(1) == Bit::Low);
            assert(rc.getValue(2) == Bit::Low);
        }

        std::cout << "ring counter tests complete" << std::endl;
    }

    auto runRamTests() -> void
    {
        std::cout << "Running RAM tests..." << std::endl;
        {
            Bit we = Bit::Low;
            Nova::Bit data[] = {Nova::Bit::Low, Nova::Bit::Low, Nova::Bit::Low};
            Nova::Bit address[] = {Nova::Bit::Low, Nova::Bit::Low, Nova::Bit::Low, Nova::Bit::Low};

            Nova::Bus<1> writeEnable([&we](size_t)
                                     { return we; });
            Nova::Bus<3> dataBus([&data](size_t i)
                                 { return data[i]; });
            Nova::Bus<4> addressBus([&address](size_t i)
                                    { return address[i]; });

            Nova::Ram<3, 4, 5> ram(writeEnable, dataBus, addressBus);

            Nova::Bus<3> output([&ram](size_t i) { return ram.getValue(i); });

            for (size_t a = 0; a < 16; ++a)
            {
                Nova::setBits<4>(address, a);
                Nova::setBits<3>(data, 0);
                assert(ram.pulse() == true);
            }

            Nova::setBits<4>(address, 7);
            Nova::setBits<3>(data, 4);
            assert(ram.pulse() == true);

            Nova::setBits<4>(address, 9);
            Nova::setBits<3>(data, 5);
            assert(ram.pulse() == true);

            Nova::setBits<4>(address, 0);
            assert(output.getRepresentedValue() == 0);

            Nova::setBits<4>(address, 7);
            assert(output.getRepresentedValue() == 4);

            Nova::setBits<4>(address, 9);
            assert(output.getRepresentedValue() == 5);
        }

        std::cout << "RAM tests complete" << std::endl;
    }

    auto runTests() -> void
    {
        std::cout << "Running tests.." << std::endl;
        runBitsTests();
        runLogicTests();
        runRegisterTests();
        runRingCounterTests();
        std::cout << "All tests complete" << std::endl
                  << std::endl;
    }

}