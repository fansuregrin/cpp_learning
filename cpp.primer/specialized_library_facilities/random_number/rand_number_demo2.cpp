// topic: random distribution

#include <random>
#include <iostream>
#include <vector>

using namespace std;

vector<unsigned> bad_randVec() {
    uniform_int_distribution<unsigned> u(0, 9);
    default_random_engine e;
    vector<unsigned> ret;
    for (size_t i=0; i<10; ++i) {
        ret.push_back(u(e));
    }
    return ret;
}

vector<unsigned> good_randVec() {
    // because engines and distributions retain state, they usually should be
    // defined as static so that new numbers are generated on each call
    static default_random_engine e;
    static uniform_int_distribution<unsigned> u(0, 9);
    vector<unsigned> ret;
    for (size_t i=0; i<10; ++i) {
        ret.push_back(u(e));
    }
    return ret;
}

int main() {
    // uniformly distributed from 0 to 9 inclusive
    uniform_int_distribution<unsigned> u(0, 9);
    default_random_engine e;
    
    // generates 10 random unsigned integers
    string sep;
    for (size_t i=0; i<10; ++i, sep=" ") {
        cout << sep << u(e);
    }
    cout << endl;

    // always "equal"
    cout << ((bad_randVec() == bad_randVec())?"equal":"not equal") << endl;
    cout << ((good_randVec() == good_randVec())?"equal":"not equal") << endl;
}