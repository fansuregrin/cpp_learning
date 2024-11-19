#include <cstdint>
#include <cstdio>

class B {
public:
    virtual void f() { printf("B::f()\n"); }
    virtual ~B() { printf("B::~B()\n"); }
    int64_t m_b;
};

class C : public B {
public:
    virtual void f() { printf("C::f()\n"); }
    virtual ~C() { printf("C::~C()\n"); }
    int64_t m_c;
};

int main() {
    C c;
    C *pc = &c;
    B *pb = &c;
    pc->f();
    pb->f();
}