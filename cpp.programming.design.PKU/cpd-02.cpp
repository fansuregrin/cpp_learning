// coursera C++程序设计
// 第 3 周 编程作业—类和对象 第一题
#include <iostream>
using namespace std;
class A {
public:
    int val;
    // constructor
    A(int n=0){ val = n; }
    int & GetObj(){
        return val;
    }
};
int main() {
    A a;
    cout << a.val << endl;
    a.GetObj() = 5;
    cout << a.val << endl;
    return 0;
}