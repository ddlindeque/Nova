#include <iostream>

#include "bit.h"
#include "bus.h"
#include "control_bus.h"

int main(int argc, char *argv[])
{
    std::cout << "Hello test_opcodes" << std::endl;
    Nova::ControlBus controlBus;
    controlBus.AddressBusSelectPc();

    std::cout << controlBus << std::endl;
    return 0;
}