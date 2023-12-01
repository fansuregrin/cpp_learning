#include "str_blob.h"
#include <iostream>
#include <string>

using namespace std;

ostream& operator<<(ostream& os, const StrBlob& sb) {
    os << "[";
    string sep;
    for (auto it=sb.begin(); it!=sb.end(); ++it) {
        os << sep << *it;
        sep = ", ";
    }
    return os << "]";
}

int main() {
    StrBlob b1;
    {
        StrBlob b2 = {"a", "an", "the"};
        b1 = b2;
        b2.push_back("about");
        b2.front() = "A";
        cout << "b2: " << b2 << endl;
    }

    const StrBlob b3(b1);
    cout << "b1: " << b1 << endl;
    cout << "b3: " << b3 << endl;

    cout << "first element in b1: " << b3.front() << endl;
    b1.front() = "a";
    cout << "first element in b1: " << b3.front() << endl;

    return 0;
}