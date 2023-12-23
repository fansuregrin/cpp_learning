// Specializing Members but Not the Class

#include <iostream>
#include <string>

using namespace std;

template <typename T>
struct Foo {
    Foo(const T &t = T()): mem(t) {}

    void bar() { cout << "Foo<T>::bar" << endl; }

    T mem;
};

template <>  // we're specializing a template
void Foo<int>::bar() {  // we're specializing the Bar member of Foo<int>
    cout << "Foo<int>::bar" << endl;
}

int main() {
    Foo<string> fs;
    fs.bar();

    Foo<int> fi;
    fi.bar();

    return 0;
}