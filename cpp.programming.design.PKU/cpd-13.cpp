// coursera C++程序设计
// 第 6 周 编程作业—多态与虚函数 第二题
#include <iostream>
using namespace std;
class A {
    // 在此处补充你的代码
    public:
        virtual ~A(){ cout << "destructor A" << endl; }
};
class B:public A {
    public:
        ~B() { cout << "destructor B" << endl; }
};
int main() {
    A * pa;
    pa = new B;
    delete pa;
    return 0;
}