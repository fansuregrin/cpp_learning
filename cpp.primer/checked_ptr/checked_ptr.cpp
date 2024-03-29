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

    // overload dereference operator (non-const version)
    int& operator*() {
        return *curr;
    }

    // overload dereference operator (const version)
    const int& operator*() const {
        return *curr;
    }

    // overload subscript operator (non-const version)
    int& operator[](const size_t index) {
        if (index > end-beg) {
            throw out_of_range("index of range");
        }
        return *(beg + index);
    }

    // overload subscript operator (const version)
    const int& operator[](const size_t index) const {
        if (index > end-beg) {
            throw out_of_range("index of range");
        }
        return *(beg + index);
    }
    
    CheckedPtr& operator++();  // prefix increment operator
    CheckedPtr& operator--();  // prefix decrement operator

    CheckedPtr operator++(int);  // postfix increment operator
    CheckedPtr operator--(int);  // postfix increment operator

    // implement equality operator
    bool operator==(const CheckedPtr& rhs) {
        return beg == rhs.beg && end == rhs.end;
    }

    // implement inequality operator
    bool operator!=(const CheckedPtr& rhs) {
        return !(*this == rhs);
    }
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
    int arr2[6] = {5, 4, 3, 2, 1, 0};

    CheckedPtr p(&arr[0], &arr[4]);
    CheckedPtr p2(&arr2[0], &arr2[5]);
    CheckedPtr p3 = p;
    const CheckedPtr p4(p);

    // call postfix increment operator of `p`
    while (true) {
        try {
            cout << *p++ << endl;
        } catch (exception& e) {
            cout << e.what() << endl;
            break;
        }
    }

    // call subscript operator of `p`
    cout << "p[3] = " << p[3] << endl;
    cout << "before changing value: p[4] = " << p[4] << endl;
    p[4] = 15;
    cout << "after changing value: p[4] = " << p[4] << endl;

    try {
        cout << "p[5] = " << p[5] << endl;
    } catch (exception& e) {
        cout << e.what() << endl;
    }

    // call equality/inequality operator of `CheckedPtr`
    if (p == p3) {
        cout << "p == p3" << endl;
    } else {
        cout << "p != p3" << endl;
    }

    if (p == p2) {
        cout << "p == p2" << endl;
    } else {
        cout << "p != p2" << endl;
    }

    return 0;
}