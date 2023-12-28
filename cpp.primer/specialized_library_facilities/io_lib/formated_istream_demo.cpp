// topic: format istream

#include <iostream>
#include <iomanip>
#include <sstream>


int main() {
    char ch;

    std::istringstream is1("a b c\nd");
    while (is1 >> ch) {
        std::cout << ch;
    }
    std::cout << std::endl;

    std::istringstream is2("a b c\nd");
    is2 >> std::noskipws;
    while (is2 >> ch) {
        std::cout << ch;
    }
    std::cout << std::endl << std::skipws;
}