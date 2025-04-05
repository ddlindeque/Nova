#include <iostream>

#include "register.h"
#include "bus.h"
#include "bit.h"
#include "incrementing_register.h"

int main(int argc, char *argv[])
{
    Nova::Bus<1> readEnable;
    Nova::Bus<1> writeEnable;
    Nova::Bus<8> dataBus;

    Nova::Register<8> reg(readEnable, writeEnable, dataBus);

    return 0;
}