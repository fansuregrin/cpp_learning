// topic: `typeid` operator

#include <iostream>
#include <typeinfo>

class Base {
public:
    virtual void print() const {}
};

class Derived: public Base {
public:
    void print() const {}
    void hi() {}
};

int main() {
    Derived d;

   // both pointers point to a Derived object 
    Derived *dp = &d;
    Base *bp = &d;

    // compare the type of two objects at run time
    if (typeid(*bp) == typeid(*dp)) {
        std::cout << "bp and dp point to objects of the same type" << std::endl;
    }

    // test whether the run-time type is a specific type
    if (typeid(*bp) == typeid(Derived)) {
        std::cout << "bp actually points to a Derived" << std::endl;
    }

    // Note that the operands to the typeid are objects—we used *bp, not bp
    // test always fails: the type of bp is pointer to Base
    // The typeid of a pointer (as opposed to the object to which the pointer
    // points) returns the static, compile-time type of the pointer. 
    if (typeid(bp) == typeid(Derived)) {
        // code never executed
    }
}