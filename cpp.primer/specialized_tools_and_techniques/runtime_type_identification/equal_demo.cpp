// using RTTI

#include <typeinfo>
#include <iostream>

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
    Base b1(1), b2(2), b3(2);
    Derived d1(1, 0.1), d2(2, 0.2), d3(2, 0.2);

    std::cout << std::boolalpha 
        << "b1 == b2: " << (b1 == b2) << '\n'
        << "b2 == b3: " << (b2 == b3) << '\n'
        << "b1 == d1: " << (b1 == d1) << '\n'
        << "d2 == d3: " << (d2 == d3) << '\n'
        << std::noboolalpha << std::endl;
}