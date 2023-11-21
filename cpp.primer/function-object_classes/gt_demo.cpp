#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// Classes that overload the call operator allow objects of its type to be used as if they
// were a function. Because such classes can also store state, they can be more flexible
// than ordinary functions.

// determine whether a length of a given word is longer than a stored bound
class GT_cls {
public:
    GT_cls(size_t val = 0): bound(val) {}

    // overload function-call operator
    bool operator()(const string& s) {
        return s.size() > bound;
    }
private:
    string::size_type bound;
};

int main() {
    vector<string> words = {
        "the", "spice", "must", "flow",
        "With", "great", "power", "comes", "great", "responsibility"
    };
    for (int len=2; len<=5; ++len) {
        // Objects of classes that define the call operator are referred to as `function objects`.
        // Such objects “act like functions” because we can call them.

        // use an object of `GT_cls` as a `predicate`
        cout << count_if(words.begin(), words.end(), GT_cls(len))
            << " word(s) has/have more than " << len << " letters" << endl;
    }
}