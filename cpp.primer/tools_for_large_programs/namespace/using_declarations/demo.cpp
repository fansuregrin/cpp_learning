#include <iostream>
#include "primer.hpp"

// A using declaration introduces only one namespace member at a time. It allows us
// to be very specific regarding which names are used in our programs.

int main() {
    using std::cout;
    using std::endl;
    using cplusplus_primer::tools_for_large_programs::using_declarations::value;

    cout << value << endl;
}