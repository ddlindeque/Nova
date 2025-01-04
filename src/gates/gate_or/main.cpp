#include <iostream>

#include <gate_or.h>

std::ostream& write_or(std::ostream& os, bool input1, bool input2)
{
    bool output;
    gate_or()(input1, input2, [&output](bool res) { output = res ;});
    return os << std::boolalpha << "or(" << input1 << ',' << input2 << ")=" << output;
}

int main()
{
    std::cout << std::endl << std::endl << "OR Gate" << std::endl;

    write_or(std::cout, false, false) << std::endl;
    write_or(std::cout, false, true) << std::endl;
    write_or(std::cout, true, false) << std::endl;
    write_or(std::cout, true, true) << std::endl;
    return 0;
}