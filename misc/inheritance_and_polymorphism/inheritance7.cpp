#include <cstdint>
#include <cstdio>

class A {
public:
    virtual void f() { printf("A::f()\n"); }
    ~A() { printf("A::~A()\n"); }
    int64_t m_a;
};

class B : virtual public A {
public:
    virtual void g() { printf("B::g()\n"); }
    virtual ~B() { printf("B::~B()\n"); }
    int64_t m_b;
};

class C : virtual public A{
public:
    virtual void h() { printf("C::h()\n"); }
    virtual ~C() { printf("C::~C()\n"); }
    int64_t m_c;
};

class D : public B, public C {
public:
    virtual ~D() { printf("D::~D()\n"); }
    int64_t m_d;
};

int main() {
    D d;
    D *pd = &d;
    B *pb = &d;
    C *pc = &d;
    A *pa = &d;
    pd->f();
}