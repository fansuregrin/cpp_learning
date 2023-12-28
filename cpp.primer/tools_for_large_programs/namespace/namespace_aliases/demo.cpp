#include "primer.hpp"
#include <iostream>

// A namespace alias can be used to associate a shorter synonym with a namespace name.

namespace primer_4 = cplusplus_primer::fourth_edition;
namespace primer_5 = cplusplus_primer::fifth_edition;

int main() {
    std::cout << primer_4::edition << std::endl;
    std::cout << primer_5::edition << std::endl;
}