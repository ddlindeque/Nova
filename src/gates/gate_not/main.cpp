#include <iostream>

#include <gate_not.h>

std::ostream& write_not(std::ostream& os, bool input)
{
    bool output;
    gate_not()(input, [&output](bool res) { output = res ;});
    return os << std::boolalpha << "not(" << input << ")=" << output;
}

int main()
{
    write_not(std::cout, false) << std::endl;
    write_not(std::cout, true) << std::endl;
    return 0;
}