#include <iostream>
#include <vector>
using namespace std;

class A{
    public:
        A(){
            cout << "调用构造函数 " << this << endl;
        }
        A(const A & a){
            cout << "调用复制构造函数 " << this << endl;
        }
        ~A(){
            cout << "调用析构函数 " << this << endl;
        }
};

int main(){
    vector<A> ctn;
    {
        A temp;
        ctn.push_back(temp);
    }
    return 0;
}