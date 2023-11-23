
class Base {
    friend class Frnd;
protected:
    int i;
};

class D1: public Base {
protected:
    int j;
};

class Frnd {
public:
    // ok: Frnd is friend to Base
    int mem(const Base& b) {
        return b.i;
    }

    // error: friendship doesn't inherit
    // int mem(const D1& d) {
    //     return d.j;
    // }
};

class D2: public Frnd {
public:
    // D2 has no access to members in Base
    // error: friendship doesn't inherit
    // int mem(const Base& b) {
    //     return b.i;
    // }
};