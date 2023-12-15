// topic: template type deduction and references

template <typename T> void f1(T & p) {}
template <typename T> void f2(const T & p) {}
template <typename T> void f3(T && p) {}

int main() {
    int i;
    const int ci = 1;

    // Type Deduction from Lvalue Reference Function Parameters

    // calls to `f1` use the referred-to type of the argument as the template parameter type
    f1(i);  // `i` is an `int`; template parameter `T` is `int`
    f1(ci); // `ci` is a `const int`; template parameter `T` is `const int`
    // f1(5);  // error: argument to a & parameter must be an lvalue

    // If a function parameter has type const T&, normal binding rules say that we can
    // pass any kind of argument—an object (const or otherwise), a temporary, or a literal
    // value. When the function parameter is itself const, the type deduced for T will not be
    // a const type. The const is already part of the function parameter type; therefore, it
    // does not also become part of the template parameter type

    // parameter in `f2` is `const &`; `const` in the argument is irrelevant
    // in each of these three calls, f2's function parameter is inferred as `const int&`
    f2(i);   // i is an int; template parameter T is int
    f2(ci);  // ci is a const int, but template parameter T is int
    f2(5);   // a const & parameter can be bound to an rvalue; T is int

    // Type Deduction from Rvalue Reference Function Parameters

    f3(12);  // argument is an rvalue of type int; template parameter T is int

    // Reference Collapsing and Rvalue Reference Parameters

    // Two exceptions for binding an rvalue reference to an lvalue:
    // 1) When we pass an lvalue (e.g., i) to a function parameter that is an
    //    rvalue reference to a template type parameter (e.g, T&&), the compiler
    //    deduces the template type parameter as the argument’s lvalue reference type.
    // 2) If we **indirectly** create a reference to a reference, then those references “collapse.”
    //    - X& &, X&& &, X& && --> X&
    //    - only X&& && --> X&&

    // argument is an lvalue; template parameter T is `int&`
    f3(i);  // int& && --> int &  (collpasing)
    // argument is an lvalue; template parameter T is `const int&`
    f3(ci); // const int& && --> const int & (collapsing)

    return 0;
}