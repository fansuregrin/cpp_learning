#include <memory>
#include <iostream>
using namespace std;

class B;

class A {
public:
    A() = default;
    A(shared_ptr<B> ptr) : _ptr(ptr) { }
    ~A() {
        cout << "A::~A()" << endl;
    }

    void setPtr(shared_ptr<B> ptr) {
        _ptr = ptr;
    }
private:
    shared_ptr<B> _ptr;
};

class B {
public:
    B() = default;
    B(shared_ptr<A> ptr) : _ptr(ptr) {}
    ~B() {
        cout << "B::~B()" << endl;
    }

    void setPtr(shared_ptr<A> ptr) {
        _ptr = ptr;
    }
private:
#ifndef USE_WEAKPTR
    shared_ptr<A> _ptr;
#else
    weak_ptr<A> _ptr;
#endif
};


// ```text
// $ g++ shared_ptr_circular_ref.cpp
// $ ./a.out
//
// $ g++ shared_ptr_circular_ref.cpp -DUSE_WEAKPTR
// $ ./a.out
// A::~A()
// B::~B()
// ```
int main() {
    {
        shared_ptr<A> pa{make_shared<A>()}; // a 对象
        shared_ptr<B> pb{make_shared<B>()}; // b 对象
        pa->setPtr(pb);
        pb->setPtr(pa);
    } // 离开作用域，a、b对象相互引用，无法被析构
}