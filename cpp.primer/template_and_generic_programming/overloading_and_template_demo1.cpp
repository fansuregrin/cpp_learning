// topic: overloading and template
//  - Multiple Viable Templates

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

// print any type we don't otherwise handle
template <typename T>
string debug_rep(const T &t) {
    ostringstream ret;
    ret << t; // uses T's output operator to print a representation of t
    return ret.str(); // return a copy of the string to which ret is bound
}

// print pointers as their pointer value, followed by the object to which the pointer points
template <typename T>
string debug_rep(T *p) {
    ostringstream ret;
    ret << "pointer: " << p;  // print the pointer's own value
    if (p) {
        ret << " " << debug_rep(*p);  // print the value to which p points
    } else {
        ret << " null pointer";  // or indicate that the p is null
    }
    return ret.str();  // return a copy of the string to which ret is bound
}


int main() {
    string s("hi");

    // calls `std::string debug_rep<std::string>(const std::string &t)`
    // only the first version of `debug_rep` is viable.
    // The second version of `debug_rep` requires a pointer parameter,
    // and in this call we passed a nonpointer object.
    // There is no way to instantiate a function template that expects a pointer type
    // from a nonpointer argument, so argument deduction fails.
    cout << debug_rep(s) << endl;

    // There are two viable instantiations:
    //   1) `debug_rep(const string* &)`
    //   2) `debug_rep(string*)`
    // calls `std::string debug_rep<std::string>(std::string *p)`
    cout << debug_rep(&s) << endl;

    const string * sp = &s;

    // Note:
    // When there are several overloaded templates that provide an equally good
    // match for a call, the most specialized version is preferred.

    // There are two viable instantiations:
    //   1) `debug_rep(const string* &)`, instantiation of `debug_rep(const T &)`
    //   2) `debug_rep(const string*)`, instantiation of `debug_rep(T *)`
    // Due to the special rule for overloaded function templates, this call resolves
    // to debug_rep(T*), which is the more **specialized** template.
    // calls `std::string debug_rep<const std::string>(const std::string *p)`
    cout << debug_rep(sp) << endl;

    return 0;
}