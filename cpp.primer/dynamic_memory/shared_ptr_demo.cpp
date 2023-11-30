// topic: shared_ptr
// `shared_ptr` is a type of `smart pointers` that manage dynamic objects.
// It allows multiple pointers to refer to the same object.

#include <memory>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Foo {
public:
    Foo(){
        cout << "calling default constructor" << endl;
    }

    Foo(const Foo&) {
        cout << "calling copy constructor" << endl;
    }

    Foo& operator=(const Foo&) {
        cout << "calling copy-assignment operator" << endl;
        return *this;
    }

    ~Foo() {
        cout << "calling destructor" << endl;
    }
};

// factory returns a shared_ptr pointing to a dynamically allocated object
shared_ptr<Foo> factory() {
    // shared_ptr will take care of deleting this memory
    return make_shared<Foo>();
}

void use_factory_1() {
    auto p = factory();
} // p goes out of scope; the memory to which p points is automatically freed

shared_ptr<Foo> use_factory_2() {
    auto p = factory();
    return p;  // reference count is incremented when we return p
} // p goes out of scope; the memory to which p points is not freed

int main() {
    shared_ptr<string> p1;  // `shared_ptr` that can point at a `string`
    shared_ptr<vector<int>> p2;  // `shared_ptr` that can point at a vector of ints

    // We use a smart pointer in ways that are similar to using a pointer.

    // if `p1` is not null, check whether it's the empty string
    if (p1 && p1->empty()) {
        *p1 = "hi"; // if so, dereference p1 to assign a new value to that string
    }

    // The safest way to allocate and use dynamic memory is to call 
    // a library function named `make_shared`, which allocates and initializes
    // an object in dynamic memory and returns a shared_ptr that points to that object.

    // shared_ptr that points to an int with value 43
    auto p3 = make_shared<int>(43);
    // p4 points to a string with value 9999999999
    auto p4 = make_shared<string>(10, '9');
    // p5 points to an empty string
    auto p5 = make_shared<string>();

    // When we copy or assign a shared_ptr, each shared_ptr keeps track of how many
    // other shared_ptrs point to the same object
    
    // coping shared_ptr
    auto p6(p4);  // p6 and p4 point to the same object
                  // object to which p4 and p6 point has two users

    auto p7 = make_shared<int>(10); // int to which p7 points has one user
    // assigning shared_ptr
    p7 = p3;  // assign to p7, making it point to a different address
              // increase the use count for the object to which p3 points
              // reduce the use count of the object to which p7 had pointed
              // the object p7 had pointed to has no users; that object is automatically freed

    cout << "*p3: " << *p3 << endl;
    cout << "*p4: " << *p4 << endl;
    cout << "*p5: " << *p5 << endl;
    cout << "*p6: " << *p6 << endl;

    cout << "---------------------------------" << endl;

    auto sp1 = make_shared<Foo>();
    auto sp2 = make_shared<Foo>();
    auto sp3(sp1);
    sp2 = sp1;  // the object `sp2` had pointed to will be freed

    use_factory_1();
    auto sp4 = use_factory_2();

    cout << "---------------------------------" << endl;

    return 0;
}