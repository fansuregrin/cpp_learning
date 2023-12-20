#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

template <typename T> string debug_rep(const T &t);
template <typename T> string debug_rep(T *p);
string debug_rep(const string& s);
string debug_rep(char * p);
string debug_rep(const char * p);

template <typename T>
string debug_rep(const T &t) {
    ostringstream ret;
    ret << t;
    return ret.str();
}

template <typename T>
string debug_rep(T *p) {
    ostringstream ret;
    ret << "0x" << std::setw(8) << std::setfill('0') << std::hex << p;
    return ret.str();
}

string debug_rep(const string& s) {
    return '"' + s + '"';
}

string debug_rep(char * p) {
    return debug_rep((string)p);
}

string debug_rep(const char * p) {
    return debug_rep((string)p);
}

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

// call `debug_rep` on each argument in the call to print
template <typename ... Args>
ostream& errorMsg(ostream &os, const Args& ... rest) {
    return print(os, debug_rep(rest)...);
}

void fcnName(int a, int b) {}

int main() {
    int i = 0; double d = 3.14; string s = "how now brown cow";
    print(cout, i, s, 42);
    cout << endl;

    errorMsg(cerr, fcnName, i, d, s);

    return 0;
}