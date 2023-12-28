// topic: overloading and template
//  - Nontemplate and Template Overloads
//  - Overloaded Templates and Conversions

#include <string>
#include <sstream>
#include <iostream>


// print any type we don't otherwise handle
template <typename T>
std::string debug_rep(const T &t) {
    std::ostringstream ret;
    ret << t; // uses T's output operator to print a representation of t
    return ret.str(); // return a copy of the string to which ret is bound
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
    return ret.str();  // return a copy of the string to which ret is bound
}

std::string debug_rep(const std::string& s) {
    return '"' + s + '"';
}


int main() {
    std::string s = "hi";

    // Note:
    // When a nontemplate function provides an equally good match for a call as a
    // function template, the nontemplate version is preferred.

    // There are two equally good viable functions:
    //   1) debug_rep<string>(const string&)
    //   2）debug_rep(const string&)
    // a nontemplate function is preferred over equally good match(es) to a function template
    // This calls `string debug_rep(const string&)`.
    std::cout << debug_rep(s) << std::endl;

    // There are three viable funcitons:
    //   1) `debug_rep(const T&)`, with T bound to char[10]
    //   2) `debug_rep(T*)`, with T bound to const char
    //   3) `debug_rep(const string&)`, which requires a conversion from `const char*` to `string`
    // Both templates provide an exact match to the argument—the second template
    // requires a (permissible) conversion from array to pointer, and that conversion is
    // considered as an exact match for function-matching purposes. The
    // nontemplate version is viable but requires a **user-defined conversion**. That function is
    // less good than an exact match, leaving the two templates as the possible functions to
    // call. As before, the T* version is more specialized and is the one that will be selected.
    //
    // This will call `debug_rep<const char>(const char *)`
    std::cout << debug_rep("hi world!") << std::endl;
    // However, this function donot handle character pointers as strings as we wanted. 
    // We can define two more nontemplate overloads specifically for character pointers.
    // Please see "overloading and template demo3".

    return 0;
}