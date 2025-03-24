#include "and_gate.h"
#include "nand_gate.h"
#include "or_gate.h"
#include "nor_gate.h"
#include "nxor_gate.h"
#include "xor_gate.h"
#include "not_gate.h"

#include <iostream>

using namespace Nova::hardware;

template<typename GATE>
auto assert_unary_gate(const char *file, const int line, const char* msg, bool input, bool expected) -> void
{
    GATE gate;

    // Setup callbacks
    bool actual;
    gate.registerListener(GATE::PIN_DATA, [&actual](bool value, bool force) {
        actual = value;
    });

    // Initialise
    gate.setInput(GATE::PIN_INPUT, false, true);

    // Setup
    gate.setInput(GATE::PIN_INPUT, input);

    // Assert
    if (actual != expected) {
        std::cerr << file << ':' << line << ' ' << msg << "; pin INPUT = " << input << "; expected = " << expected << "; actual = " << actual << std::endl;
        exit(1);
    }
}

#define TEST_UNARY(GATE, msg, input, expected) assert_unary_gate<GATE>(__FILE__, __LINE__, msg, input, expected)

template<typename GATE>
auto assert_binary_gate(const char *file, const int line, const char* msg, bool a, bool b, bool expected) -> void
{
    GATE gate;

    // Setup callbacks
    bool actual;
    gate.registerListener(GATE::PIN_DATA, [&actual](bool value, bool force) { actual = value; });

    // Initialise
    gate.setInput(GATE::PIN_A, false, true);
    gate.setInput(GATE::PIN_B, false, true);

    // Setup
    gate.setInput(GATE::PIN_A, a);
    gate.setInput(GATE::PIN_B, b);

    // Assert
    if (actual != expected) {
        std::cerr << file << ':' << line << ' ' << msg << "; pin A = " << a << "; pin B = " << b << "; expected = " << expected << "; actual = " << actual << std::endl;
        exit(1);
    }
}

#define TEST_BINARY(GATE, msg, a, b, expected) assert_binary_gate<GATE>(__FILE__, __LINE__, msg, a, b, expected)

auto main(int argc, char* argv[]) -> int
{
    TEST_UNARY(NotGate, "NotGate", false, true);
    TEST_UNARY(NotGate, "NotGate", true, false);

    TEST_BINARY(AndGate, "AndGate", false, false, false);
    TEST_BINARY(AndGate, "AndGate", false, true, false);
    TEST_BINARY(AndGate, "AndGate", true, false, false);
    TEST_BINARY(AndGate, "AndGate", true, true, true);

    TEST_BINARY(NandGate, "NandGate", false, false, true);
    TEST_BINARY(NandGate, "NandGate", false, true, true);
    TEST_BINARY(NandGate, "NandGate", true, false, true);
    TEST_BINARY(NandGate, "NandGate", true, true, false);

    TEST_BINARY(OrGate, "OrGate", false, false, false);
    TEST_BINARY(OrGate, "OrGate", false, true, true);
    TEST_BINARY(OrGate, "OrGate", true, false, true);
    TEST_BINARY(OrGate, "OrGate", true, true, true);

    TEST_BINARY(NorGate, "NorGate", false, false, true);
    TEST_BINARY(NorGate, "NorGate", false, true, false);
    TEST_BINARY(NorGate, "NorGate", true, false, false);
    TEST_BINARY(NorGate, "NorGate", true, true, false);

    TEST_BINARY(XorGate, "XorGate", false, false, false);
    TEST_BINARY(XorGate, "XorGate", false, true, true);
    TEST_BINARY(XorGate, "XorGate", true, false, true);
    TEST_BINARY(XorGate, "XorGate", true, true, false);

    TEST_BINARY(NxorGate, "NxorGate", false, false, true);
    TEST_BINARY(NxorGate, "NxorGate", false, true, false);
    TEST_BINARY(NxorGate, "NxorGate", true, false, false);
    TEST_BINARY(NxorGate, "NxorGate", true, true, true);
    
    return 0;
}