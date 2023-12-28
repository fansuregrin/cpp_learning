// topic: Overloading across Multiple `using` Directives

#include <iostream>

namespace A {
    void print(int x) { std::cout << "A::print(" << x << ")" << std::endl; }
}

namespace B {
    void print(double x) { std::cout << "B::print(" << x << ")" << std::endl; }
}

void print(long x) {
    std::cout << "::print(" << x << ")" << std::endl;
}

// using directives create an overload set of functions from different namespaces
using namespace A;
using namespace B;

int main() {
    print(1);
    print(2L);
    print(3.14);
}