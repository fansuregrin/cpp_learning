// topic: class template partial specializations

// Note:
// We can partially specialize only a class template. We cannot partially
// specialize a function template.

#include <utility>
#include <iostream>

// original, most general template
template <class T>
struct remove_reference {
    typedef T type;
};

// partial specializations that will be used for lvalue references
template <class T>
struct remove_reference<T&> {
    typedef T type;
};

// partial specializations that will be used for rvalue references
template <class T>
struct remove_reference<T&&> {
    typedef T type;
};

int main() {
    int i;

    // decltype(42) is int, uses the original template
    remove_reference<decltype(42)>::type a;

    // decltype(i) is int&, uses first (T&) partial specialization
    remove_reference<decltype(i)>::type b;

    // decltype(std::move(i)) is int&&, uses second (i.e., T&&) partial specialization
    remove_reference<decltype(std::move(i))>::type c;

    return 0;
}