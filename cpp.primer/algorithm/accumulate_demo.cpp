#include <numeric>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    vector<double> v1{1.2, 2.3, 3.4, 4.4};
    cout << "sum of v1: " << accumulate(v1.begin(), v1.end(), 0) << endl;
    cout << "sum of v1: " << accumulate(v1.begin(), v1.end(), 0.0) << endl;
}