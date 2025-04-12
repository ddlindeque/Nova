#include <iostream>

#include "bit.h"
#include "bus.h"
#include "register.h"
#include "logic.h"

#include "tests.h"

int main(int argc, char *argv[])
{
    Nova::runTests();

    std::cout << "Hello test_opcodes" << std::endl;

    Nova::Bit enableWriteBit = Nova::Bit::Low;
    Nova::Bus<1> enableWrite([&enableWriteBit](size_t)
                             { return enableWriteBit; });

    Nova::Bit enaleIncrementBit = Nova::Bit::Low;
    Nova::Bus<1> enaleIncrement([&enaleIncrementBit](size_t)
                                { return enaleIncrementBit; });

    Nova::Bit dataBits[8] = {Nova::Bit::Low, Nova::Bit::Low, Nova::Bit::Low, Nova::Bit::Low, Nova::Bit::Low, Nova::Bit::Low, Nova::Bit::Low, Nova::Bit::Low};
    Nova::Bus<8> dataBus([&dataBits](size_t index)
                         { return dataBits[index]; });

    Nova::IncrementableRegister<8> reg(enaleIncrement, enableWrite, dataBus);

    if (!reg.pulse())
        abort();
    std::cout << reg << std::endl;

    enableWriteBit = Nova::Bit::High;
    dataBits[0] = Nova::Bit::High;
    if (!reg.pulse())
        abort();
    std::cout << reg << std::endl;

    enableWriteBit = Nova::Bit::Low;
    dataBits[1] = Nova::Bit::High;
    if (!reg.pulse())
        abort();
    std::cout << reg << std::endl;

    enableWriteBit = Nova::Bit::High;
    if (!reg.pulse())
        abort();
    std::cout << reg << std::endl;

    enableWriteBit = Nova::Bit::Low;
    enaleIncrementBit = Nova::Bit::High;

    if (!reg.pulse())
        abort();
    std::cout << reg << std::endl;

    if (!reg.pulse())
        abort();
    std::cout << reg << std::endl;

    if (!reg.pulse())
        abort();
    std::cout << reg << std::endl;

    if (!reg.pulse())
        abort();
    std::cout << reg << std::endl;

    if (!reg.pulse())
        abort();
    std::cout << reg << std::endl;

    if (!reg.pulse())
        abort();
    std::cout << reg << std::endl;

    if (!reg.pulse())
        abort();
    std::cout << reg << std::endl;

    if (!reg.pulse())
        abort();
    std::cout << reg << std::endl;

    if (!reg.pulse())
        abort();
    std::cout << reg << std::endl;

    return 0;
}