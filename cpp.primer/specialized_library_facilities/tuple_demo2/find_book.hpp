#include "sales_data.hpp"
#include <tuple>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <numeric>

using namespace std;

// `matches` has three members: an index of a store and iterators into that store's vector
typedef tuple<vector<SalesData>::size_type,
              vector<SalesData>::const_iterator,
              vector<SalesData>::const_iterator> matches;

// `files` holds the transactions for every store
// `findBook` returns a vector with an entry for each store that sold the given book
vector<matches>
find(const vector<vector<SalesData>> &files, const string &book) {
    vector<matches> ret;  // initially empty
    // for each store find the range of matching books, if any
    for (auto it=files.cbegin(); it!=files.end(); ++it) {
        // find the range of `SalesData` that have the same ISBN
        auto found = equal_range(it->cbegin(), it->cend(), SalesData(book), compareIsbn);
        if (found.first != found.second) { // this store had sales
            // remember the index of this store and the matching range
            ret.push_back(make_tuple(it-files.cbegin(), found.first, found.second));
        }
    }

    return ret;
}

void reportResults(istream &is, ostream &os, const vector<vector<SalesData>> &files) {
    string s;
    while (is >> s) {
        auto trans = find(files, s);
        if (trans.empty()) {
            cout << s << " not found in any stores!" << endl;
            continue;
        }
        for (const auto &store:trans) {
            os << "store " << get<0>(store) << " sales:"
               << accumulate(get<1>(store), get<2>(store), SalesData(s)) << endl;
        }
    }
}