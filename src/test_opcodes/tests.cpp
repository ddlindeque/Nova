#include "tests.h"

#include <sstream>
#include <iostream>

#undef NDEBUG

#include <assert.h>

#include "bit.h"
#include "logic.h"

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
            bool r1[2] = { false, false };
            Nova::inc<2>(r1);
            assert(r1[0] == true);
            assert(r1[1] == false);
        }
        {
            bool r1[2] = { true, false };
            Nova::inc<2>(r1);
            assert(r1[0] == false);
            assert(r1[1] == true);
        }
        {
            bool r1[2] = { false, true };
            Nova::inc<2>(r1);
            assert(r1[0] == true);
            assert(r1[1] == true);
        }
        {
            bool r1[2] = { true, true };
            Nova::inc<2>(r1);
            assert(r1[0] == false);
            assert(r1[1] == false);
        }
        std::cout << "Logic tests complete" << std::endl;
    }

    auto runTests() -> void
    {
        std::cout << "Running tests.." << std::endl;
        runBitsTests();
        runLogicTests();
        std::cout << "All tests complete" << std::endl << std::endl;
    }

}