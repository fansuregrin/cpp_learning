// topic: Variadic Templates

#include <string>
#include <iostream>

using namespace std;

// `Args` is a template parameter pack; rest is a function parameter pack.
// `Args` represents zero or more template type parameters.
// `rest` represents zero or more function parameters
template <typename T, typename... Args>
void foo(const T &t, const Args& ... rest) {

}

template <typename ... Args>
void g(Args ... args) {
    // The `sizeof...` Operator
    // When we need to know how many elements there are in a pack, we can use the
    // `sizeof...` operator.
    cout << "number of type params: " << sizeof...(Args) << endl;  // number of template type parameters
    cout << "number of function params: " << sizeof...(args) << endl;  // number of function parameters
}


int main() {
    int i = 0; double d = 3.14; string s = "how now brown cow";
    foo(i, s, 42, d); // three parameters in the pack
    foo(s, 42, "hi"); // two parameters in the pack
    foo(d, s); // one parameter in the pack
    foo("hi"); // empty pack

    g(i, s, 42, d);

    return 0;
}