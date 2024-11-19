#include <cstdint>

class A {
public:
    int64_t m_a;
};

class C: public A {
public:
    int64_t m_c;
};

int main() {
    C c;
    C *pc = &c;
    A *pa = &c;
}