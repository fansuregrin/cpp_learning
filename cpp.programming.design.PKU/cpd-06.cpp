// coursera C++程序设计
// 第 4 周 编程作业—运算符重载 第一题
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

class Complex {
    private:    
        double r,i;
    public:    
        void Print() {
            cout << r << "+" << i << "i" << endl;
        }
        // 在此处补充你的代码
        Complex & operator=(const char * s){
            char real[100] = {0};
            char image[100] = {0};
            int i = 0, j = 0;
            while(s[i] != '+'){
                real[j] = s[i];
                ++i; ++j;
            }
            ++i; j = 0;
            while(s[i] != 'i' && s[i] != 0){
                image[j] = s[i];
                ++i; ++j;
            }
            this->r = atof(real);
            this->i = atof(image);
            return *this;
        }
};

int main() {
    Complex a;
    a = "3+4i"; a.Print();
    a = "5+6i"; a.Print();
    return 0;
}