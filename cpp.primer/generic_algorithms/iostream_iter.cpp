// topic: iostream iterators

#include <vector>
#include <iterator>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    out << "[";
    string sep;
    for (typename vector<T>::const_iterator iter=v.begin();
    iter!=v.end(); ++iter) {
        out << sep << *iter;
        sep = ", ";
    }
    return out << "]";
}

int main() {
    cout << "please input some integers:";
    istream_iterator<int> in_iter(cin);
    istream_iterator<int> eof;

    vector<int> vec(in_iter, eof);

    // vector<int> vec;
    // while (in_iter != eof) {
    //     vec.push_back(*in_iter++);
    // }

    cout << "vec: " << vec << endl;
    ostream_iterator<int> out_iter(cout, " ");

    sort(vec.begin(), vec.end());
    unique_copy(vec.begin(), vec.end(), out_iter);
    cout << "\n";

    istringstream str_in("the spice must flow");
    istream_iterator<string> src_iter(str_in), eof2;
    ostream_iterator<string> dst_iter(cout, ", ");
    while (src_iter != eof2) {
        *dst_iter++ = *src_iter++;
    }
    cout << endl;

    return 0;
}