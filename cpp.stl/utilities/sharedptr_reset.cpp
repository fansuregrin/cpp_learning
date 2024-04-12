/**
 * @file sharedptr_reset.cpp
 * @brief 演示 reset 的用法和背后的原理
*/

#include <iostream>
#include <memory>

struct Foo {
    Foo(int n = 0) noexcept : bar(n) {
        std::cout << "Foo::Foo(), bar = " << bar << " @ " << this << '\n';
    }

    ~Foo() {
        std::cout << "Foo::~Foo(), bar = " << bar << " @ " << this << '\n';
    }

    int get_bar() const noexcept { return bar; }
private:
    int bar;
};


int main() {
    std::cout << "1) unique ownership\n";
    {
        auto sptr = std::make_shared<Foo>(100);
        std::cout << "Foo::bar = " << sptr->get_bar() << ", use_count() = "
            << sptr.use_count() << '\n';
        std::cout << "call sptr.reset()...\n";
        sptr.reset();  // 会调用 Foo 的析构函数 Foo::~Foo()
        std::cout << "After reset(): use_count() = " << sptr.use_count()
            << ", sptr = " << sptr << '\n';
    }

    std::cout << "\n2) unique ownership\n";
    {
        auto sptr = std::make_shared<Foo>(200);
        std::cout << "Foo::bar = " << sptr->get_bar() << ", use_count() = " 
            << sptr.use_count() << '\n';
        std::cout << "call sptr.reset()...\n";
        sptr.reset(new Foo(222));
        std::cout << "After reset(): use_count() = " << sptr.use_count()
            << ", sptr = " << sptr << "\nLeaving the scope...\n";
    }

    std::cout << "\n3) multiple ownership\n";
    {
        auto sptr1 = std::make_shared<Foo>(300);
        auto sptr2 = sptr1;
        auto sptr3 = sptr2;

        std::cout << "Foo::bar = " << sptr1->get_bar() << ", use_count() = " 
            << sptr1.use_count() << '\n';
        std::cout << "call sptr1.reset()...\n";
        // 重置 `sptr1` 让其指向 `Foo(333)` 这个对象
        // 指向 `Foo(300)` 的指针数量减1
        sptr1.reset(new Foo(333));

        std::cout << "After reset():\n"
            << "sptr1.use_count() = " << sptr1.use_count()
            << ", sptr1 @ " << sptr1 << '\n'
            << "sptr2.use_count() = " << sptr2.use_count()
            << ", sptr2 @ " << sptr2 << '\n'
            << "sptr3.use_count() = " << sptr3.use_count()
            << ", sptr3 @ " << sptr3 << '\n'
            << "Leaving the scope...\n";
    }
}