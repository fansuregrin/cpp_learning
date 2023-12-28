// Specializing Members but Not the Class

#include <iostream>
#include <string>


template <typename T>
struct Foo {
    Foo(const T &t = T()): mem(t) {}

    void bar() { std::cout << "Foo<T>::bar" << std::endl; }

    T mem;
};

template <>  // we're specializing a template
void Foo<int>::bar() {  // we're specializing the Bar member of Foo<int>
    std::cout << "Foo<int>::bar" << std::endl;
}

int main() {
    Foo<std::string> fs;
    fs.bar();

    Foo<int> fi;
    fi.bar();

    return 0;
}