// topic: Friend Declarations and Argument-Dependent Lookup

// Recall that when a class declares a friend, the friend declaration does not make the
// friend visible. However, an otherwise undeclared class or function
// that is first named in a friend declaration is assumed to be a member of the closest
// enclosing namespace. The combination of this rule and argument-dependent lookup
// can lead to surprises.

namespace A {
    class C {
        // two friends; neither is declared apart from a friend declaration
        // these functions implicitly are members of namespace A
        friend void f1(const C&);
        friend void f2();
    };
}

int main() {
    A::C cobj;
    f1(cobj);  // ok: finds A::f1 through the friend declaration in A::C
    // f2();  // error: A::f2 not declared
}