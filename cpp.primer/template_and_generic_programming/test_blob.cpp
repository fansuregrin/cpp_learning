#include "blob.h"
#include <iostream>
#include <string>


template <typename T>
std::ostream& operator<<(std::ostream& os, const Blob<T>& b) {
    os << "[";
    std::string sep;
    for (auto it=b.begin(); it!=b.end(); ++it) {
        os << sep << *it;
        sep = ", ";
    }
    return os << "]";
}

int main() {
    Blob<int> squares = {0, 1, 2, 3, 4, 5};
    typedef Blob<int>::size_type size_type;
    for (size_type i=0; i!=squares.size(); ++i) {
        squares[i] = i*i;
    }
    std::cout << "squares: " << squares << std::endl;

    Blob<std::string> grp1 = {"apple", "banana"};
    Blob<std::string> grp2 = {"apple", "banana"};
    std::cout << "grp1: " << grp1 << "\n" << "grp2: " << grp2 << std::endl;

    std::cout << (grp1 == grp2 ? "grp1 == grp2" : "grp1 != grp2") << std::endl;

    return 0;
}