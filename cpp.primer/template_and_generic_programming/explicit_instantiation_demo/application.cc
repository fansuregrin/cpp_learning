// Application.cc

#include <vector>
#include <string>
#include "compare.hpp"

using namespace std;

// these template types must be instantiated elsewhere in the program
extern template class std::vector<string>;
extern template int compare(const int&, const int&);

int main() {
    vector<string> sv1, sv2;

    compare(4, 3);

    return 0;
}