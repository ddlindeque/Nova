#include <iostream>

#include <gate_xor.h>

std::ostream& write_xor(std::ostream& os, bool input1, bool input2)
{
    bool output;
    gate_xor()(input1, input2, [&output](bool res) { output = res ;});
    return os << std::boolalpha << "xor(" << input1 << ',' << input2 << ")=" << output;
}

int main()
{
    write_xor(std::cout, false, false) << std::endl;
    write_xor(std::cout, false, true) << std::endl;
    write_xor(std::cout, true, false) << std::endl;
    write_xor(std::cout, true, true) << std::endl;
    return 0;
}