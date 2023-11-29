
struct NoCopy {
    NoCopy() = default;  // use the synthesized default constructor
    NoCopy(const NoCopy&) = delete;  // no copy
    NoCopy& operator=(const NoCopy&) = delete;  // no assignment
    ~NoCopy() = default;  // use the synthesized destructor
};


// The Destructor Should Not be a Deleted Member

struct NoDtor {
    NoDtor() = default;
    ~NoDtor() = delete;
};

int main() {
    NoCopy a, b;

    // error: use of deleted function ‘NoCopy::NoCopy(const NoCopy&)’
    // NoCopy c = a;

    // error: use of deleted function ‘NoCopy& NoCopy::operator=(const NoCopy&)’
    // b = a;

    // error: use of deleted function ‘NoDtor::~NoDtor()’
    // The compiler will not let us define variables or create 
    // temporaries of a type that has a deleted destructor.
    // NoDtor nd;

    // NoDtor *p = new NoDtor(); // ok: but we can't delete p
    // delete p;  // error: use of deleted function ‘NoDtor::~NoDtor()’
    
    return 0;
}