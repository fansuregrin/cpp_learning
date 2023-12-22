#include "sales_data.hpp"
#include <unordered_set>
#include <iostream>

using namespace std;

int main() {
    unordered_multiset<SalesData> SD_set;
    SD_set.insert(SalesData("4-662-30596-9"));
    for (int i=0; i<2; ++i) {
        SD_set.insert(SalesData("6-658-22398-X", 3, 11.9));
    }

    for (const auto& sale:SD_set) {
        print(cout, sale);
        cout << endl;
    }

    return 0;
}