// topic: template type aliases

#include <utility>
#include <string>

using namespace std;

// The c++11 standard lets us define a type alias for a class template:

// `twin` is a synonym for pairs in which the members have the same type
template<typename T> using twin = pair<T, T>;

// `partNo` is a synonym for the family of types that are pairs in
// which the second member is an unsigned.
template<typename T> using partNo = pair<T, unsigned>;

int main() {
    twin<string> authors;  // authors is a pair<string, string>
    twin<int> win_loss;  // win_loss is a pair<int, int>
    twin<double> area;  // area is a pair<double, double>

    partNo<string> books;  // books is a pair<string, unsigned>
}   