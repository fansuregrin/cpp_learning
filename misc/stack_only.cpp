#include <iostream>

using namespace std;

// Objects can only be created and destroyed on the stack.
class StackOnly {
public:
    StackOnly(int data) : data_(data) {
        cout << "StackOnly::StackOnly(int)" << endl;
    }
    
    ~StackOnly() {
        cout << "StackOnly::~StackOnly()" << endl;
    }

    void *operator new(size_t) = delete;
    void operator delete(void *) = delete;

    int data_;
};

int main() {
    // StackOnly *p = new StackOnly(42);
    // delte p;

    StackOnly x(42);
}