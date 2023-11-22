// Topic: Avoiding Ambiguous Conversions
// 
// Multiple conversion paths may cause ambiguity.
//
// There are two ways that multiple conversion paths can occur.
//   - The first happens when two classes provide mutual conversions.
//   - The second way to generate multiple conversion paths is to define
//     multiple conversions from or to types that are themselves related
//     by conversions.


// --------------------------------------------------------------------
// Example for Mutual Conversions
// It is usually a bad idea to have mutual conversions between two class types.

#include<iostream>

using namespace std;

class B;

class A {
public:
    A(int __val): val(__val) {}
    A(const B&);  // converts a B to an A
private:
    int val;
};

class B {
public:
    B(double __val): val(__val) {}

    double get_val() const {
        return val;
    }

    operator A() const {
        cout << "calling B::operator A()" << endl;
        return A(val);
    };  // also converts a B to an A

private:
    double val;
};

A::A(const B& b): val(b.get_val()) {
    cout << "calling A::A(const B&)" << endl;
}

A f(const A& x) {
    return x;
}
// --------------------------------------------------------------------


// --------------------------------------------------------------------
// Example for the situation when a class defines multiple conversions
// to (or from) types that are themselves related by conversions.
// --------------------------------------------------------------------

// a class defines constructors from or conversions to more than one arithmetic type

class C {
public:
    // usually a bad idea to have two conversions from arithmetic types

    C(int i): val(i) {}
    C(double i): val(i) {}

    // usually a bad idea to have two conversions to arithmetic types

    operator int() const { return val; }
    operator double() const { return val; }
private:
    long val;
};

void f2(long double x) {}
// ---------------------------------------------------------------------


// ---------------------------------------------------------------------
// Overloaded Functions and Converting Constructors
//
// ambiguity problems can arise when overloaded functions take parameters that
// differ by class types that define the same converting constructors:

class D {
public:
    D(int) {}
};

class E {
public:
    E(int) {}
};

void manip(const D&) {}
void manip(const E&) {}
// ---------------------------------------------------------------------

// ---------------------------------------------------------------------
// Overloaded Functions and User-Defined Conversion

class F {
public:
    F(int) {}
};

class G {
public:
    G(double) {}
};

void manip2(const F&) {}
void manip2(const G&) {}
// ---------------------------------------------------------------------


int main() {
    B b(3.14);

    // Note:
    // Enable `-pedantic` option for g++ to force it to comform to C++ standard
    // specified by any -std option used strictly.
    // If we don't pass this option to g++ compiler, the following code will be 
    // compiled sucessfully without errors.
    
    // error: conversion from ‘B’ to ‘const A’ is ambiguous
    // Because there are two ways to obtain an A from a B:
    //   - use the `A::A(const B&)` constructor that takes a B to convert to an A
    //   - use the `B::operator A()` conversion operator that converts a B to an A
    //
    // A a = f(b);
    
    // to make this call, we have to explicitly call 
    // the conversion operator or the constructor
    A a1 = f(A(b));  // ok: use A's constructor
    A a2 = f(b.operator A());  // ok: use B's conversion operator

    C c(3);
    long lg = 3;
    short sh = 3;

    // error: conversion from ‘C’ to ‘long double’ is ambiguous
    // Because there two ambiguous way to convert to `long double`
    // use `C::operator int()` to convert a `C` to a `int`, then convert to a `long double`
    // or use `C::operator double()` to convert to a `double` then convert to a `long double`
    //
    // f2(c);

    // error: call of overloaded ‘C(long int&)’ is ambiguous
    // 1) long -> int -> C
    // 2) long -> double -> C
    // convertion paths 1) and 2) are indistinguishable
    // 
    // C c2(lg);

    // 1) short -> int -> C
    // 2) short -> double -> C
    // path 1) is better than 2)
    // bcz promoting `short` to `int` is better than converting `short` to `double`
    C c3(sh);  // ok

    // error: call of overloaded ‘manip(int)’ is ambiguous
    //
    // manip(10);
    manip(D(10)); // ok

    // error: call of overloaded ‘manip2(int)’ is ambiguous
    // 1) int -> F
    // and 
    // 2) int -> double -> G
    // are considered euqally
    // 
    // In a call to an overloaded function, the rank of an additional standard
    // conversion (if any) matters only if the viable functions require the 
    // same user-defined conversion. If different user-defined conversions 
    // are needed, then the call is ambiguous.
    // 
    // manip2(10);

    return 0;   
}