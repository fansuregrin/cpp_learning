// topic: unique_ptr
// `unique_ptr` is a type of `smart pointers` that manage dynamic objects.
// It “owns” the object to which it points.
// Unlike `shared_ptr`, only one unique_ptr at a time can point to a given object.

#include <memory>
#include <iostream>

using namespace std;

template<typename T>
ostream& operator<<(ostream& os, const unique_ptr<T>& p) {
    return p ? os << *p : os;
}

unique_ptr<int> clone1(int val) {
    return unique_ptr<int>(new int(val));
}

unique_ptr<int> clone2(int val) {
    unique_ptr<int> ret(new int(val));
    return ret;
}

int main() {
    unique_ptr<double> up1;  // unique_ptr that can point at a double

    // Unlike `shared_ptr`, there is no library function comparable to `make_shared` that
    // returns a `unique_ptr`. Instead, when we define a `unique_ptr`, we bind it to a
    // pointer returned by `new`.
    unique_ptr<int> up2(new int(42));  // p2 points to int with value 42

    // Besides, we must use the direct form of initialization.
    // unique_ptr<int> up3 = new int(42);  // error!

    // Because a unique_ptr owns the object to which it points, 
    // unique_ptr does not support **ordinary copy or assignment**.

    unique_ptr<string> p1(new string(3, '6'));
    
    // error: no copy for unique_ptr
    // unique_ptr<string> p2(p1); // error: use of deleted copy constructor
    
    // unique_ptr<string> p3;
    // error: no assign for unique_ptr
    // p3 = p1;  // use of deleted copy-assignment operator

    // Although we can’t copy or assign a unique_ptr, we can **transfer ownership**
    // from one (nonconst) unique_ptr to another by calling release or reset.

    // transfers ownership from p1 (which points to the string "666") to p2
    unique_ptr<string> p2(p1.release()); // `release` make p1 points to null

    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;

    unique_ptr<string> p3(new string(3, '9'));
    cout << "before transfering ownership from p3 to p2" << endl;
    cout << "p2: " << p2 << endl;
    cout << "p3: " << p3 << endl;
    // transfers ownership from p3 to p2
    p2.reset(p3.release());  // reset deletes the memory to which p2 had pointed
    cout << "after transfering ownership from p3 to p2" << endl;
    cout << "p2: " << p2 << endl;
    cout << "p3: " << p3 << endl;

    // WRONG: p2 won't free the memory and we've lost the pointer
    // p2.release();
    // auto p = p2.release(); // ok, but we must remember to delete(p)
    // delete p;

    // There is one exception to the rule that we cannot copy a unique_ptr: We can 
    // copy or assign a unique_ptr that is about to be destroyed.
    
    unique_ptr<int> p4 = clone1(5);
    unique_ptr<int> p5(clone2(5));

    return 0;
}