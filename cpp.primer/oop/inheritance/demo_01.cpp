#include <iostream>

using namespace std;

class Base {
public:
    void basemem() {
        cout << "calling Base::basemem()" << endl;
    }  // public member
protected:
    int i;  // protected member
private:
    int j;  // private member
};

struct Public_derived: public Base {
    int use_base() {
        return i;  // ok: derived classes can access i
    }
};

struct Protected_derived: protected Base {
    int use_base() {
        return i;  // ok: derived classes can access i
    }
};

struct Private_derived: private Base {
    int use_base() {
        return i;  // ok: derived classes can access i
    }
};

int main() {
    Base b;
    Public_derived d1;
    Private_derived d2;
    Protected_derived d3;
    b.basemem();  // ok: basemem is public
    d1.basemem();  // ok: basemem is public in the derived class

    // error: ‘void Base::basemem()’ is inaccessible within this context
    // error: ‘Base’ is not an accessible base of ‘Private_derived’
    // d2.basemem();  // error: basemem is private in the derived class

    // d3.basemem(); // error: basemem is protected in the derived class

    return 0;
}