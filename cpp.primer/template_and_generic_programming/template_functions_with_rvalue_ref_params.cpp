// topic: Writing Template Functions with Rvalue Reference Parameters

// Note!!!
// It is surprisingly hard to write code that is correct when the types involved
// might be plain (nonreference) types or reference types.

#include <iostream>


template <typename T>
T fcn(T val) {
    return ++val;
}

// The fact that the template parameter can be deduced to a reference type can have
// surprising impacts on the code inside the template:

template <typename T>
void f3(T && val) {
    T t = val;  // copy or binding a reference?
    t = fcn(t); // does the assignment change only t or val and t?
    if (t == val) {  // always true if T is a reference type
        std::cout << "t == val" << std::endl;
    } else {
        std::cout << "t != val" << std::endl;
    }
}

int main() {
    int i;

    // When we call f3 on an rvalue, such as the literal 42, T is int. In this case, the local
    // variable t has type int and is initialized by copying the value of the parameter val.
    // When we assign to t, the parameter val remains unchanged.
    f3(42);

    // when we call f3 on the lvalue i, then T is int&. When we
    // define and initialize the local variable t, that variable has type int&. The initialization
    // of t binds t to val. When we assign to t, we change val at the same time. In this
    // instantiation of f3, the if test will always yield true.
    f3(i);

    return 0;
}