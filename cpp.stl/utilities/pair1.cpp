#include <utility>
#include <tuple>
#include <cmath>
#include <iostream>

using std::tuple;
using std::pair;

struct Foo {
    Foo(tuple<int, float> t) {
        std::cout << "Foo::Foo(tuple)" << std::endl;
    }

    template <typename... Args>
    Foo(Args ...args) {
        std::cout << "Foo::Foo(args...)" << std::endl;
    }
};

int main() {
    tuple<int, float> t(1, 3.14);
    pair<int, Foo> p1(10, t);
    pair<int, Foo> p2(std::piecewise_construct, std::make_tuple(10), t);
}