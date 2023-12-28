#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>


template <typename T> std::string debug_rep(const T &t);
template <typename T> std::string debug_rep(T *p);
std::string debug_rep(const std::string& s);
std::string debug_rep(char * p);
std::string debug_rep(const char * p);

template <typename T>
std::string debug_rep(const T &t) {
    std::ostringstream ret;
    ret << t;
    return ret.str();
}

template <typename T>
std::string debug_rep(T *p) {
    std::ostringstream ret;
    ret << "0x" << std::setw(8) << std::setfill('0') << std::hex << p;
    return ret.str();
}

std::string debug_rep(const std::string& s) {
    return '"' + s + '"';
}

std::string debug_rep(char * p) {
    return debug_rep((std::string)p);
}

std::string debug_rep(const char * p) {
    return debug_rep((std::string)p);
}

// function to end the recursion and print the last element
// this function must be declared before the variadic version of print is defined
template <typename T>
std::ostream& print(std::ostream &os, const T &t) {
    return os << t;  // no separator after the last element in the pack
}

template <typename T, typename ... Args>
std::ostream& print(std::ostream &os, const T &t, const Args& ... rest) {
    os << t << ", ";  // print the first argument
    return print(os, rest...);  // recursive call; print the other arguments
}

// call `debug_rep` on each argument in the call to print
template <typename ... Args>
std::ostream& errorMsg(std::ostream &os, const Args& ... rest) {
    return print(os, debug_rep(rest)...);
}

void fcnName(int a, int b) {}

int main() {
    int i = 0; double d = 3.14; std::string s = "how now brown cow";
    print(std::cout, i, s, 42);
    std::cout << std::endl;

    errorMsg(std::cerr, fcnName, i, d, s);

    return 0;
}