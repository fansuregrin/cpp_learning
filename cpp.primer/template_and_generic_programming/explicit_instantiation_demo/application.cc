// Application.cc

#include <vector>
#include <string>
#include "compare.hpp"


// these template types must be instantiated elsewhere in the program
extern template class std::vector<std::string>;
extern template int compare(const int&, const int&);

int main() {
    std::vector<std::string> sv1, sv2;

    compare(4, 3);

    return 0;
}