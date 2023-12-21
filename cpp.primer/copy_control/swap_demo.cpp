#include <string>
#include <utility>

using namespace std;

class HasPtr {
    friend void swap(HasPtr&, HasPtr&);
public:
    HasPtr(const string &s = string()): ps(new string(s)), i(0) {}

    HasPtr(const HasPtr &other): ps(new string(*other.ps)), i(other.i) {}

    HasPtr& operator=(HasPtr);

    ~HasPtr() { delete ps; }
private:
    string * ps;
    int i;
};

inline void swap(HasPtr &lhs, HasPtr &rhs) {
    using std::swap;
    swap(lhs.ps, rhs.ps);  // swap the pointers, not the string data
    swap(lhs.i, rhs.i);  // swap the int members
}

// copy and swap

// note `rhs` is passed by value, which means the `HasPtr` copy constructor
// copies the string in the right-hand operand into `rhs`.
HasPtr& HasPtr::operator=(HasPtr rhs) {
    // swap the contents of the left-hand operand with the local variable rhs
    swap(*this, rhs); // rhs now points to the memory this object had used
    return *this; // rhs is destroyed, which deletes the pointer in rhs
}

int main() {
    HasPtr p1(string("Tom")), p2(string("Jerry"));

    // This code copies the string that was originally in p1 twice 
    // and also copies the string that was originally in p2 when it assigns p2 to p1.
    // HasPtr tmp = p2;
    // p2 = p1;
    // p1 = tmp;

    swap(p1, p2);

    HasPtr p3(string("..."));
    p3 = p1;

    return 0;
}