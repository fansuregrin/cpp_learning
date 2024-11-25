#include <memory>
#include <functional>
#include <iostream>
#include <thread>
#include <chrono>

class A: public std::enable_shared_from_this<A> {
public:
    A() = default;
    A(int v) : v_(v) {}
    ~A() {
        std::cout << "A::~A()" << std::endl;
    }

    void f() {
        std::cout << "value is " << v_ << std::endl;
    }

    void runInNewThread() {
        std::thread(std::bind(&A::f, shared_from_this())).detach();
    }
private:
    int v_;
};

int main() {
    {
        auto a = std::make_shared<A>(42);
        a->runInNewThread();
    }

    std::this_thread::sleep_for(std::chrono::seconds(5));
}