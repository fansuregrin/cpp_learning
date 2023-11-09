#include <iostream>

using namespace std;

class Base{
    public:
        virtual void foo(double);
        virtual void foo(int);
};

void Base::foo(double n){
    cout << "inside Base " << n << endl;
}

void Base::foo(int n){
    cout << "inside Base " << n << endl; 
}

class Derived: public Base {
    public:
        void foo(int);
};

void Derived::foo(int n){
    cout << "inside Derived " << n << endl;
}


int main(){
    Base b;
    Derived d;
    Base * pb = &b;

    pb->foo(2.2);   //Base::foo(double)
    pb->foo(10);    //Base::foo(int)

    pb = &d;
    pb->foo(130);   //Derived::foo(int)
    pb->foo(1.2);   //Base::foo(double)

    return 0;
}