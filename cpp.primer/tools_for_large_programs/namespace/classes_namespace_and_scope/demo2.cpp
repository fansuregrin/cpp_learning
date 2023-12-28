// topic: namespace and class

// When a class is wrapped in a namespace, the normal lookup still happens: When a
// name is used by a member function, look for that name in the member first, then
// within the class (including base classes), then look in the enclosing scopes, one or
// more of which might be a namespace.

namespace A {
    int i;
    int k;

    class C1 {
    public:
        C1(): i(0), j(0) {}  // ok: initializes C1::i and C1::j
        int f1() { return k; }  // return A::k
        // int f2() { return h; }  // error: ‘h’ was not declared in this scope
        int f3();
    private:
        int i;  // hides A::i within C1
        int j;
    };

    int h = i;  // initialzed from A::i
}

// The order in which scopes are examined to find a name can be inferred from
// the qualified name of a function. The qualified name indicates, in reverse
// order, the scopes that are searched.

// member f3 is defined outside class C1 and outside namespace A
int A::C1::f3() { return h; }  // ok: returns A::h
// scopes that are to be searched: f3 -> C1 -> A