#include <iostream>

#include <gate_and.h>

std::ostream& write_and(std::ostream& os, bool input1, bool input2)
{
    bool output;
    gate_and()(input1, input2, [&output](bool res) { output = res ;});
    return os << std::boolalpha << "and(" << input1 << ',' << input2 << ")=" << output;
}

int main()
{
    std::cout << std::endl << std::endl << "AND Gate" << std::endl;

    write_and(std::cout, false, false) << std::endl;
    write_and(std::cout, false, true) << std::endl;
    write_and(std::cout, true, false) << std::endl;
    write_and(std::cout, true, true) << std::endl;
    return 0;
}