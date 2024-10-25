# C++继承和多态的实现原理

## 无多态继承
### 单继承
```cpp
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
```

对象 c 的内存布局如下所示：
```
0  +-------------------+  <--- pc/pa
   |       m_a         |
8  +-------------------+
   |       m_c         |
16 +-------------------+

C 继承自 A，所以对象 c 中先存放 A 定义的成员变量，再存在 C 定义的成员变量。
```

在 x86-64 平台上使用 gcc-14.2 翻译成汇编：
```assembly
main:
    pushq   %rbp               # 保存栈帧的基地址，用于函数返回时恢复之前的栈帧
    movq    %rsp, %rbp         # 将栈顶地址作为当前栈帧的基地址
    leaq    -32(%rbp), %rax    # 加载 c 的起始地址到寄存器 rax
    movq    %rax, -8(%rbp)     # 将 c 的起始地址保存到局部变量 pc 中 
    leaq    -32(%rbp), %rax    # 加载 c 的起始地址到寄存器 rax
    movq    %rax, -16(%rbp)    # 将 c 的起始地址保存到局部变量 pa 中
    movl    $0, %eax           # 将寄存器 rax 置为 0，作为 main 函数的返回值
    popq    %rbp               # 恢复之前栈帧的基地址
    ret                        # 返回调用 main 函数的下一条指令处
```

从汇编代码可以看出上述 main 函数运行过程中，栈上的内存分配情况如下：
```
8   +----------------+
    |    old %rbp    |
0   +----------------+  <--- %rsp/%rbp
    |       pc       |-------+
-8  +----------------+       |
    |       pa       |-------|
-16 +----------------+       |
    |       m_c      |       | 
-24 +----------------+       |
    |       m_a      |       |
-32 +----------------+  <----+
```

### 多继承
```cpp
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
```

对象 d 的内存布局如下所示：
```
0  +-------------------+  <--- pd/pa
   |        m_a        |
8  +-------------------+  <--- pb
   |        m_b        |
16 +-------------------+
   |        m_c        |
24 +-------------------+
```

在 x86-64 平台上使用 gcc-14.2 翻译成汇编：
```assembly
main:
    pushq   %rbp
    movq    %rsp, %rbp
    leaq    -48(%rbp), %rax
    movq    %rax, -8(%rbp)
    leaq    -48(%rbp), %rax
    movq    %rax, -16(%rbp)
    leaq    -48(%rbp), %rax
    addq    $8, %rax
    movq    %rax, -24(%rbp)
    movl    $0, %eax
    popq    %rbp
    ret
```

从汇编代码可以看出上述 main 函数运行过程中，栈上的内存分配情况如下：
```
8   +----------------+
    |    old %rbp    |
0   +----------------+  <--- %rsp/%rbp
    |       pd       |---------+
-8  +----------------+         |
    |       pa       |---------|
-16 +----------------+         |
    |       pb       |------+  |
-24 +----------------+      |  |
    |       m_d      |      |  |
-32 +----------------+      |  |
    |       m_b      |      |  | 
-40 +----------------+  <---+  |
    |       m_a      |         |
-48 +----------------+  <------+
```

## 多态继承
### 单继承
```cpp
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
```

B 的对象的内存布局如下：
```
0  +-----------------+
   |       vptr      |
8  +-----------------+
   |       m_b       |
16 +-----------------+
```
由于 B 定义了虚函数，B 的对象中不仅包含其成员变量，还包含一个虚函数表指针 `vptr`，并且位于对象的起始位置。

B 的虚函数表如下：
```
+--------------------------+
|    offset to top = 0     |
+--------------------------+
|    RTTI information      |
+--------------------------+   <--- vptr
|     entry of B::f()      |
+--------------------------+
|  entry of B::~B() dtor1  |
+--------------------------+
|  entry of B::~B() dtor0  |
+--------------------------+
```
- offset to top：表示在对象的内存布局中，vptr 离对象起始位置的偏移量。
- RTTI information：是一个指向 typeinfo 结构的指针，用于运行时识别对象的类型。
- entry of `B::f()`：一个指针，指向函数 `B::f()`。
- entry of `B::~B()` dtor1：一个指针，指向 B 的 complete object destructor (dtor1)。
- entry of `B::~B()` dtor0：一个指针，指向 B 的 deleting destructor (dtor0)。

C 的对象的内存布局如下：
```
0  +-----------------+
   |       vptr      |
8  +-----------------+
   |       m_b       |
16 +-----------------+
   |       m_c       |
24 +-----------------+
```

C 的虚函数表如下：
```
+--------------------------+
|    offset to top = 0     |
+--------------------------+
|    RTTI information      |
+--------------------------+   <--- vptr
|     entry of C::f()      |
+--------------------------+
|  entry of C::~C() dtor1  |
+--------------------------+
|  entry of C::~C() dtor0  |
+--------------------------+
```

上面的代码在 x86-64 平台用 gcc-14.2 翻译成汇编:
```assembly
.LC0:
        .string "B::f()"
B::f():
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movq    %rdi, -8(%rbp)
        movl    $.LC0, %edi
        call    puts
        nop
        leave
        ret
.LC1:
        .string "B::~B()"
B::~B() [base object destructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movq    %rdi, -8(%rbp)
        movl    $vtable for B+16, %edx
        movq    -8(%rbp), %rax
        movq    %rdx, (%rax)
        movl    $.LC1, %edi
        call    puts
        nop
        leave
        ret
B::~B() [deleting destructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movq    %rdi, -8(%rbp)
        movq    -8(%rbp), %rax
        movq    %rax, %rdi
        call    B::~B() [complete object destructor]
        movq    -8(%rbp), %rax
        movl    $16, %esi
        movq    %rax, %rdi
        call    operator delete(void*, unsigned long)
        leave
        ret
.LC2:
        .string "C::f()"
C::f():
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movq    %rdi, -8(%rbp)
        movl    $.LC2, %edi
        call    puts
        nop
        leave
        ret
.LC3:
        .string "C::~C()"
C::~C() [base object destructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movq    %rdi, -8(%rbp)
        movl    $vtable for C+16, %edx
        movq    -8(%rbp), %rax
        movq    %rdx, (%rax)
        movl    $.LC3, %edi
        call    puts
        movq    -8(%rbp), %rax
        movq    %rax, %rdi
        call    B::~B() [base object destructor]
        nop
        leave
        ret
C::~C() [deleting destructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movq    %rdi, -8(%rbp)
        movq    -8(%rbp), %rax
        movq    %rax, %rdi
        call    C::~C() [complete object destructor]
        movq    -8(%rbp), %rax
        movl    $24, %esi
        movq    %rax, %rdi
        call    operator delete(void*, unsigned long)
        leave
        ret
B::B() [base object constructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        movq    %rdi, -8(%rbp)
        movl    $vtable for B+16, %edx
        movq    -8(%rbp), %rax
        movq    %rdx, (%rax)
        nop
        popq    %rbp
        ret
C::C() [base object constructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movq    %rdi, -8(%rbp)
        movq    -8(%rbp), %rax
        movq    %rax, %rdi
        call    B::B() [base object constructor]  # 调用 B 的构造函数
        movl    $vtable for C+16, %edx
        movq    -8(%rbp), %rax
        movq    %rdx, (%rax)
        nop
        leave
        ret
main:
        pushq   %rbp
        movq    %rsp, %rbp
        pushq   %rbx
        subq    $56, %rsp
        leaq    -64(%rbp), %rax  # 将 c 的起始地址加载到寄存器 rax 中
        movq    %rax, %rdi       # 将 rax 的内容移动到参数寄存器 rdi 中
        call    C::C() [complete object constructor] # 调用 C 的构造函数
        leaq    -64(%rbp), %rax  # 将 c 的起始地址加载到寄存器 rax 中（此时对象c已经构造完成）
        movq    %rax, -24(%rbp)  # 将 c 的起始地址保存到局部变量 pc 中
        leaq    -64(%rbp), %rax  # 将 c 的起始地址加载到寄存器 rax 中
        movq    %rax, -32(%rbp)  # 将 c 的起始地址保存到局部变量 pb 中 
        movq    -24(%rbp), %rax  # 将局部变量 pc（保存的是c的起始地址）加载到寄存器 rax 中
        movq    (%rax), %rax     # 将 c 的前 8 个字节加载到寄存器 rax 中（此时 rax 中存的是虚函数表指针）
        movq    (%rax), %rdx     # 将虚函数表的前 8 个字节加载到寄存器 rax 中（此时 rax 中存的是虚函数表中第一项函数的地址，即 C::f() 的地址）
        movq    -24(%rbp), %rax  # 将 c 的起始地址加载到寄存器 rax 中
        movq    %rax, %rdi       # 将 rax 的内容移动到参数寄存器 rdi 中（即把c的地址作为参数）
        call    *%rdx            # 调用函数 C::f()
        movq    -32(%rbp), %rax  # 将局部变量 pb（保存的是c的起始地址）加载到寄存器 rax 中
        movq    (%rax), %rax     # 将 c 的前 8 个字节加载到寄存器 rax 中（此时 rax 中存的是虚函数表指针）
        movq    (%rax), %rdx     # 将虚函数表的前 8 个字节加载到寄存器 rax 中（此时 rax 中存的是虚函数表中第一项函数的地址，即 C::f() 的地址）
        movq    -32(%rbp), %rax  # 将 c 的起始地址加载到寄存器 rax 中
        movq    %rax, %rdi       # 将 rax 的内容移动到参数寄存器 rdi 中（即把c的地址作为参数） 
        call    *%rdx            # 调用函数 C::f()
        leaq    -64(%rbp), %rax
        movq    %rax, %rdi
        call    C::~C() [complete object destructor]
        movl    $0, %eax
        jmp     .L13
        movq    %rax, %rbx
        leaq    -64(%rbp), %rax
        movq    %rax, %rdi
        call    C::~C() [complete object destructor]
        movq    %rbx, %rax
        movq    %rax, %rdi
        call    _Unwind_Resume
.L13:
        movq    -8(%rbp), %rbx
        leave
        ret
vtable for C:
        .quad   0
        .quad   typeinfo for C
        .quad   C::f()
        .quad   C::~C() [complete object destructor]
        .quad   C::~C() [deleting destructor]
vtable for B:
        .quad   0
        .quad   typeinfo for B
        .quad   B::f()
        .quad   B::~B() [complete object destructor]
        .quad   B::~B() [deleting destructor]
typeinfo for C:
        .quad   vtable for __cxxabiv1::__si_class_type_info+16
        .quad   typeinfo name for C
        .quad   typeinfo for B
typeinfo name for C:
        .string "1C"
typeinfo for B:
        .quad   vtable for __cxxabiv1::__class_type_info+16
        .quad   typeinfo name for B
typeinfo name for B:
        .string "1B"
```

main 运行过程中的内存布局：
```
8   +----------------+
    |    old %rbp    |
0   +----------------+  <--- %rbp
    |    old %rbx    |
-8  +----------------+
    |                |
-16 +----------------+
    |       pc       |-----+
-24 +----------------+     |
    |       pb       |-----+
-32 +----------------+     |
    |                |     |
-40 +----------------+     |
    |      m_c       |     |
-48 +----------------+     |
    |      m_b       |     |
-56 +----------------+     |
    |      vptr      |     |
-64 +----------------+  <--+ %rsp
```

### 多继承
```cpp
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

class E : public B, public D {
public:
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
```

B 的对象的内存布局如下：
```
0  +-----------------+
   |       vptr      |
8  +-----------------+
   |       m_b       |
16 +-----------------+
```

B 的虚函数表如下：
```
+--------------------------+
|    offset to top = 0     |
+--------------------------+
|    RTTI information      |
+--------------------------+   <--- vptr
|     entry of B::f()      |
+--------------------------+
|  entry of B::~B() dtor1  |
+--------------------------+
|  entry of B::~B() dtor0  |
+--------------------------+
```

D 的对象的内存布局如下：
```
0  +-----------------+
   |       vptr      |
8  +-----------------+
   |       m_d       |
16 +-----------------+
```

D 的虚函数表如下：
```
+--------------------------+
|    offset to top = 0     |
+--------------------------+
|    RTTI information      |
+--------------------------+   <--- vptr
|     entry of D::g()      |
+--------------------------+
|  entry of D::~D() dtor1  |
+--------------------------+
|  entry of D::~D() dtor0  |
+--------------------------+
```

E 的对象的内存布局如下：
```
0  +-------------------+  <--- pe/pb
   |      vptr1        |
8  +-------------------+
   |       m_b         |
16 +-------------------+  <--- pd
   |      vptr2        |
24 +-------------------+
   |       m_d         |
32 +-------------------+
   |       m_e         |
40 +-------------------+
```

E 的虚函数表如下：
```
+-------------------------------------+ 
|          offset to top = 0          |
+-------------------------------------+
|          RTTI information           |
+-------------------------------------+   <--- vptr1
|            entry of B::f()          |
+-------------------------------------+
|           entry of E::~E()          |
+-------------------------------------+
|           entry of E::~E()          |
+-------------------------------------+
|         offset to top = -16         |
+-------------------------------------+
|          RTTI information           |
+-------------------------------------+   <--- vptr2
|           entry of D::g()           |
+-------------------------------------+
| non-vitural thunk to E::~E() dtor1  |
+-------------------------------------+
| non-virtual thunk to E::~E() dtor0  |
+-------------------------------------+
```

上面的代码在 x86-64 平台用 gcc-14.2 翻译成汇编:
```assembly
.LC0:
        .string "B::f()"
B::f():
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movq    %rdi, -8(%rbp)
        movl    $.LC0, %edi
        call    puts
        nop
        leave
        ret
.LC1:
        .string "B::~B()"
B::~B() [base object destructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movq    %rdi, -8(%rbp)
        movl    $vtable for B+16, %edx
        movq    -8(%rbp), %rax
        movq    %rdx, (%rax)
        movl    $.LC1, %edi
        call    puts
        nop
        leave
        ret
B::~B() [deleting destructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movq    %rdi, -8(%rbp)
        movq    -8(%rbp), %rax
        movq    %rax, %rdi
        call    B::~B() [complete object destructor]
        movq    -8(%rbp), %rax
        movl    $16, %esi
        movq    %rax, %rdi
        call    operator delete(void*, unsigned long)
        leave
        ret
.LC2:
        .string "D::g()"
D::g():
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movq    %rdi, -8(%rbp)
        movl    $.LC2, %edi
        call    puts
        nop
        leave
        ret
.LC3:
        .string "D::~D()"
D::~D() [base object destructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movq    %rdi, -8(%rbp)
        movl    $vtable for D+16, %edx
        movq    -8(%rbp), %rax
        movq    %rdx, (%rax)
        movl    $.LC3, %edi
        call    puts
        nop
        leave
        ret
D::~D() [deleting destructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movq    %rdi, -8(%rbp)
        movq    -8(%rbp), %rax
        movq    %rax, %rdi
        call    D::~D() [complete object destructor]
        movq    -8(%rbp), %rax
        movl    $16, %esi
        movq    %rax, %rdi
        call    operator delete(void*, unsigned long)
        leave
        ret
.LC4:
        .string "E::~E()"
E::~E() [base object destructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movq    %rdi, -8(%rbp)
        movl    $vtable for E+16, %edx
        movq    -8(%rbp), %rax
        movq    %rdx, (%rax)
        movl    $vtable for E+56, %edx
        movq    -8(%rbp), %rax
        movq    %rdx, 16(%rax)
        movl    $.LC4, %edi
        call    puts
        movq    -8(%rbp), %rax
        addq    $16, %rax
        movq    %rax, %rdi
        call    D::~D() [base object destructor]
        movq    -8(%rbp), %rax
        movq    %rax, %rdi
        call    B::~B() [base object destructor]
        nop
        leave
        ret
non-virtual thunk to E::~E() [complete object destructor]:
        subq    $16, %rdi
        jmp     .LTHUNK0
E::~E() [deleting destructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movq    %rdi, -8(%rbp)
        movq    -8(%rbp), %rax
        movq    %rax, %rdi
        call    E::~E() [complete object destructor]
        movq    -8(%rbp), %rax
        movl    $40, %esi
        movq    %rax, %rdi
        call    operator delete(void*, unsigned long)
        leave
        ret
non-virtual thunk to E::~E() [deleting destructor]:
        subq    $16, %rdi
        jmp     .LTHUNK1
B::B() [base object constructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        movq    %rdi, -8(%rbp)
        movl    $vtable for B+16, %edx
        movq    -8(%rbp), %rax
        movq    %rdx, (%rax)
        nop
        popq    %rbp
        ret
D::D() [base object constructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        movq    %rdi, -8(%rbp)
        movl    $vtable for D+16, %edx
        movq    -8(%rbp), %rax
        movq    %rdx, (%rax)
        nop
        popq    %rbp
        ret
E::E() [base object constructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movq    %rdi, -8(%rbp)
        movq    -8(%rbp), %rax
        movq    %rax, %rdi
        call    B::B() [base object constructor]
        movq    -8(%rbp), %rax
        addq    $16, %rax
        movq    %rax, %rdi
        call    D::D() [base object constructor]
        movl    $vtable for E+16, %edx
        movq    -8(%rbp), %rax
        movq    %rdx, (%rax)
        movl    $vtable for E+56, %edx
        movq    -8(%rbp), %rax
        movq    %rdx, 16(%rax)
        nop
        leave
        ret
main:
        pushq   %rbp
        movq    %rsp, %rbp
        pushq   %rbx
        subq    $72, %rsp
        
        ## E e;
        leaq    -80(%rbp), %rax
        movq    %rax, %rdi
        call    E::E() [complete object constructor]
        
        ## E *pe = &e;
        leaq    -80(%rbp), %rax
        movq    %rax, -24(%rbp)   # E *pe = &e;
        
        ## B *pb = &e;
        leaq    -80(%rbp), %rax
        movq    %rax, -32(%rbp)
        
        ## D *pd = &e;
        leaq    -80(%rbp), %rax
        addq    $16, %rax         # e中先存基类B的数据，再存基类D的数据，B的大小占16字节，所以用基类D的指针指向e，会有偏移。
        movq    %rax, -40(%rbp)
        
        ## pe->f();
        movq    -24(%rbp), %rax   # %rax = pe = &e; 获取 e 的地址
        movq    (%rax), %rax      # %rax = *(uint64_t *)pe; 获取 e 的 vptr1
        movq    (%rax), %rdx      # %rdx = *(uint64_t *)vptr1; 获取 B::f() 的地址
        movq    -24(%rbp), %rax   # %rax = pe = &e;
        movq    %rax, %rdi        # %rdi = pe = &e;
        call    *%rdx             # B::f((B *)&e); (this = (B *)&e)
        
        ## pe->g();
        movq    -24(%rbp), %rax   # %rax = pe = &e;
        movq    16(%rax), %rax    # %rax = *((uint64_t *)pe + 2); 获取 e 的 vptr2
        movq    (%rax), %rax      # %rax = *(uint64_t *)vptr2; 获取 D::g() 的地址
        movq    -24(%rbp), %rdx   # %rdx = pe = &e;
        addq    $16, %rdx         # %rdx = (uint64_t *)&e + 2; 获取e中D的部分的起始地址
        movq    %rdx, %rdi        
        call    *%rax             # D::g((D *)((uint64_t *)&e + 2));
        
        ## pb->f();
        movq    -32(%rbp), %rax   # %rax = pb;
        movq    (%rax), %rax      # %rax = *(uint64_t *)pb; 获取 e 的 vptr1
        movq    (%rax), %rdx      # %rdx = *(uint64_t *)vptr1; 获取 B::f() 的地址
        movq    -32(%rbp), %rax   # %rax = pb;
        movq    %rax, %rdi
        call    *%rdx             # B::f(pb);
        
        ## pd->g();
        movq    -40(%rbp), %rax   # %rax = pd;
        movq    (%rax), %rax      # %rax = *(uint64_t *)pd; 获取 e 的 vptr2
        movq    (%rax), %rdx      # %rax = *(uint64_t *)vptr2; 获取 D::g() 的地址
        movq    -40(%rbp), %rax   # %rax = pd;
        movq    %rax, %rdi
        call    *%rdx             # D::g(pd);
        
        leaq    -80(%rbp), %rax
        movq    %rax, %rdi
        call    E::~E() [complete object destructor]
        movl    $0, %eax
        
        jmp     .L16
        movq    %rax, %rbx
        leaq    -80(%rbp), %rax
        movq    %rax, %rdi
        call    E::~E() [complete object destructor]
        movq    %rbx, %rax
        movq    %rax, %rdi
        call    _Unwind_Resume
.L16:
        movq    -8(%rbp), %rbx
        leave
        ret
vtable for E:
        .quad   0
        .quad   typeinfo for E
        .quad   B::f()
        .quad   E::~E() [complete object destructor]
        .quad   E::~E() [deleting destructor]
        .quad   -16
        .quad   typeinfo for E
        .quad   D::g()
        .quad   non-virtual thunk to E::~E() [complete object destructor]
        .quad   non-virtual thunk to E::~E() [deleting destructor]
vtable for D:
        .quad   0
        .quad   typeinfo for D
        .quad   D::g()
        .quad   D::~D() [complete object destructor]
        .quad   D::~D() [deleting destructor]
vtable for B:
        .quad   0
        .quad   typeinfo for B
        .quad   B::f()
        .quad   B::~B() [complete object destructor]
        .quad   B::~B() [deleting destructor]
typeinfo for E:
        .quad   vtable for __cxxabiv1::__vmi_class_type_info+16
        .quad   typeinfo name for E
        .long   0
        .long   2
        .quad   typeinfo for B
        .quad   2
        .quad   typeinfo for D
        .quad   4098
typeinfo name for E:
        .string "1E"
typeinfo for D:
        .quad   vtable for __cxxabiv1::__class_type_info+16
        .quad   typeinfo name for D
typeinfo name for D:
        .string "1D"
typeinfo for B:
        .quad   vtable for __cxxabiv1::__class_type_info+16
        .quad   typeinfo name for B
typeinfo name for B:
        .string "1B"
```

main 运行过程中的内存布局：
```
8   +----------------+
    |    old %rbp    |
0   +----------------+  <--- %rbp
    |    old %rbx    |
-8  +----------------+
    |                |
-16 +----------------+
    |       pe       |----------+
-24 +----------------+          |
    |       pb       |----------+
-32 +----------------+          |
    |       pd       |-----+    |
-40 +----------------+     |    |
    |      m_e       |     |    |
-48 +----------------+     |    |
    |      m_d       |     |    |
-56 +----------------+     |    |
    |     vptr2      |     |    |
-64 +----------------+  <--+    |
    |      m_b       |          |
-72 +----------------+          |
    |     vptr1      |          |
-80 +----------------+  <-------+ %rsp
```

**派生类覆盖了第二个基类的方法**
```cpp
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
    pd->g();  // 实际调用的是 E 重写的 g()，而不是基类 D 的 g()
}
```

重点关注 `pd->g()` 的汇编代码：
```assembly
.LC0:
        .string "B::f()"
B::f():
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movq    %rdi, -8(%rbp)
        movl    $.LC0, %edi
        call    puts
        nop
        leave
        ret
.LC1:
        .string "B::~B()"
B::~B() [base object destructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movq    %rdi, -8(%rbp)
        movl    $vtable for B+16, %edx
        movq    -8(%rbp), %rax
        movq    %rdx, (%rax)
        movl    $.LC1, %edi
        call    puts
        nop
        leave
        ret
B::~B() [deleting destructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movq    %rdi, -8(%rbp)
        movq    -8(%rbp), %rax
        movq    %rax, %rdi
        call    B::~B() [complete object destructor]
        movq    -8(%rbp), %rax
        movl    $16, %esi
        movq    %rax, %rdi
        call    operator delete(void*, unsigned long)
        leave
        ret
.LC2:
        .string "D::g()"
D::g():
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movq    %rdi, -8(%rbp)
        movl    $.LC2, %edi
        call    puts
        nop
        leave
        ret
.LC3:
        .string "D::~D()"
D::~D() [base object destructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movq    %rdi, -8(%rbp)
        movl    $vtable for D+16, %edx
        movq    -8(%rbp), %rax
        movq    %rdx, (%rax)
        movl    $.LC3, %edi
        call    puts
        nop
        leave
        ret
D::~D() [deleting destructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movq    %rdi, -8(%rbp)
        movq    -8(%rbp), %rax
        movq    %rax, %rdi
        call    D::~D() [complete object destructor]
        movq    -8(%rbp), %rax
        movl    $16, %esi
        movq    %rax, %rdi
        call    operator delete(void*, unsigned long)
        leave
        ret
.LC4:
        .string "E::g()"
E::g():
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movq    %rdi, -8(%rbp)
        movl    $.LC4, %edi
        call    puts
        nop
        leave
        ret
non-virtual thunk to E::g():
        ; %rdi 指向 e 的D部分的起始位置，这里减了16，偏移到e的起始位置
        ; 这样 E::g() 才能正确地访问对象 e，而不是只能访问e中的D部分
        subq    $16, %rdi
        
        jmp     .LTHUNK0
.LC5:
        .string "E::~E()"
E::~E() [base object destructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movq    %rdi, -8(%rbp)
        movl    $vtable for E+16, %edx
        movq    -8(%rbp), %rax
        movq    %rdx, (%rax)
        movl    $vtable for E+64, %edx
        movq    -8(%rbp), %rax
        movq    %rdx, 16(%rax)
        movl    $.LC5, %edi
        call    puts
        movq    -8(%rbp), %rax
        addq    $16, %rax
        movq    %rax, %rdi
        call    D::~D() [base object destructor]
        movq    -8(%rbp), %rax
        movq    %rax, %rdi
        call    B::~B() [base object destructor]
        nop
        leave
        ret
non-virtual thunk to E::~E() [complete object destructor]:
        subq    $16, %rdi
        jmp     .LTHUNK1
E::~E() [deleting destructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movq    %rdi, -8(%rbp)
        movq    -8(%rbp), %rax
        movq    %rax, %rdi
        call    E::~E() [complete object destructor]
        movq    -8(%rbp), %rax
        movl    $40, %esi
        movq    %rax, %rdi
        call    operator delete(void*, unsigned long)
        leave
        ret
non-virtual thunk to E::~E() [deleting destructor]:
        subq    $16, %rdi
        jmp     .LTHUNK2
B::B() [base object constructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        movq    %rdi, -8(%rbp)
        movl    $vtable for B+16, %edx
        movq    -8(%rbp), %rax
        movq    %rdx, (%rax)
        nop
        popq    %rbp
        ret
D::D() [base object constructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        movq    %rdi, -8(%rbp)
        movl    $vtable for D+16, %edx
        movq    -8(%rbp), %rax
        movq    %rdx, (%rax)
        nop
        popq    %rbp
        ret
E::E() [base object constructor]:
        pushq   %rbp
        movq    %rsp, %rbp
        subq    $16, %rsp
        movq    %rdi, -8(%rbp)
        movq    -8(%rbp), %rax
        movq    %rax, %rdi
        call    B::B() [base object constructor]
        movq    -8(%rbp), %rax
        addq    $16, %rax
        movq    %rax, %rdi
        call    D::D() [base object constructor]
        movl    $vtable for E+16, %edx
        movq    -8(%rbp), %rax
        movq    %rdx, (%rax)
        movl    $vtable for E+64, %edx
        movq    -8(%rbp), %rax
        movq    %rdx, 16(%rax)
        nop
        leave
        ret
main:
        pushq   %rbp
        movq    %rsp, %rbp
        pushq   %rbx
        subq    $72, %rsp
        
        ; E e;
        leaq    -80(%rbp), %rax
        movq    %rax, %rdi
        call    E::E() [complete object constructor]
        
        ; E *pe = &e;
        leaq    -80(%rbp), %rax
        movq    %rax, -24(%rbp)
        
        ; B *pb = &e;
        leaq    -80(%rbp), %rax
        movq    %rax, -32(%rbp)
        
        ; D *pd = &e;
        leaq    -80(%rbp), %rax
        addq    $16, %rax
        movq    %rax, -40(%rbp)
        
        ; pe->f();
        movq    -24(%rbp), %rax
        movq    (%rax), %rax
        movq    (%rax), %rdx
        movq    -24(%rbp), %rax
        movq    %rax, %rdi
        call    *%rdx
        
        ; pe->g();
        movq    -24(%rbp), %rax
        movq    (%rax), %rax
        addq    $24, %rax
        movq    (%rax), %rdx
        movq    -24(%rbp), %rax
        movq    %rax, %rdi
        call    *%rdx
        
        ; pb->f();
        movq    -32(%rbp), %rax
        movq    (%rax), %rax
        movq    (%rax), %rdx
        movq    -32(%rbp), %rax
        movq    %rax, %rdi
        call    *%rdx
        
        ; pd->g();
        movq    -40(%rbp), %rax
        movq    (%rax), %rax
        movq    (%rax), %rdx
        movq    -40(%rbp), %rax
        movq    %rax, %rdi
        call    *%rdx
        
        leaq    -80(%rbp), %rax
        movq    %rax, %rdi
        call    E::~E() [complete object destructor]
        movl    $0, %eax
        
        jmp     .L17
        movq    %rax, %rbx
        leaq    -80(%rbp), %rax
        movq    %rax, %rdi
        call    E::~E() [complete object destructor]
        movq    %rbx, %rax
        movq    %rax, %rdi
        call    _Unwind_Resume
.L17:
        movq    -8(%rbp), %rbx
        leave
        ret
vtable for E:
        .quad   0
        .quad   typeinfo for E
        .quad   B::f()
        .quad   E::~E() [complete object destructor]
        .quad   E::~E() [deleting destructor]
        .quad   E::g()
        .quad   -16
        .quad   typeinfo for E
        .quad   non-virtual thunk to E::g()  ; non-virtual thunk 到底干了什么？
        .quad   non-virtual thunk to E::~E() [complete object destructor]
        .quad   non-virtual thunk to E::~E() [deleting destructor]
vtable for D:
        .quad   0
        .quad   typeinfo for D
        .quad   D::g()
        .quad   D::~D() [complete object destructor]
        .quad   D::~D() [deleting destructor]
vtable for B:
        .quad   0
        .quad   typeinfo for B
        .quad   B::f()
        .quad   B::~B() [complete object destructor]
        .quad   B::~B() [deleting destructor]
typeinfo for E:
        .quad   vtable for __cxxabiv1::__vmi_class_type_info+16
        .quad   typeinfo name for E
        .long   0
        .long   2
        .quad   typeinfo for B
        .quad   2
        .quad   typeinfo for D
        .quad   4098
typeinfo name for E:
        .string "1E"
typeinfo for D:
        .quad   vtable for __cxxabiv1::__class_type_info+16
        .quad   typeinfo name for D
typeinfo name for D:
        .string "1D"
typeinfo for B:
        .quad   vtable for __cxxabiv1::__class_type_info+16
        .quad   typeinfo name for B
typeinfo name for B:
        .string "1B"
```