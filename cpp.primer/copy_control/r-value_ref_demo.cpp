// topic: r-value reference

// Lvalues Persist; Rvalues Are Ephemeral
// 左值持久；右值短暂 

#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int main() {
    int i = 42;

    int & r = i;  // ok
    
    // error: cannot bind rvalue reference of type ‘int&&’ to lvalue of type ‘int’
    // an rvalue reference cannot be bound to an lvalue
    // int && rr = i;
    
    // error: cannot bind non-const lvalue reference of 
    // type ‘int&’ to an rvalue of type ‘int’
    // initial value of reference to non-const must be an lvalue
    // int & r2 = i * 42;

    const int & r3 = i * 42;  // ok

    int && rr2 = i * 42;  // ok

    // NOTE: variables are l-values!
    // error: cannot bind rvalue reference of type ‘int&&’ to lvalue of type ‘int’
    // an rvalue reference cannot be bound to an lvalue
    // int && rr3 = rr2;

    // use `move` to explicitly cast an lvalue to its corresponding rvalue reference type
    int && rr3 = std::move(rr2);

    vector<int> v1{1, 2, 3};
    vector<int> && rr_v = std::move(v1);

    return 0;
}