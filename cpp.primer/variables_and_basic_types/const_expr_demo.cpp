// topic: `constexpr` and constant expressions

int get_size() {
    return 1;
}

constexpr int get_size2() {
    return 1;
}

constexpr int i = 42;
int j = 3;

int main() {
    // A constant expression is an expression whose value cannot change and that can be
    // evaluated at compile time. A literal is a constant expression. A const object that is
    // initialized from a constant expression is also a constant expression.

    // max_files is a const expression because it is a const `int` initialized from a literal `int`.
    const int max_files = 20;
    const int limit = max_files + 1;  // limit is a constant expression
    // Although staff_size is initialized from a literal, it is not a constant expression
    // because it is a plain `int`, not a `const int`.
    int staff_size = 27; // staff_size is not a constant expression
    // sz is not a constant expression because the value of its initializer is not known until run time
    const int sz = get_size();

    // we can ask the compiler to verify that a variable is a constant expression 
    // by declaring the variable in a constexpr declaration. Variables
    // declared as constexpr are implicitly const and must be initialized by constant expressions.
    constexpr int mf = 20;  // 20 is a constant expression
    constexpr int limit2 = mf + 1;  // `mf + 1` is a constant expression
    // constexpr int sz2 = get_size(); // ok only if `get_size` is a constexpr function
    constexpr int sz2 = get_size2(); //ok! `get_size2` is a constexpr function.

    const int * p = nullptr;  // p is a pointer to a const int
    // We can initialize a constexpr pointer from the nullptr literal 
    // or the literal (i.e., constant expression) 0
    constexpr int * q = nullptr;
    constexpr int * q2 = 0;  // q is a const pointer to int
    // `constexpr` imposes a top-level const on the objects it defines


    // error: ‘& mf’ is not a constant expression
    // why? Variables defined inside a function ordinarily are not stored 
    // at a fixed address. Hence, we cannot use a constexpr pointer to point to such variables.
    // constexpr const int * q3 = &mf;

    // the address of an object defined outside of any function is a constant expression,
    // and so may be used to initialize a constexpr pointer.
    constexpr const int * q3 = &i;  // ok! q3 is a constant pointer to the const int i

    constexpr int * q4 = &j;  // q4 is a constant pointer to the int j
}