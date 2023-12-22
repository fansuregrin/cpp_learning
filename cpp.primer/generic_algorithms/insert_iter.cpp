// topic: insert iterators
// These iterators are bound to a container and can be used to
// insert elements into the container.
//
// There are three kinds of inserters. Each differs from the others as
// to where elements are inserted:
// 1) back_inserter: creates an iterator that uses `push_back`.
// 2) front_inserter: creates an iterator that uses `push_front`.
// 3) inserter: creates an iterator that uses `insert`.

#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const list<T>& v) {
    out << "[";
    string sep;
    for (typename list<T>::const_iterator iter=v.begin();
    iter!=v.end(); ++iter) {
        out << sep << *iter;
        sep = ", ";
    }
    return out << "]";
}

int main() {
    list<int> i_lst{1, 2, 3, 4, 5};
    vector<int> v1{-1, -2, -3};

    list<int>::iterator it = find(i_lst.begin(), i_lst.end(), 4);
    
    // replace_copy(v1.begin(), v1.end(), front_inserter(i_lst), -2, 2);
    // replace_copy(v1.begin(), v1.end(), back_inserter(i_lst), -2, 2);
    replace_copy(v1.begin(), v1.end(), inserter(i_lst, it), -2, 2);

    cout << i_lst << endl;

    return 0;
}