#include <boost/multiprecision/cpp_dec_float.hpp>           // include the header
#include <iostream>

using namespace boost::multiprecision;
using BigFloat = cpp_dec_float_50;

int main() {
    BigFloat a = 1.0 / 3.0;
    BigFloat b = sqrt(BigFloat(2));

    std::cout << "1/3 with high precision: " << std::setprecision(51) << a << std::endl;
    std::cout << "Square root of 2: " << std::setprecision(51) << b << std::endl;

    return 0;
}