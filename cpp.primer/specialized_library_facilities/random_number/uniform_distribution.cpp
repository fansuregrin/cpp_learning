// topic: uniform distributions

#include <random>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    default_random_engine e;  // generates unsigned random integers
    // uniformly distributed from 0 to 1 inclusive
    uniform_real_distribution<double> u(0, 1);
    string sep;
    for (size_t i=0; i<10; ++i, sep=" ") {
        cout << sep << u(e);
    }
    cout << endl;

    // the distribution types have a default template arguement
    uniform_int_distribution<> int_u(0, 9);  // int
    uniform_real_distribution<> double_u(0, 1);  // double

    // visualizing the uniform distribution
    vector<int> vals(10);
    for (size_t i=0; i<300; ++i) {
        ++vals[int_u(e)];
    }
    for (size_t i=0; i<vals.size(); ++i) {
        cout << i << ": " << string(vals[i], '*') << endl;
    }
}