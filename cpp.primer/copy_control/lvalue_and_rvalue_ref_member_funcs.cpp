// topic: Rvalue and Lvalue Reference Member Functions

class Foo {
public:
    Foo(): val(0) {}
    Foo(int _val): val(_val) {}

    
    // Placing a **reference qualifier** after the parameter list to
    // indicate the lvalue/rvalue property of `this`.
    // A reference qualifier may appear only on a (nonstatic) member function and
    // must appear in both the declaration and definition of the function.
    // The reference qualifier can be either & or &&, indicating that this may point to an
    // rvalue or lvalue, respectively.

    // This may assign only to modifiable lvalues.
    Foo& operator=(const Foo &) &;

    // A function can be both const and reference qualified. In such cases, the reference
    // qualifier must follow the const qualifier

    // void someMem() & const;  // error: const qualifier must come first
    void anotherMem() const &;  // ok: const qualifier comes first

private:
    int val;
};

Foo& Foo::operator=(const Foo & rhs) & {
    val = rhs.val;
    return *this;
}

Foo retVal() {
    return Foo();
}

int main() {
    Foo a(2), b;
    
    b = a;  // ok! `b` is a lvalue.
    b = retVal();  // ok: we can pass an rvalue as the right-hand operand to assignment

    // Foo(3) = a; // error! `Foo(3)` is a rvalue.
    // retVal() = a;  // error! `retVal()` returns a rvalue.

    return 0;
}