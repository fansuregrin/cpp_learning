// Classes That Act Like Values

#include <string>

using namespace std;

class HasPtr {
public:
    HasPtr(const string &s = string()): ps(new string(s)), i(0) {}

    HasPtr(const HasPtr &other): ps(new string(*other.ps)), i(other.i) {}

    HasPtr& operator=(const HasPtr &);

    ~HasPtr() { delete ps; }
private:
    string * ps;
    int i;
};

HasPtr& HasPtr::operator=(const HasPtr &rhs) {
    string * tmp = new string(*rhs.ps);
    delete ps;
    ps = tmp;
    i = rhs.i;

    return *this;
}

// Key Concept: Assignment Operators
// There are two points to keep in mind when you write an assignment
// operator:
//  • Assignment operators must work correctly if an object is assigned to itself.
//  • Most assignment operators share work with the destructor and copy constructor.
// A good pattern to use when you write an assignment operator is to first copy
// the right-hand operand into a local temporary. After the copy is done, it is
// safe to destroy the existing members of the left-hand operand. Once the lefthand
// operand is destroyed, copy the data from the temporary into the
// members of the left-hand operand.