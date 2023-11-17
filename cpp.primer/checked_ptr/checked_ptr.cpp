#include <stdexcept>
#include <iostream>

using namespace std;

/*
* smart pointer: Checks access to elements throws an out_of_range
* exception if attempt to access a non-existent element
* users allocate and free the array
*/
class CheckedPtr {
public:
    // no default constructor; CheckedPtrs must be bound to an object
    CheckedPtr(int *b, int *e): beg(b), end(e), curr(b) {}

    int& operator*() {
        return *curr;
    }

    const int& operator*() const {
        return *curr;
    }
    
    CheckedPtr& operator++();  // prefix increment operator
    CheckedPtr& operator--();  // prefix decrement operator

    CheckedPtr operator++(int);  // postfix increment operator
    CheckedPtr operator--(int);  // postfix increment operator
private:
    int * beg;   // pointer to beginning of the array
    int * end;   // one past the end of the array
    int * curr;  // current position within the array
};

// prefix: return reference to incremented object
CheckedPtr& CheckedPtr::operator++() {
    if (curr == end) {
        throw out_of_range("increment past the end of CheckedPtr");
    }
    ++curr;  // advance current state
    return *this;
}

// prefix: return reference to decremented object
CheckedPtr& CheckedPtr::operator--() {
    if (curr == beg) {
        throw out_of_range("decrement past the beginning of CheckedPtr");
    }
    --curr;  // move current state back one element
    return *this;
}

// postfix: increment object but return unchanged value
CheckedPtr CheckedPtr::operator++(int) {
    // no check needed here, the call to prefix increment will do the check
    CheckedPtr ret(*this);  // save current value
    ++(*this);  // advance one element, checking the increment
    return ret;  // return saved state
}

// postfix: decrement object but return unchanged value
CheckedPtr CheckedPtr::operator--(int) {
    // no check needed here, the call to prefix decrement will do the check
    CheckedPtr ret(*this);  // save current value
    --(*this);  // move backward one element and check
    return ret;  // return saved state
}


int main() {
    int arr[5] = {1, 2, 3, 4, 5};

    CheckedPtr p(&arr[0], &arr[4]);

    while (true) {
        try {
            cout << *p++ << endl;
        } catch (exception& e) {
            cout << e.what() << endl;
            break;
        }
    }

    return 0;
}