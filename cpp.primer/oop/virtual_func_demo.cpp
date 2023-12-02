// topic: virtual function

#include <iostream>

using namespace std;

struct B {
    virtual void f1() const {
        cout << "B::f1()" << endl;
    }

    virtual void f2(int a = 10) const {
        cout << "B::f2(" << a << ")" << endl;
    }
};

struct D: B {
    // A function that is virtual in a base class is implicitly virtual in its
    // derived classes.
    // When a derived class overrides a virtual, the parameters in
    // the base and derived classes must match exactly.

    // f1 overrides the virtual funciton in base class `B`
    void f1() const override {
        cout << "D::f1()" << endl;
    }

    // this version of f1 is not a virtual function because it doesn't match any
    // virtual function in its base class `B`
    void f1(int i) {}

    void f2(int a = 20) const override final {
        cout << "D::f2(" << a << ")" << endl;
    }
};

struct D2: D {
    // We can also designate a function as final. Any attempt to override a function that
    // has been defined as final will be flagged as an error

    // cannot override 'final' function "D::f2"
    // void f2(int a) const override {}
};

int main() {
    B b;
    D d;
    B * p1 = &d;
    B & r1 = d;

    b.f1();  // calls `B::f1()`
    d.f1();  // calls `D::f1()`

    // dynamic binding happens when a virtual member function is
    // called through a reference or a pointer to a base-class type
    //
    // dynamic binding occurs
    p1->f1();  // calls `D::f1()`, but p1 points to the `B` type
    r1.f1();  // calls `D::f1()`, but p1 refers to the `B` type

    // p1->f1(0); // error!

    // When a call is made through a reference or pointer to base, the default
    // argument(s) will be those defined in the base class. The base-class arguments 
    // will be used even when the derived version of the function is run.
    p1->f2();  // calls `D::f2()`, but the value of `a` is 10!!!
    // Note: Virtual functions that have default arguments should use the same argument
    // values in the base and derived classes.

    return 0;
}