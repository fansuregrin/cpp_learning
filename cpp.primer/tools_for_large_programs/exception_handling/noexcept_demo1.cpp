// topic: the `noexcept` exception specification

#include <stdexcept>

// Under the new standard, a function can specify that it does not throw exceptions by
// providing a **noexcept** specification. The keyword noexcept following the function
// parameter list indicates that the function won’t throw.

void recoup(int) noexcept {}  // won't throw
void alloc(int) {}  // might throw

// The noexcept specifier must appear on all of the declarations and the
// corresponding definition of a function or on none of them. 
//   - The specifier precedes a trailing return
//   - We can specify noexcept on the declaration and definition of a function pointer
//   - In a member function the noexcept specifier follows any const or reference qualifiers,
//     and it precedes final, override, or = 0 on a virtual function


/// Violating the Exception Specification
// The compiler does not check the noexcept specification at compile time. 
// If a noexcept function does throw, terminate is called, thereby enforcing
// the promise not to throw at run time.
//
// for example:
//
// void f() noexcept {
//     // warning: throw will always call terminate() [-Wterminate]
//     throw std::exception();
// }

/// Arguments to the noexcept Specification
// The noexcept specifier takes an optional argument that must be convertible to
// bool: If the argument is true, then the function won’t throw; if the argument is
// false, then the function might throw

void func1() noexcept(true) {}  // func1 won't throw
void func2() noexcept(false) {}  // func2 can throw

/// The noexcept Operator
// The noexcept operator is a unary operator that returns a bool rvalue
// constant expression that indicates whether a given expression might throw

// func3 has same exception specifier as func1
void func3() noexcept(noexcept(func1())) {}

int main() {
    /// Exception Specifications and Pointers, Virtuals, and Copy Control
    //
    // (1) If we declare a pointer that has a nonthrowing exception specification, we can use 
    //     that pointer only to point to similarly qualified functions. A pointer that specifies
    //     (explicitly or implicitly) that it might throw can point to any function, even if
    //     that function includes a promise not to throw.
    void (*pf1)(int) noexcept = recoup;  // both recoup and pf1 promise not to throw
    void (*pf2)(int) = recoup;  // ok: recoup won't throw; it doesn't matter that pf2 might
    pf1 = alloc;
    pf2 = alloc;

}

// (2) If a virtual function includes a promise not to throw, the inherited virtuals must also
//     promise not to throw. On the other hand, if the base allows exceptions, it is okay for
//     the derived functions to be more restrictive and promise not to throw.

class Base {
public:
    virtual double f1(double) noexcept;  // doesn't throw
    virtual int f2() noexcept(false);
    virtual void f3();
};

class Derived: public Base {
public:
    // error: looser throw specifier for ‘virtual double Derived::f1(double)’
    // double f1(double);
    int f2() noexcept(true);
    void f3() noexcept;
};