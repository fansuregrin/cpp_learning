#include "str_vec.h"
#include <iostream>
#include <string>

using namespace std;

ostream& operator<<(ostream& os, const StrVec& sv) {
    os << "[";
    string sep;
    for (auto it=sv.begin(); it!=sv.end(); ++it) {
        os << sep << *it;
        sep = ", ";
    }
    return os << "]";
}

int main() {
    StrVec sv1;
    string s;
    cout << "enter something:\n";
    while (cin >> s) {
        if (s == ":q") break;
        sv1.push_back(s);
    }

    StrVec sv2 = sv1;
    sv2.push_back("tail");

    StrVec sv3;
    sv3 = sv2;
    sv3[2] = "^-^";
    sv3.emplace_back(5, '9');

    cout << "sv1: " << sv1 << endl;
    cout << "sv2: " << sv2 << endl;
    cout << "sv3: " << sv3 << endl;

    return 0;
}
