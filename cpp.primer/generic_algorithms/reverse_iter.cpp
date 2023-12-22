// topic: reverse iterator

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    vector<int> vec;
    for (int i=0; i<10; vec.push_back(i++));

    // output `vec` backward
    string sep;
    for (vector<int>::const_reverse_iterator r_iter = vec.crbegin();
    r_iter != vec.crend(); ++r_iter) {
        cout << sep << *r_iter;
        sep = ", ";
    }
    cout << endl;

    // sort `vec` in descedent order
    sort(vec.rbegin(), vec.rend());

    string line("the,spice,must,flow");
    
    string::iterator comma = find(line.begin(), line.end(), ',');
    cout << "first word: " << string(line.begin(), comma) << endl;
    
    string::reverse_iterator r_comma = find(line.rbegin(), line.rend(), ',');

    // the output is "last word: wolf", which doesn't meet our expectation
    // cout << "last word: " << string(line.rbegin(), r_comma) << endl;
    cout << "last word: " << string(r_comma.base(), line.end()) << endl;

    return 0;
}