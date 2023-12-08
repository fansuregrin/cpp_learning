// topic: static member of class template

#include <cstddef>
#include <iostream>

using namespace std;

template <typename T>
class Foo {
public:
    static std::size_t count() { return ctr; }
    static void increase_cnt() { ++ctr; }
private:
    static std::size_t ctr;
};

template <typename T> std::size_t Foo<T>::ctr = 0;

int main() {
    Foo<double> fd; // instantiates Foo<double> class and the static data member ctr
    Foo<int> fi;  // instantiates Foo<int> class and the static data member ctr
    auto ct = Foo<int>::count();  // instantiates Foo<int>::count

    fi.increase_cnt();  // instantiates Foo<int>::increase_cnt
    ct = fi.count();  // uses Foo<int>::count

    cout << "Foo<double>::ctr = " << fi.count() << endl;
    cout << "Foo<int>::ctr = " << fd.count() << endl;

    Foo<int> fi2, fi3;

    // fi, fi2 and fi3 share the same Foo<int>::ctr, Foo<int>::increase_cnt()
    // and Foo<int>::count members

    fi3.increase_cnt();
    cout << "Foo<int>::ctr = " << fi.count() << endl;
    cout << "Foo<int>::ctr = " << fi2.count() << endl;
    cout << "Foo<int>::ctr = " << fi3.count() << endl;

    return 0;
}