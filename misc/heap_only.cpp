#include <iostream>

using namespace std;

// Objects can only be created and destroyed on the heap.
class HeapOnly {
public:
    static HeapOnly *create(int data = 0) {
        return new HeapOnly(data);
    }

    void destroy() {
        delete this;
    }

private:
    HeapOnly(int data = 0) : data_(data) {
        cout << "HeapOnly::HeapOnly(int)" << endl;
    }

    ~HeapOnly() {
        cout << "HeapOnly::~HeapOnly()" << endl;
    }

    int data_;
};

int main() {
    // error: ‘HeapOnly::HeapOnly(int)’ is private within this context
    // error: ‘HeapOnly::~HeapOnly()’ is private within this context
    // HeapOnly x;
    
    HeapOnly *p = HeapOnly::create(42);
    
    // error: ‘HeapOnly::~HeapOnly()’ is private within this context
    // delete p;
    
    p->destroy();
}