// Explore inheritance (w/o polymorphism)
#include <cstdint>
#include <cstdio>
#include <cassert>

#define SHOW_SIZE(e) printf("size of class %s %ld\n", #e, sizeof(e))

class A {
public:
    int64_t m_a;
};

class B {
public:
    int64_t m_b;
};

class C: public A {
public:
    int64_t m_c;
};

class D: public A, public B {
public:
    int64_t m_d;
};

class E : public C {
public:
    int64_t m_e;
};

class F : public C, public D {
public:
    int64_t m_f;
};

int main() {
    // 单继承 (Single inheritance)
    C c;
    C *pc = &c;
    A *pa = &c;
    
    SHOW_SIZE(A);
    SHOW_SIZE(B);
    SHOW_SIZE(C);
    SHOW_SIZE(D);
    SHOW_SIZE(E);
    SHOW_SIZE(F);

    // memory layout of c
    // 0  +-------------------+  <--- pc/pa
    //    |       m_a         |
    // 8  +-------------------+
    //    |       m_c         |
    // 16 +-------------------+
    //
    // C 继承自 A，所以对象 c 中先存放 A 定义的成员变量，再存在 C 定义的成员变量。
    SHOW_SIZE(c);
    printf("address of c %p\n", &c);
    // c 的起始地址就是 c::m_a 的起始地址
    assert((void *)&c == (void *)&c.m_a);
    printf("address of c::m_a %p\n", &c.m_a);
    printf("address of c::m_c %p\n", &c.m_c);
    assert((void *)&c == (void *)pc);
    assert((void *)&c == (void *)pa);
    printf("pc = %p\n", pc);
    printf("pa = %p\n", pa);
    
    // 多继承 (Multiple inheritance)
    D d;
    D *pd = &d;
    pa = &d;
    B *pb = &d;

    // memory layout of d
    // 0  +-------------------+  <--- pd/pa
    //    |        m_a        |
    // 8  +-------------------+  <--- pb
    //    |        m_b        |
    // 16 +-------------------+
    //    |        m_c        |
    // 24 +-------------------+
    //
    // D 继承自 A 和 B，在类派生列表中基类出现的顺序是先 A 后 B
    // 所以对象 d 中先存放 A 中定义的成员变量，再存放 B 中定义的成员变量，
    // 最后存放 D 中定义的成员变量。
    SHOW_SIZE(d);
    printf("address of d %p\n", &d);
    assert((void *)&d == (void *)&d.m_a);
    printf("address of d::m_a %p\n", &d.m_a);
    printf("address of d::m_b %p\n", &d.m_b);
    printf("address of d::m_c %p\n", &d.m_d);
    assert((void *)&d == (void *)pa);
    // pb 会偏移，不指向 d 的起始位置，而指向 d 中 B 的起始位置
    assert((void *)&d != (void *)pb);
    assert((void *)((unsigned char *)&d + sizeof(A)) == (void *)pb);
    printf("pd = %p\n", pd);
    printf("pa = %p\n", pa);
    printf("pb = %p\n", pb);

    E e;
    E *pe = &e;
    pc = &e;
    pa = &e;

    // memory layout of e
    // 0  +-------------------+  <--- pe/pa/pc
    //    |        m_a        |
    // 8  +-------------------+
    //    |        m_c        |
    // 16 +-------------------+
    //    |        m_e        |
    // 24 +-------------------+
    SHOW_SIZE(e);
    printf("address of e %p\n", &e);
    printf("address of e::m_a %p\n", &e.m_a);
    printf("address of e::m_c %p\n", &e.m_c);
    printf("address of e::m_e %p\n", &e.m_e);
    assert((void *)pe == (void *)&e);
    assert((void *)pa == (void *)&e);
    assert((void *)pc == (void *)&e);

    F f;
    F *pf = &f;
    // 出现二义性
    // pa = &f;  // error: ‘A’ is an ambiguous base of ‘F’
    pb = &f;
    pc = &f;
    pd = &f;

    // memory layout of f
    // 0  +-------------------+  <--- pf/pc
    //    |        m_a        |
    // 8  +-------------------+
    //    |        m_c        |
    // 16 +-------------------+  <--- pd
    //    |        m_a        |
    // 24 +-------------------+  <--- pb
    //    |        m_b        |
    // 32 +-------------------+
    //    |        m_d        |
    // 40 +-------------------+
    //    |        m_f        |
    // 48 +-------------------+
    SHOW_SIZE(f);
    printf("address of f %p\n", &f);
    // error: request for member ‘m_a’ is ambiguous
    // printf("address of f::m_a %p\n", &f.m_a);
    printf("address of f::m_c %p\n", &f.m_c);
    printf("address of f::m_b %p\n", &f.m_b);
    printf("address of f::m_d %p\n", &f.m_d);
    printf("address of f::m_f %p\n", &f.m_f);
    assert((void *)pf == (void *)&f);
    assert((void *)pc == (void *)&f);
    assert((void *)pd != (void *)&f);
    assert( (void *)pd == (void *)((unsigned char *)&f + sizeof(C)) );
    assert((void *)pb != (void *)&f);
    assert( (void *)pb == (void *)((unsigned char *)pd + sizeof(A)) );
    printf("pf = %p\n", pf);
    printf("pc = %p\n", pc);
    printf("pd = %p\n", pd);
    printf("pb = %p\n", pb);
}