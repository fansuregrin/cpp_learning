// topic: Overloading and Reference Functions

#include <vector>
#include <algorithm>

using namespace std;

class Foo {
public:
    Foo(vector<int> _data): data(_data) {}

    Foo sorted() &&;  // may run on modifiable rvalues

    Foo sorted() const &;  // may run on any kind of `Foo`

    // Note:
    // If a member function has a reference qualifier, all the versions of that
    // member with the same parameter list must have reference qualifiers.
    //
    // Foo sorted();  // error!
private:
    vector<int> data;
};

// this object is an rvalue, so we can sort in place
Foo Foo::sorted() && {
    sort(data.begin(), data.end());
    return *this;
}

Foo Foo::sorted() const & {
    Foo ret(*this);  // make a copy
    sort(ret.data.begin(), ret.data.end());  // sort the copy
    return ret;  // return the copy
}

int main() {
    Foo a({1, 4, 3, 5});

    // `a` is a lvalue, calls `Foo::sorted() const &`.
    Foo b = a.sorted();
    // `Foo({3,2.1})` is a rvalue, calls `Foo::sorted() &&`.
    Foo c = Foo({3,2,1}).sorted();

    return 0;
}