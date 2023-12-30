// topic: typeinfo

#include <typeinfo>
#include <iostream>
#include <string>

class Base {
    friend bool operator==(const Base&, const Base&);
public:
    // interface members for Base
    Base(): val(0) {}
    Base(int __val): val(__val) {}
protected:
    virtual bool equal(const Base&) const;
    // data and other implementation members of Base
    int val;
};


class Derived: public Base {
public:
    // other interface members for Derived
    Derived(): rate(0.0) {}
    Derived(int __val, double __rate): Base(__val), rate(__rate) {}
protected:
    bool equal(const Base&) const;
    // data and other implementation members of Derived
    double rate;
};

bool Base::equal(const Base &rhs) const {
    return val == rhs.val;
}

bool Derived::equal(const Base &rhs) const {
    auto r = dynamic_cast<const Derived&>(rhs);
    return val == r.val && rate == r.rate;
}

bool operator==(const Base &lhs, const Base &rhs) {
    return typeid(lhs) == typeid(rhs) && lhs.equal(rhs);
}

int main() {
    int arr[10];
    Derived d;
    Base *p = &d;

    // The type_info class varies by compiler. Some compilers provide additional
    // member functions that provide additional information about types used in a
    // program. You should consult the reference manual for your compiler to
    // understand the exact type_info support provided.

    std::cout 
        << "42: " << typeid(42).name() << '\n'
        << "arr[10]: " << typeid(arr).name() << '\n'
        << "string: " << typeid(std::string).name() << '\n'
        << "p: " << typeid(p).name() << '\n'
        << "*p: " << typeid(*p).name()
        << std::endl;

    // on my machine: gcc version 9.4.0 (Ubuntu 9.4.0-1ubuntu1~20.04.2)
    // 42: i
    // arr[10]: A10_i
    // string: NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
    // p: P4Base
    // *p: 7Derived
}