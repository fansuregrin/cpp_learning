// topic: `dynamic_cast` operator

#include <iostream>
#include <stdexcept>

class Base {
public:
    virtual void print() const {}
};

class Derived: public Base {
public:
    void print() const {}
    void hi() {}
};

void check(Base *bp) {
    if (Derived *dp = dynamic_cast<Derived*>(bp)) {
        // If bp points to a Derived object, then the cast will initialize dp to point to the
        // Derived object to which bp points. In this case, it is safe for the code inside the if
        // to use Derived operations.
        std::cout << "use the Derived object to which dp points" << std::endl;
        dp->hi();
    } else {
        // Otherwise, the result of the cast is 0. If dp is 0, the condition in the if fails.
        // In this case, the else clause does processing appropriate to Base instead.
        std::cout << "use the Base object to which bp points" << std::endl;
    }
}

void f(const Base &b) {
    // When a cast to a reference type fails, the cast throws a std::bad_cast exception
    try {
        const Derived &d = dynamic_cast<const Derived&>(b);
    } catch (std::bad_cast) {
        std::cout << "cannot cast" << std::endl;
    }
}

int main() {
    Base b;
    Derived d;
    check(&b);
    check(&d);

    // We can do a dynamic_cast on a null pointer; the result is a null pointer of
    // the requested type.
    check(nullptr);

    f(b);
    f(d);
}