// topic: Argument-Dependent Lookup and Parameters of Class Type

#include <string>
#include <iostream>

int main() {
    std::string s("hello\n");
    
    // This `operator<<` function is defined by `string` library, which is in turn
    // defined in the `std` namespace. Yet we can call it without an `std::` qualifier
    // and without a `using` declaration. Why?
    std::cout << s;
    // We can directly access this function because there is an important exception
    // to the rule that names defined in a namespace are hidden. 
    // When we pass **an object of a class type** to a function, the compiler searches **the namespace
    // in which the argument’s class is defined** in addition to the normal scope lookup. This exception
    // also applies for calls that pass pointers or references to a class type.
    //
    // Thus, for this call, the compiler looks in the `std` namespace, which defines the
    // `ostream` and `string` types.
}