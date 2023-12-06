#include "blob.h"
#include <iostream>
#include <string>

using namespace std;

template <typename T>
ostream& operator<<(ostream& os, const Blob<T>& b) {
    os << "[";
    string sep;
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
    cout << "squares: " << squares << endl;

    return 0;
}