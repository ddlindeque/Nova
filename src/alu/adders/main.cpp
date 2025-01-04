#include <iostream>

#include <half_adder.h>
#include <full_adder.h>

std::ostream& write_half_adder(std::ostream& os, bool input1, bool input2)
{
    bool digit, carry;
    half_adder()(input1, input2, [&digit, &carry](bool d, bool c) { digit = d; carry = c ;});
    return os << std::boolalpha << "half_adder(" << input1 << ',' << input2 << ")=" << digit << " with carry " << carry;
}

std::ostream& write_full_adder(std::ostream& os, bool prev_carry, bool input1, bool input2)
{
    bool digit, carry;
    full_adder()(input1, input2, prev_carry, [&digit, &carry](bool d, bool c) { digit = d; carry = c ;});
    return os << std::boolalpha << "full_adder(" << prev_carry << ',' << input1 << ',' << input2 << ")=" << digit << " with carry " << carry;
}

int main()
{
    std::cout << std::endl << std::endl << "Half adder" << std::endl;

    write_half_adder(std::cout, false, false) << std::endl;
    write_half_adder(std::cout, false, true) << std::endl;
    write_half_adder(std::cout, true, false) << std::endl;
    write_half_adder(std::cout, true, true) << std::endl;

    write_full_adder(std::cout, false, false, false) << std::endl;
    write_full_adder(std::cout, false, false, true) << std::endl;
    write_full_adder(std::cout, false, true, false) << std::endl;
    write_full_adder(std::cout, false, true, true) << std::endl;
    write_full_adder(std::cout, true, false, false) << std::endl;
    write_full_adder(std::cout, true, false, true) << std::endl;
    write_full_adder(std::cout, true, true, false) << std::endl;
    write_full_adder(std::cout, true, true, true) << std::endl;


    return 0;
}