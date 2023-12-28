// topic: Variadic Templates

#include <string>
#include <iostream>


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
    std::cout << "number of type params: " << sizeof...(Args) << std::endl;  // number of template type parameters
    std::cout << "number of function params: " << sizeof...(args) << std::endl;  // number of function parameters
}


int main() {
    int i = 0; double d = 3.14; std::string s = "how now brown cow";
    foo(i, s, 42, d); // three parameters in the pack
    foo(s, 42, "hi"); // two parameters in the pack
    foo(d, s); // one parameter in the pack
    foo("hi"); // empty pack

    g(i, s, 42, d);

    return 0;
}