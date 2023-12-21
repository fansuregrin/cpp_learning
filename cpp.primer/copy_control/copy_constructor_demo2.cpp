#include <iostream>
#include <vector>

using namespace std;

class X {
private:
    int val;
public:
    X(): val(0) {
        cout << "Calling consturctor (default) of class `X`." << endl;
    }

    X(int val_): val(val_) {
        cout << "Calling consturctor (1 argument) of class `X`." << endl;
    }

    X(const X& other) {
        this->val = other.val;
        cout << "Calling copy constructor of class `X`." << endl;
    }

    X(X&& other) {
        this->val = move(other.val);
        cout << "Calling move constructor of class `X`." << endl;
    }

    X& operator=(const X& other) {
        this->val = other.val;
        cout << "Calling operator= (copy) of class `X`." << endl;
        
        return *this;
    }

    X& operator=(X&& other) {
        this->val = move(other.val);
        cout << "Calling operator= (move) of class `X`." << endl;

        return *this;
    }

    int get_val() {
        return val;
    }
};

X foo(int val) {
    X t(val);
    return t;
}

void bar(X a) {

}

int main(void) {
    X a;
    a = foo(4);
    X b(5);
    a = b;
    X c(b);
    X d(foo(6));

    bar(c);

    cout << "a.val = " << a.get_val() << endl;
    cout << "b.val = " << b.get_val() << endl;
    cout << "c.val = " << c.get_val() << endl;
    cout << "d.val = " << d.get_val() << endl;

    vector<X> v1(3);
    vector<X> v2 = {1, 2, 3};

    return 0;
}