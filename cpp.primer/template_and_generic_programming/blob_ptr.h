#ifndef BLOB_PTR_H
#define BLOB_PTR_H

#include "blob.h"
#include <memory>
#include <string>
#include <stdexcept>

template <typename T>
class BlobPtr {
public:
    BlobPtr(): curr(0) {}

    BlobPtr(Blob<T>& a, std::size_t sz = 0): wptr(a.data), curr(sz) {}

    T& operator*() const {
        auto p = check(curr, "dereference past end");
        return (*p)[curr];  // (*p) is the vector to which this object points
    }

    BlobPtr& operator++();  // prefix increment

    BlobPtr operator++(int);  // postfix increment

    BlobPtr& operator--();  // prefix decrement

    BlobPtr operator--(int);  // postfix decrement
private:
    // store a weak_ptr, which means the underlying vector might be destroyed
    std::weak_ptr<std::vector<T>> wptr;
    std::size_t curr;  // current position within the array

    // check returns a shared_ptr to the vector if the check succeeds
    std::shared_ptr<std::vector<T>>
    check(std::size_t, const std::string &) const;
};

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator++() {
    // if curr already points past the end of the container, can't increment it
    check(curr, "increment past end of BlobPtr");
    ++curr;  // advance the current state
    return *this;
}

template <typename T>
BlobPtr<T> BlobPtr<T>::operator++(int) {
    // no check needed here; the call to prefix increment will do the check
    BlobPtr ret = *this;  // save the current value
    ++(*this);  // advance one element; prefix ++ checks the increment
    return ret;  // return the saved state
}

template <typename T>
BlobPtr<T> BlobPtr<T>::operator--(int) {
    // no check needed here; the call to prefix decrement will do the check
    BlobPtr ret = *this;  // save the current value
    --(*this);  // fall back one element; prefix -- checks the decrement
    return ret;  // return the saved state
}

template <typename T>
BlobPtr<T>& BlobPtr<T>::operator--() {
    // if curr already points past the begin of the container, can't decrement it
    check(curr, "decrement past begin of BlobPtr");
    --curr;  // fall back the current state
    return *this;
}

template <typename T>
std::shared_ptr<std::vector<T>>
BlobPtr<T>::check(std::size_t i, const std::string & msg) const {
    auto ret = wptr.lock();  // is the vector still around?
    if (!ret) {
        throw std::runtime_error("unbound BlobPtr");
    }
    if (i >= ret->size()) {
        throw std::out_of_range(msg);
    }
    return ret;  // otherwise, return a shared_ptr to the vector
}

#endif