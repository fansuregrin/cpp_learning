// topic: forwarding

// Some functions need to forward one or more of their arguments with their types
// unchanged to another, forwarded-to, function. In such cases, we need to preserve
// everything about the forwarded arguments, including whether or not the argument
// type is const, and whether the argument is an lvalue or an rvalue.

#include <iostream>
#include <utility>

template <typename F, typename T1, typename T2>
void flip1(F f, T1 t1, T2 t2) {
    f(t2, t1);
}

template <typename F, typename T1, typename T2>
void flip2(F f, T1 && t1, T2 && t2) {
    f(t2, t1);
}

template <typename F, typename T1, typename T2>
void flip3(F f, T1 && t1, T2 && t2) {
    f(std::forward<T2>(t2), std::forward<T1>(t1));
}

void f(int v1, int& v2) {  // note v2 is a reference
    ++v2;
    std::cout <<  "in f: v1 = " << v1 << ", v2 = " << v2 << std::endl;
}

void g(int &&v1, int& v2) {
    ++v2;
    std::cout <<  "in g: v1 = " << v1 << ", v2 = " << v2 << std::endl;
}

int main() {
    using namespace std;

    int i = 2, j = 2;
    
    f(42, i); // f changes its argument i
    flip1(f, j, 42);  // f called through flip1 leaves j unchanged
    cout << "i = " << i << ", j = " << j << endl;  // i = 3, j = 2

    // The problem is that j is passed to the t1 parameter in flip1. That parameter has is
    // a plain, nonreference type, int, not an int&. That is, the instantiation of this call to
    // flip1 is `void flip1(void(*fcn)(int, int&), int t1, int t2)`.
    // The value of j is copied into t1. The reference parameter in f is bound to t1, not to j.


    /* Defining Function Parameters That Retain Type Information */

    // **Notes**:
    // A function parameter that is an rvalue reference to a template type
    // parameter (i.e., T&&) preserves the constness and lvalue/rvalue property of
    // its corresponding argument.

    i = j = 2;
    f(42, i);
    flip2(f, j, 42);
    cout << "i = " << i << ", j = " << j << endl;  // i = 3, j = 3
    // in flip2, the type deduced for T1 is int&, which means
    // that the type of t1 collapses to int&. The reference t1 is bound to j.

    // This version of flip2 solves one half of our problem. Our flip2 function works
    // fine for functions that take lvalue references but cannot be used to call a function that
    // has an rvalue reference parameter.
    // i = j = 2;
    // g(42, i);
    // flip2(g, j, 42); // error: cannot bind rvalue reference of type ‘int&&’ to lvalue of type ‘int’
    // the function parameter (i.e. t2) is a lvalue expression.


    /* Using std::forward to Preserve Type Information in a Call */

    // **Notes**:
    // When used with a function parameter that is an rvalue reference to template
    // type parameter (T&&), forward preserves all the details about an
    // argument’s type.

    // the return type of forward<T> is T&&

    i = j = 2;
    g(42, i);
    flip3(g, j, 42);
    cout << "i = " << i << ", j = " << j << endl;  // i = 3, j = 3
    // j is a lvalue of int, so T1 is deduced as `int &`;
    // 42 is a rvalue of int, so T2 is deduced as `int &&`.
    // Thus, std::forward<T2>(t2) returns a `int&& &&` which collapses to `int&&`;
    // std::forward<T1>(t1) returns a `int& &&` which collapses to `int&`.

    return 0;
}