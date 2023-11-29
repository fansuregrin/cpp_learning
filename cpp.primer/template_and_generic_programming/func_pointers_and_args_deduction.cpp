// topic: function pointers and arguments deduction

// When we initialize or assign a function pointer from a function template,
// the compiler uses the type of the pointer to deduce the template argument(s).


template<typename T>
int compare(const T& a, const T& b) {
    if (a < b) return -1;
    if (b < a) return 1;
    return 0;
}

// overloaded versions of func; each takes a different function pointer type

void func(int (*pf)(const double &, const double &)) {}
void func(int (*pf)(const int &, const int &)) {}

int main() {
    // `pf1` points to the instantiation `int compare(const int&, const int&)`
    int (*pf1) (const int&, const int&) = compare;

    // func(compare);  // error: which instantiation of compare?

    // ok: explicitly specify which version of compare to instantiate
    func(compare<int>);  // passing compare(const int&, const int&)

    return 0;
}