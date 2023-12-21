// Classes That Act Like Pointers

#include <string>

using namespace std;

class HasPtr {
public:
    // constructor allocates a new string and a new counter, which it sets to 1
    HasPtr(const string &s = string()):
    i(0), ps(new string(s)), use(new size_t(1)) {}

    // copy constructor copies all three data members and increments the counter
    HasPtr(const HasPtr &other):
    i(other.i), ps(other.ps), use(other.use) {
        ++*use;
    }

    HasPtr& operator=(const HasPtr &);

    ~HasPtr() {
        if (--*use == 0) {
            delete ps;
            delete use;
        }
    }
private:
    int i;
    string * ps;
    size_t * use;
};

HasPtr& HasPtr::operator=(const HasPtr & rhs) {
    ++*rhs.use;  // increment the use count of the right-hand operand
    // then decrement this object's counter, if no other users
    // free this object's allocated members
    if (--*use == 0) {
        delete use;
        delete ps;
    }
    // copy data from rhs into this object
    i = rhs.i;
    ps = rhs.ps;
    use = rhs.use;

    return *this;
}