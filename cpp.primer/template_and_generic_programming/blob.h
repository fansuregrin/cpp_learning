#ifndef BLOB_H
#define BLOB_H

#include <memory>
#include <vector>
#include <initializer_list>
#include <stdexcept>

using namespace std;

template<typename T>
class Blob {
public:
    typedef T value_type;
    typedef typename vector<T>::size_type size_type;
    typedef typename vector<T>::iterator iterator;
    typedef typename vector<T>::const_iterator const_iterator;

    Blob(): data(make_shared<vector<T>>()) {}

    Blob(initializer_list<T> il):
    data(make_shared<vector<T>>(il)) {}

    size_type size() const {
        return data->size();
    }

    bool empty() {
        return data->empty();
    }

    void push_back(const string & t) {
        data->push_back(t);
    }

    void pop_back() {
        check(0, "pop_back on empty StrBlob");
        data->pop_back();
    }

    T& front() {
        check(0, "front on empty StrBlob");
        return data->front();
    }

    const T& front() const {
        check(0, "front on empty StrBlob");
        return data->front();
    }

    T& back() {
        check(0, "back on empty StrBlob");
        return data->back();
    }

    const T& back() const {
        check(0, "back on empty StrBlob");
        return data->back();
    }

    T& operator[](size_type);

    iterator begin() { return data->begin(); }
    const_iterator begin() const { return data->begin(); }
    iterator end() { return data->end(); }
    const_iterator end() const { return data->end(); }
private:
    shared_ptr<vector<T>> data;

    void check(size_type i, const string& msg) const {
        if (i >= data->size()) {
            throw out_of_range(msg);
        }
    }
};

template <typename T>
T& Blob<T>::operator[](Blob<T>::size_type i) {
    check(i, "subscript out of range");
    return (*data)[i];
}

#endif