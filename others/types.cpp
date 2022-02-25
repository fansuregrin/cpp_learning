#include <iostream>
#include <limits>

using namespace std;

int main(){
    std::cout 
    << "wchar_t: " << sizeof(wchar_t) << " bytes" << std::endl
    << "bool: " << sizeof(bool) << " bytes" << std::endl
    << "nullptr: " << sizeof(nullptr) << " bytes" << std::endl
    << "min of int: " << numeric_limits<int>::min() << endl
    << "max of int: " << numeric_limits<int>::max() << endl
    ;
    return 0;
}
