#include <memory>

using namespace std;

int main() {
    // bad practice
    // double free !!!
    shared_ptr<int> p1(new int{0});
    shared_ptr<int> p2(p1.get());

    // good practice
    // shared_ptr<int> p1{make_shared<int>(0)};
    // shared_ptr<int> p2{p1};
}