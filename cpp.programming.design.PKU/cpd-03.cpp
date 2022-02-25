// coursera C++程序设计
// 第 3 周 编程作业—类和对象 第二题
#include <iostream>
using namespace std;
class Sample{
public:
    int v;
    Sample(int n):v(n) { }
    Sample(const Sample & s){
        this->v = 2*s.v;
    }
};
int main() {
    Sample a(5);
    Sample b = a;
    cout << b.v;
    return 0;
}