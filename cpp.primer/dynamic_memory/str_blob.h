#ifndef STR_BLOB_H
#define STR_BLOB_H

#include <memory>
#include <vector>
#include <string>
#include <initializer_list>
#include <stdexcept>

using namespace std;

class StrBlob {
public:
    typedef vector<string>::size_type size_type;
    typedef vector<string>::iterator iterator;
    typedef vector<string>::const_iterator const_iterator;

    StrBlob(): data(make_shared<vector<string>>()) {}

    StrBlob(initializer_list<string> il):
    data(make_shared<vector<string>>(il)) {}

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

    string& front() {
        check(0, "front on empty StrBlob");
        return data->front();
    }

    const string& front() const {
        check(0, "front on empty StrBlob");
        return data->front();
    }

    string& back() {
        check(0, "back on empty StrBlob");
        return data->back();
    }

    const string& back() const {
        check(0, "back on empty StrBlob");
        return data->back();
    }

    iterator begin() { return data->begin(); }
    const_iterator begin() const { return data->begin(); }
    iterator end() { return data->end(); }
    const_iterator end() const { return data->end(); }
private:
    shared_ptr<vector<string>> data;

    void check(size_type i, const string& msg) const {
        if (i >= data->size()) {
            throw out_of_range(msg);
        }
    }
};

#endif