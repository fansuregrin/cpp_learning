#include <iostream>
#include <string>
#include <iomanip>

constexpr int MSG_LEN = 25;

template <typename T>
void f(T &x, const std::string &msg) {
    std::cout << std::setw(MSG_LEN) << std::left << msg << " lvalue" << std::endl;
}

template <typename T>
void f(T &&x, const std::string &msg) {
    std::cout << std::setw(MSG_LEN) << std::left << msg << " rvalue" << std::endl;
}

struct A {
    int mv;  // member variable
    void mf() {} // non-static member function
    static void smf() {} // static member function
    enum Color { RED, GREEN, BLUE };  // member enumerator

    void g() { f(this, "this"); }
};

enum Day {
    SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY
};

int main() {
    //===========
    // prvalue
    //===========
    // 1) literal (except for string literal)
    f(42, "42");         // integer literal
    f(3.14, "3.14");     // float-point literal
    f('a', "a");         // character literal
    f(true, "true");     // boolean literal
    f(nullptr, "nullptr"); // the pointer literal

    // 2) built-in post-increment and post-decrement
    int a = 10;
    f(a++, "a++");
    f(a--, "a--");

    // 3) a function call or an overloaded operator expression,
    //    whose return type is non-reference
    std::string s1 = "hello", s2 = " world";
    std::string::iterator it = s1.begin();
    f(s1 + s2, "s1 + s2");
    f(s1.substr(2), "s1.substr()");
    f(it++, "it++");

    // 4) built-in arithmetic expressions
    int b = 20;
    f(a + b, "a + b");
    f(a - b, "a - b");
    f(a % b, "a % b");
    f(a * b, "a * b");
    f(a / b, "a / b");
    f(a & b, "a & b");
    f(a | b, "a | b");
    f(a ^ b, "a ^ b");
    f(~a, "~a");

    // 5) built-in logical expressions
    int b1 = true, b2 = false;
    f(!b1, "!b1");
    f(b1 && b2, "b1 && b2");
    f(b1 || b2, "b1 || b2");
    f(!b1 && (b > 0 || b2), "!b1 && (b > 0 || b2)");

    // 6) built-in comparison expressions
    f(a < b, "a < b");
    f(a >= b, "a >= b");
    f(a == b, "a == b");
    f(a != b, "a != b");

    // 7) built-in address-of expression
    int arr[5] = {1, 2, 3, 4, 5};
    f(&a, "&a");
    f(&arr[2], "&arr[2]");

    // 8) a.m, the member of object,
    //    where the member is a member enumerator or a non-static member function
    A obj;
    f(obj.mv, "obj.mv");
    f(obj.RED, "obj.RED");
    // cannot use non-static member function directly for initializing function arguments!
    // f(obj.mf, "obj.mf"); 

    // The expressions a.mf and p->mf, where mf is a non-static member function,
    // and the expressions a.*pmf and p->*pmf, where pmf is a pointer to member function,
    // are classified as prvalue expressions, but they cannot be used to initialize references,
    // as function arguments, or for any purpose at all,
    // except as the left-hand argument of the function call operator.

    f(obj.smf, "obj.smf"); // lvalue!!!

    // 9) p->m, the built-in member of pointer expression,
    //    where m is a member enumerator or a non-static member function
    A *p = &obj;
    f(p->mv, "p->mv");
    f(p->GREEN, "p->GREEN");
    // f(p->mf, "p->mf");
    f(p->smf, "p->smf");

    // 10) a.*mp, the pointer to member of object expression,
    //     where mp is a pointer to member function
    auto pmf = &A::mf;
    auto pmv = &A::mv;
    // a pointer to a bound function may only be used to call the function
    // f(obj.*pmf, "obj.*pmf");
    f(obj.*pmv, "obj.*pmv");

    // 11) p->*mp, the built-in pointer to member of pointer expression,
    //     where mp is a pointer to member function
    // f(p->*pmf, "p->*pmf");
    f(p->*pmv, "p->*pmv");

    // 12) `a,b`, the built-in comma expression, where b is an prvalue
    f((a, 42), "a, 42");

    // 13) the ternary conditional expression for certain b and c
    f(true ? a : 42, "true ? a : 42");
    f(true ? a+b : a-b, "true ? a+a : a-b");

    // 14) a cast expression to non-reference type
    f(static_cast<double>(a), "static_cast<double>(a)");
    f((double)b, "(double)b");

    // 15) the this pointer
    obj.g();

    // 16) an enumerator
    Day today = Day::FRIDAY;
    f(Day::SATURDAY, "Day::SATURDAY");
    f(today, "today");
}