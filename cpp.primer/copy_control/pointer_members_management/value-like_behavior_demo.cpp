/*
* Valuelike behavior even though HasPtr has a pointer member:
* Each time we copy a HasPtr object, we make a new copy of the
* underlying int object to which ptr points.
*/
class HasPtr {
public:
    // no point to passing a pointer if we're going to copy it anyway
    // store pointer to a copy of the object we're given
    HasPtr(const int& p, int i): ptr(new int(p)), val(i) {}

    // copy members and increment the use count
    HasPtr(const HasPtr& orig): ptr(new int(*orig.ptr)), val(orig.val) {}

    HasPtr& operator=(const HasPtr& rhs) {
        // Note: Every HasPtr is guaranteed to point at an actual int;
        // We know that ptr cannot be a zero pointer
        *ptr = *rhs.ptr;
        val = rhs.val;

        return *this;
    }

    ~HasPtr() {
        delete ptr;
    }

    // accessors must change to fetch value from Ptr object
    int get_ptr_val() const { return *ptr; }
    int get_int() const { return val; }

    // change the appropriate data member
    void set_ptr(int *p) { ptr = p; }
    void set_int(int i) { val = i; }

    // return or change the value pointed to, so ok for const objects
    int *get_ptr() const { return ptr; }
    void set_ptr_val(int p) const { *ptr = p; }
private:
    int * ptr;
    int val;
};

int main() {
    HasPtr p1(42, 10);

    // start a new scope
    {
        HasPtr p2(p1);
        p2.set_int(20);
    } // after this scope, `p2` will be deleted
    
    p1.set_ptr_val(0);

    return 0;
}