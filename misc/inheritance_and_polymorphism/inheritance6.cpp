#include <cstdint>
#include <cstdio>

class A {
public:
    int64_t m_a1;
    int64_t m_a2;
};

class B : virtual public A {
public:
    int64_t m_b1;
    int64_t m_b2;
};

class C : virtual public A{
public:
    int64_t m_c1;
    int64_t m_c2;
};

class D : public B, public C {
public:
    int64_t m_d1;
    int64_t m_d2;
};

int main() {
    D d;
}