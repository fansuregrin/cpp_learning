#include <cstdint>

class A {
public:
    int64_t m_a;
};

class B {
public:
    int64_t m_b;
};

class D: public A, public B {
public:
    int64_t m_d;
};

int main() {
    D d;
    D *pd = &d;
    A *pa = &d;
    B *pb = &d;
}