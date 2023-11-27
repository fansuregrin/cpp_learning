#include <algorithm>
#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    out << "[";
    for (typename vector<T>::const_iterator iter=v.begin();
    iter!=v.end(); ++iter) {
        if (iter != v.end()-1)
            out << *iter << ", ";
        else
            out << *iter;
    }
    return out << "]";
}

int main() {
    vector<int> ept;

    // run-time error
    // fill_n(ept.begin(), 5, 1);

    // using a `insert iterator` to ensure there are enough elements
    // to hold the output.
    fill_n(back_inserter(ept), 5, 1);

    cout << "ept: " << ept << endl;
}