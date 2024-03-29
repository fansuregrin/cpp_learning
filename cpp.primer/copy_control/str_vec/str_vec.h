#ifndef STR_VEC_H
#define STR_VEC_H

#include <string>
#include <utility>
#include <memory>

using namespace std;

class StrVec {
public:
    typedef std::size_t size_type;

    StrVec(): elements(nullptr), first_free(nullptr), cap(nullptr) {}

    StrVec(const StrVec&);

    StrVec& operator=(const StrVec&);

    ~StrVec();

    // move constructor
    StrVec(StrVec && sv) noexcept: 
    elements(sv.elements), first_free(sv.first_free), cap(sv.cap) {
        // leave sv in a state in which it is safe to run the destructor
        sv.elements = sv.first_free = sv.cap = nullptr;
    }

    StrVec& operator=(StrVec && rhs) noexcept {
        // direct test for self-assignment
        if (this != &rhs) {
            free();  // free existing elements
            // take over resources from rhs
            elements = rhs.elements;
            first_free = rhs.first_free;
            cap = rhs.cap;
            // leave `rhs` in a destructible state
            rhs.elements = rhs.first_free = rhs.cap = nullptr;
        }
        return *this;
    }

    void push_back(const string&);

    void push_back(string &&);

    size_type size() const {
        return first_free - elements;
    }

    size_type capacity() const {
        return cap - elements;
    }

    string * begin() const { return elements; }
    string * end() const { return first_free; }

    const string& operator[](size_type pos) const {
        return *(elements+pos);
    }

    string& operator[](size_type pos) {
        return *(elements+pos);
    }

    template <typename ... Args>
    inline void emplace_back(Args && ... args) {
        chk_n_alloc();
        alloc.construct(first_free++, std::forward<Args>(args)...);
    }
private:
    allocator<string> alloc;  // allocates the elements
    string * elements;  // pointer to the first element in the array
    string * first_free;  // pointer to the first free element in the array
    string * cap;  // pointer to one past the end of the array

    // used by the functions that add elements to the StrVec

    void chk_n_alloc() {
        if (size() == capacity()) reallocate();
    }

    // utilities used by the copy constructor, assignment operator, and destructor

    // get more space and copy the existing elements
    void reallocate();

    // destroy the elements and free the space
    void free();

    pair<string*,string*> alloc_n_copy(const string*, const string *);
};

void StrVec::push_back(const string& s) {
    chk_n_alloc();  // ensure that there is room for another element
    // construct a copy of `s` in the element to which first_free points
    alloc.construct(first_free++, s);
}

void StrVec::push_back(string&& s) {
    chk_n_alloc();  // ensure that there is room for another element
    alloc.construct(first_free++, std::move(s));
}

pair<string*,string*>
StrVec::alloc_n_copy(const string* b, const string * e) {
    // allocate space to hold as many elements as are in the range
    auto data = alloc.allocate(e-b);
    // initialize and return a pair constructed from data and
    // the value returned by uninitialized_copy
    return {data, uninitialized_copy(b, e, data)};
}

void StrVec::free() {
    // may not pass deallocate a 0 pointer;
    // if elements is 0, there's no work to do
    if (elements) {
        // destroy the old elements in reverse order
        for (auto p=first_free; p!=elements; ) {
            alloc.destroy(--p);
        }
        alloc.deallocate(elements, capacity());
    }
}

StrVec::StrVec(const StrVec& other) {
    // call `alloc_n_copy` to allocate exactly as many elements as in `other`
    auto new_data = alloc_n_copy(other.begin(), other.end());
    elements = new_data.first;
    first_free = cap = new_data.second;
}

StrVec& StrVec::operator=(const StrVec& rhs) {
    // call `alloc_n_copy` to allocate exactly as many elements as in `rhs`
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

StrVec::~StrVec() {
    free();
}

void StrVec::reallocate() {
    // we'll allocate space for twice as many elements as the current size
    size_type new_cap = size() ? 2 * size() : 1;
    // allocate new memory
    auto new_data = alloc.allocate(new_cap);
    // move the data from the old memory to the new
    auto dst = new_data;  // points to the next free position in the new array
    auto src = elements;  // points to the next element in the old array
    for (size_type i=0; i!=size(); ++i) {
        alloc.construct(dst++, std::move(*src++));
    }
    free();  // free the old space once we've moved the elements
    elements = new_data;
    first_free = dst;
    cap = elements + new_cap;
}

#endif