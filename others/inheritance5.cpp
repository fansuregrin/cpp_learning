#include <cstdint>
#include <cstdio>

class B {
public:
    virtual void f() { printf("B::f()\n"); }
    virtual ~B() { printf("B::~B()\n"); }
    int64_t m_b;
};

class D {
public:
    virtual void g() { printf("D::g()\n"); }
    virtual ~D() { printf("D::~D()\n"); }
    int64_t m_d;
};

class C : public B {
public:
    virtual void f() { printf("C::f()\n"); }
    virtual ~C() { printf("C::~C()\n"); }
    int64_t m_c;
};

class E : public B, public D {
public:
    virtual void g() { printf("E::g()\n"); }
    virtual ~E() { printf("E::~E()\n"); }
    int64_t m_e;
};

int main() {
    E e;
    E *pe = &e;
    B *pb = &e;
    D *pd = &e;
    pe->f();
    pe->g();
    pb->f();
    pd->g();
}