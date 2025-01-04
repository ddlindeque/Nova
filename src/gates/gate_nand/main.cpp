#include <iostream>

#include <gate_nand.h>

std::ostream& write_nand(std::ostream& os, bool input1, bool input2)
{
    bool output;
    gate_nand()(input1, input2, [&output](bool res) { output = res ;});
    return os << std::boolalpha << "nand(" << input1 << ',' << input2 << ")=" << output;
}

int main()
{
    std::cout << std::endl << std::endl << "NAND Gate" << std::endl;

    write_nand(std::cout, false, false) << std::endl;
    write_nand(std::cout, false, true) << std::endl;
    write_nand(std::cout, true, false) << std::endl;
    write_nand(std::cout, true, true) << std::endl;
    return 0;
}