// topic: normal distributions

#include <iostream>
#include <cmath>
#include <random>
#include <vector>

using namespace std;
    
int main() {
    default_random_engine e;
    // Normal(i.e. Gaussian) Distribution
    normal_distribution<> n(4, 1.5);  // mean is 4, standard deviation is 1.5
    
    // visualizing the normal distribution
    vector<int> vals(9);
    for (size_t i=0; i<200; ++i) {
        unsigned v = lround(n(e));
        if (v < vals.size()) {
            ++vals[v];
        }
    }
    for (size_t i=0; i<vals.size(); ++i) {
        cout << i << ": " << string(vals[i], '*') << endl;
    }
}