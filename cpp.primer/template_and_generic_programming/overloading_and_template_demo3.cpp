// topic: overloading and template
//   - Missing Declarations Can Cause the Program to Misbehave

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

// Tip:
// Declare every function in an overload set before you define any of the
// functions. That way you don’t have to worry whether the compiler will
// instantiate a call before it sees the function you intended to call.

template <typename T> string debug_rep(const T &t);
template <typename T> string debug_rep(T *p);
string debug_rep(const string& s);
string debug_rep(char * p);
string debug_rep(const char * p);

// print any type we don't otherwise handle
template <typename T>
string debug_rep(const T &t) {
    ostringstream ret;
    ret << t; // uses T's output operator to print a representation of t
    return ret.str(); // return a copy of the string to which ret is bound
}

// print pointers as their pointer value, followed by the object to which the pointer pointsv
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

string debug_rep(const string& s) {
    return '"' + s + '"';
}

string debug_rep(char * p) {
    return debug_rep((string)p);
}

string debug_rep(const char * p) {
    return debug_rep((string)p);
}


int main() {
    string s("hi");
    const string * sp = &s;

    // Calls `debug_rep(const std::string &s)`
    cout << debug_rep(s) << endl;
    // Calls `debug_rep<const std::string>(const std::string *p)`
    cout << debug_rep(&s) << endl;
    // Calls `debug_rep<const std::string>(const std::string *p)`
    cout << debug_rep(sp) << endl;

    // Calls `debug_rep(const char *p)`
    cout << debug_rep("hi world!") << endl;

    const char * cp = "hello";
    // Calls `debug_rep(const char *)`
    cout << debug_rep(cp) << endl;

    return 0;
}