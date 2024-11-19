#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cassert>

#define SPLIT_LINE_BEGIN(title) printf("=========== [%s] ===========\n", title)
#define SPLIT_LINE_END() printf("======================\n\n")

class A {
public:
    void f() { printf("A::f()"); }
    ~A() { printf("A::~A()\n"); }
    void operator delete(void * ptr) {
        printf("A::operator delete(void * ptr)\n");
        free(ptr);
    }
    int32_t m_a;
};

class B {
public:
    virtual void f() { printf("B::f()\n"); }
    virtual ~B() { printf("B::~B()\n"); }
    void operator delete(void * ptr) {
        printf("B::operator delete(void * ptr)\n");
        free(ptr);
    }
    int32_t m_b;
};

class C : public B {
public:
    virtual void f() { printf("C::f()\n"); }
    virtual ~C() { printf("C::~C()\n"); }
    int32_t m_c;
};

class D {
public:
    virtual void g() { printf("D::g()\n"); }
    virtual ~D() { printf("D::~D()\n"); }
    int32_t m_d;
};

class E : public B, public D {
public:
    virtual ~E() { printf("E::~E()\n"); }
    int32_t m_e;
};

class F: public B, public D {
public:
    virtual void f() { printf("F::f()\n"); }
    virtual void g() { printf("F::g()\n"); }
    virtual ~F() { printf("F::~F()\n"); }
    int32_t m_f;
};

int main() {
    A *pa = new A(); // object a

    SPLIT_LINE_BEGIN("memory layout of object a");
    // the memory layout of object a
    // 0  +-----------------+   <--- pa
    //    |       m_a       |
    // 4  +-----------------+
    printf("address of a %p\n", pa);
    printf("address of a::m_a %p\n", &pa->m_a);
    assert((void *)(&pa->m_a) == (void *)(pa));
    SPLIT_LINE_END();
    
    B *pb = new B(); // object b

    SPLIT_LINE_BEGIN("memory layout of object b");
    // the memory layout of object b
    // 0  +-----------------+   <--- pb
    //    |                 |
    // 4  +       vptr      +
    //    |                 |
    // 8  +-----------------+
    //    |       m_b       |
    // 12 +-----------------+
    printf("address of b %p\n", pb);
    printf("address of b::vptr %p\n", pb);
    printf("address of b::m_b %p\n", &pb->m_b);
    assert( (void *)(&pb->m_b) == (void *)((unsigned char *)(pb) + 8) );
    printf("vptr of b %p\n", *(uint64_t *)(pb));
    SPLIT_LINE_END();

    SPLIT_LINE_BEGIN("structure of vtable of class B");
    // structure of vtable of class B
    // +-------------------+
    // | offset to top = 0 |
    // +-------------------+
    // | RTTI information  |
    // +-------------------+   <--- vptr
    // |    entry of f()   |
    // +-------------------+
    // |    entry of ~B()  |
    // +-------------------+
    // |    entry of ~B()  |
    // +-------------------+
    uint64_t * vptr_b = (uint64_t *)*(uint64_t *)pb;
    uint64_t offset_to_top_b = *(vptr_b - 2);
    uint64_t p_rtti_info_b = *(vptr_b - 1);
    uint64_t entry_B_f = *vptr_b;
    uint64_t entry_B_dtor1 = *(vptr_b + 1);  // complete object destructor
    uint64_t entry_B_dtor0 = *(vptr_b + 2);  // deleting destructor
    printf("offset to top of objects of class B %ld\n", offset_to_top_b);
    printf("pointer to RAII information %p\n", p_rtti_info_b);
    printf("entry of B::f() %p\n", entry_B_f);
    printf("entry of B::~B() dtor1 %p\n", entry_B_dtor1);
    printf("entry of B::~B() dtor0 %p\n", entry_B_dtor0);

    reinterpret_cast<void (*)(B *)>(entry_B_f)(pb); // call B::f()
    // reinterpret_cast<void (*)(B *)>(entry_B_dtor_1)(pb); // call B::~B()
    // call B::~B(), then operator delete. same as `delete pb`
    // reinterpret_cast<void (*)(B *)>(entry_B_dtor_2)(pb);
    SPLIT_LINE_END();

    C * pc = new C();  // object c
    
    SPLIT_LINE_BEGIN("memory layout of object c");
    // the memory layout of object c
    // 0  +---------------+   <--- pc
    //    |               |
    // 4  +      vptr     +
    //    |               |
    // 8  +---------------+
    //    |      m_b      |
    // 12 +---------------+
    //    |      m_c      |
    // 16 +---------------+
    printf("address of c %p\n", pc);
    printf("adddress of c::vptr %p\n", pc);
    printf("address of c::m_b %p\n", &pc->m_b);
    assert( (void *)(&pc->m_b) == (void *)((unsigned char *)(pc) + 8) );
    printf("address of c::m_c %p\n", &pc->m_c);
    assert( (void *)(&pc->m_c) == (void *)((unsigned char *)(pc) + 12) );
    printf("vptr of c %p\n", *(uint64_t *)pc);
    SPLIT_LINE_END();

    SPLIT_LINE_BEGIN("structure of vtable of class C");
    // structure of vtable of class C
    // +----------------------+
    // |  offset to top = 0   |
    // +----------------------+
    // |   RTTI information   |
    // +----------------------+   <--- vptr
    // |     entry of f()     |
    // +----------------------+
    // |    entry of ~C()     |
    // +----------------------+
    // |    entry of ~C()     |
    // +----------------------+ 
    uint64_t * vptr_c = (uint64_t *)*(uint64_t *)pc;
    uint64_t offset_to_top_c = *(vptr_c - 2);
    uint64_t p_rtti_info_c = *(vptr_c - 1);
    uint64_t entry_C_f = *vptr_c;
    uint64_t entry_C_dtor1 = *(vptr_c + 1);
    uint64_t entry_C_dtor0 = *(vptr_c + 2);
    printf("offset to top of objects of class C %ld\n", offset_to_top_c);
    printf("pointer to RAII information %p\n", p_rtti_info_c);
    printf("entry of C::f() %p\n", entry_C_f);
    printf("entry of C::~C() v1 %p\n", entry_C_dtor1);
    printf("entry of C::~C() v2 %p\n", entry_C_dtor0);

    ((void (*)(C *))entry_C_f)(pc);  // call C::f()
    // ((void (*)(C *))entry_C_dtor_1)(pc);  // call C::~C(), the B::~B()
    SPLIT_LINE_END();

    D * pd = new D();  // object d
    SPLIT_LINE_BEGIN("memory layout of object d");
    // the memory layout of object d
    // 0  +---------------+   <--- pd
    //    |               |
    // 4  +      vptr     +
    //    |               |
    // 8  +---------------+
    //    |      m_d      |
    // 12 +---------------+
    printf("address of d %p\n", pd);
    printf("address of d::vptr %p\n", pd);
    printf("address of d::m_d %p\n", &pd->m_d);
    printf("vptr of d %p\n", *(uint64_t *)pd);
    SPLIT_LINE_END();

    SPLIT_LINE_BEGIN("structure of vtable of class D");
    // structure of vtable of class D
    // +----------------------+
    // |    offset to top     |
    // +----------------------+
    // |   RTTI information   |
    // +----------------------+   <--- vptr
    // |     entry of g()     |
    // +----------------------+
    // |    entry of ~D()     |
    // +----------------------+
    // |    entry of ~D()     |
    // +----------------------+ 
    uint64_t * vptr_d = (uint64_t *)*(uint64_t *)pd;
    uint64_t entry_D_g = *vptr_d;
    printf("address of D::g() %p\n", entry_D_g);
    // 验证是否是 D::g()
    ((void (*)(D *))entry_D_g)(pd); // call D::g()
    SPLIT_LINE_END();

    E *pe = new E();  // object e

    SPLIT_LINE_BEGIN("memory layout of object e");
    // memory layout of object e
    // 0  +-------------------+   <--- pe
    //    |                   |
    // 4  +      vptr1        +
    //    |                   |
    // 8  +-------------------+
    //    |       m_b         |
    // 12 +-------------------+
    //    |                   |
    // 16 +-------------------+
    //    |                   |
    // 20 +      vptr2        +
    //    |                   |
    // 24 +-------------------+
    //    |       m_d         |
    // 28 +-------------------+
    //    |       m_e         |
    // 32 +-------------------+
    printf("address of object e %p\n", pe);
    printf("address of e::vptr1 %p\n", pe);
    printf("address of e::m_b %p\n", &pe->m_b);
    printf("address of e::vptr2 %p\n", (uint64_t *)pe + 2);
    printf("address of e::m_d %p\n", &pe->m_d);
    printf("address of e::m_e %p\n", &pe->m_e);
    printf("vptr1 of e %p\n", *(uint64_t *)pe);
    printf("vptr2 of e %p\n", *((uint64_t *)pe + 2));
    SPLIT_LINE_END();

    SPLIT_LINE_BEGIN("structure of vtable of class E");
    // structure of vtable of class E
    // +-----------------------+ 
    // |  offset to top = 0    |
    // +-----------------------+
    // |    RTTI information   |
    // +-----------------------+   <--- vptr1
    // |   entry of B::f()     |
    // +-----------------------+
    // |   entry of E::~E()    |
    // +-----------------------+
    // |   entry of E::~E()    |
    // +-----------------------+
    // |  offset to top = -16  |
    // +-----------------------+
    // |    RTTI information   |
    // +-----------------------+   <--- vptr2
    // |   entry of D::g()     |
    // +-------------------------------------+
    // | non-vitural thunk to E::~E() dtor1  |
    // +-------------------------------------+
    // | non-virtual thunk to E::~E() dtor0  |
    // +-------------------------------------+
    uint64_t * vptr_e1 = (uint64_t *)*(uint64_t *)pe;
    uint64_t * vptr_e2 = (uint64_t *)*((uint64_t *)pe + 2);
    uint64_t entry_E_f = *vptr_e1;
    uint64_t entry_E_dtor1 = *(vptr_e1 + 1);
    uint64_t entry_E_dtor0 = *(vptr_e1 + 2);
    uint64_t entry_E_g = *vptr_e2;
    uint64_t entry_E_thunk_dtor1 = *(vptr_e2 + 1);
    uint64_t entry_E_thunk_dtor0 = *(vptr_e2 + 2);

    printf("address of E::f() %p\n", entry_E_f);
    ((void (*)(E *))entry_E_f)(pe);
    // E 继承自 B 但没有覆盖 B 的 f()，因此 E 的 f() 就是 B 的 f()
    assert(entry_E_f == entry_B_f);
    
    printf("address of E::g() %p\n", entry_E_g);
    ((void (*)(E *))entry_E_g)(pe);
    // E 继承自 D 但没有覆盖 D 的 g()，因此 E 的 g() 就是 D 的 g()
    assert(entry_E_g == entry_D_g);

    printf("address of E::~E() dtor1 %p\n", entry_E_dtor1);
    printf("address of E::~E() dtor0 %p\n", entry_E_dtor0);
    printf("address of E::~E() thunk dtor1 %p\n", entry_E_thunk_dtor1);
    printf("address of E::~E() thunk dtor0 %p\n", entry_E_thunk_dtor0);

    SPLIT_LINE_END();

    F * pf = new F();
    SPLIT_LINE_BEGIN("structure of vtable of class F");
    // structure of vtable of class E
    // +-----------------------+ 
    // |  offset to top = 0    |
    // +-----------------------+
    // |    RTTI information   |
    // +-----------------------+   <--- vptr1
    // |   entry of F::f()     |
    // +-----------------------+
    // |   entry of F::~F()    |
    // +-----------------------+
    // |   entry of F::~F()    |
    // +-----------------------+   
    // |   entry of F::g()     |
    // +-----------------------+
    // |  offset to top = -16  |
    // +-----------------------+
    // |    RTTI information   |
    // +--------------------------------------+   <--- vptr2
    // |  non-virtual thunk to F::g()         |
    // +--------------------------------------+
    // |  non-virutal thunk to F::~F() dtor1  |
    // +--------------------------------------+
    // |  non-virtual thunk to F::~F() dtor0  |
    // +--------------------------------------+
    uint64_t * vptr_f1 = (uint64_t *)*(uint64_t *)pf;
    uint64_t * vptr_f2 = (uint64_t *)*((uint64_t *)pf + 2);
    uint64_t entry_F_f = *vptr_f1;
    uint64_t entry_F_g = *vptr_f2;
    printf("address of F::f() %p\n", entry_F_f);
    ((void (*)(E *))entry_F_f)(pe);
    // E 继承自 B 且覆盖 B 的 f()，因此 E 的 f() 不是 B 的 f()
    assert(entry_F_f != entry_B_f);
    printf("address of F::g() %p\n", entry_F_g);
    // E 继承自 D 且覆盖 D 的 g()，因此 E 的 g() 不是 D 的 g()
    assert(entry_F_g != entry_D_g);
    ((void (*)(E *))entry_F_g)(pe);
    SPLIT_LINE_END();

    delete pa; // call A::~A(), then A::operator delete
    delete pb; // call B::~B(), then B::operator delete
    delete pc; // call C::~C(), then C::operator delete, then B::~B(), then B::operator delete
    delete pe;
    delete pf;
}

// References:
// - https://www.cnblogs.com/malecrab/p/5573368.html
// - https://itanium-cxx-abi.github.io/cxx-abi/abi.html#vtable
// - https://ww2.ii.uj.edu.pl/%7Ekapela/pn/cpp_vtable.html#virtual
// - https://blog.csdn.net/Howl_1/article/details/122917471