// topic: overloading and template
//   - Missing Declarations Can Cause the Program to Misbehave

#include <string>
#include <sstream>
#include <iostream>


// Tip:
// Declare every function in an overload set before you define any of the
// functions. That way you don’t have to worry whether the compiler will
// instantiate a call before it sees the function you intended to call.

template <typename T> std::string debug_rep(const T &t);
template <typename T> std::string debug_rep(T *p);
std::string debug_rep(const std::string& s);
std::string debug_rep(char * p);
std::string debug_rep(const char * p);

// print any type we don't otherwise handle
template <typename T>
std::string debug_rep(const T &t) {
    std::ostringstream ret;
    ret << t; // uses T's output operator to print a representation of t
    return ret.str(); // return a copy of the std::string to which ret is bound
}

// print pointers as their pointer value, followed by the object to which the pointer points
template <typename T>
std::string debug_rep(T *p) {
    std::ostringstream ret;
    ret << "pointer: " << p;  // print the pointer's own value
    if (p) {
        ret << " " << debug_rep(*p);  // print the value to which p points
    } else {
        ret << " null pointer";  // or indicate that the p is null
    }
    return ret.str();  // return a copy of the std::string to which ret is bound
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


int main() {
    std::string s("hi");
    const std::string * sp = &s;

    // Calls `debug_rep(const std::std::string &s)`
    std::cout << debug_rep(s) << std::endl;
    // Calls `debug_rep<const std::std::string>(const std::std::string *p)`
    std::cout << debug_rep(&s) << std::endl;
    // Calls `debug_rep<const std::std::string>(const std::std::string *p)`
    std::cout << debug_rep(sp) << std::endl;

    // Calls `debug_rep(const char *p)`
    std::cout << debug_rep("hi world!") << std::endl;

    const char * cp = "hello";
    // Calls `debug_rep(const char *)`
    std::cout << debug_rep(cp) << std::endl;

    return 0;
}