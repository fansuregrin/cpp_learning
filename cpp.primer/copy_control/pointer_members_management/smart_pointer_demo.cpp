#ifdef USE_SMART_P
// private class for use by HasPtr only
class U_Ptr {
    typedef unsigned int size_t;
    friend class HasPtr;
    int * ip;
    size_t use;

    U_Ptr(int * p): ip(p), use(1) {}

    ~U_Ptr() {
        delete ip;
    }
};

/* smart pointer class: takes ownership of the dynamically allocated
 * object to which it is bound
 * User code must dynamically allocate an object to initialize a `HasPtr`
 * and must not delete that object; the HasPtr class will delete it
 */
class HasPtr {
    public:
        // HasPtr owns the pointer; `p` must have been dynamically allocated
        HasPtr(int* p, int i): ptr(new U_Ptr(p)), val(i) {}

        // copy members and increment the use count
        HasPtr(const HasPtr& orig):
        ptr(orig.ptr), val(orig.val) {
            ++ptr->use;
        }

        HasPtr& operator=(const HasPtr& rhs) {
            ++rhs.ptr->use;  // increment use count on rhs first
            if (--ptr->use == 0) {
                delete ptr;  // if use count goes to 0 on this object, delete it
            }
            ptr = rhs.ptr;
            val = rhs.val;

            return *this;
        }

        // if use count goes to zero, delete the U_Ptr object
        ~HasPtr() {
            if (--ptr->use == 0) delete ptr;
        }

        // accessors must change to fetch value from U_Ptr object
        int * get_ptr() const {
            return ptr->ip;
        }

        int get_int() const {
            return val;
        }

        // change the appropriate data member
        void set_ptr(int * p) {
            ptr->ip = p;
        }

        void set_int(int i) {
            val = i;
        }

        // return or change the value pointed to, so ok for const objects
        // Note: *ptr->ip is equivalent to *(ptr->ip)

        int get_ptr_val() const {
            return *ptr->ip;
        }

        void set_ptr_val(int i) const {
            *ptr->ip = i;
        }
    private:
        U_Ptr * ptr;  // points to use-counted U_Ptr class
        int val;
};
#else
// class that has a pointer member that behaves like a plain pointer
class HasPtr {
public:
    // copy of the values we're given
    HasPtr(int *p, int i): ptr(p), val(i) { }

    ~HasPtr() {
        delete ptr;
    }

    // const members to return the value of the indicated data member
    int *get_ptr() const { return ptr; }
    int get_int() const { return val; }

    // non const members to change the indicated data member
    void set_ptr(int *p) { ptr = p; }
    void set_int(int i) { val = i; }
    
    // return or change the value pointed to, so ok for const objects
    int get_ptr_val() const { return *ptr; }
    void set_ptr_val(int val) const { *ptr = val; }
private:
    int *ptr;
    int val;
};
#endif

int main() {
    HasPtr p1(new int(42), 10);

    // start a new scope
    {
        HasPtr p2(p1);
        p2.set_int(20);
    } // after this scope, `p2` will be deleted
    
    p1.set_ptr_val(0);

    return 0;
}