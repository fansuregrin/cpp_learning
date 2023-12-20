#include <iostream>

using namespace std;

// function to end the recursion and print the last element
// this function must be declared before the variadic version of print is defined
template <typename T>
ostream& print(ostream &os, const T &t) {
    return os << t;  // no separator after the last element in the pack
}

template <typename T, typename ... Args>
ostream& print(ostream &os, const T &t, const Args& ... rest) {
    os << t << ", ";  // print the first argument
    return print(os, rest...);  // recursive call; print the other arguments
}

int main() {
    int i = 0; double d = 3.14; string s = "how now brown cow";
    print(cout, i, s, 42);
    cout << endl;

    return 0;
}