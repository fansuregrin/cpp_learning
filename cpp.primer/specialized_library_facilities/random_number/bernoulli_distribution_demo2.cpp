// topic: Bernoulli Distribution

#include <random>
#include <iostream>

using namespace std;

int main() {
    default_random_engine e;
    bernoulli_distribution b1;
    bernoulli_distribution b2(0.8);

    // visualizing the bernoulli distribution
    vector<int> vals1(2);
    for (size_t i=0; i<100; ++i) {
        ++vals1[b1(e)];
    }
    for (size_t i=0; i<vals1.size(); ++i) {
        cout << i << ": " << string(vals1[i], '*') << endl;
    }
    cout << endl;

    // visualizing the bernoulli distribution
    vector<int> vals2(2);
    for (size_t i=0; i<100; ++i) {
        ++vals2[b2(e)];
    }
    for (size_t i=0; i<vals2.size(); ++i) {
        cout << i << ": " << string(vals2[i], '*') << endl;
    }
}