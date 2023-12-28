#include "sales_data.hpp"
#include <tuple>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <numeric>


// `matches` has three members: an index of a store and iterators into that store's std::vector
typedef std::tuple<std::vector<SalesData>::size_type,
              std::vector<SalesData>::const_iterator,
              std::vector<SalesData>::const_iterator> matches;

// `files` holds the transactions for every store
// `findBook` returns a std::vector with an entry for each store that sold the given book
std::vector<matches>
find(const std::vector<std::vector<SalesData>> &files, const std::string &book) {
    std::vector<matches> ret;  // initially empty
    // for each store find the range of matching books, if any
    for (auto it=files.cbegin(); it!=files.end(); ++it) {
        // find the range of `SalesData` that have the same ISBN
        auto found = std::equal_range(it->cbegin(), it->cend(), SalesData(book), compareIsbn);
        if (found.first != found.second) { // this store had sales
            // remember the index of this store and the matching range
            ret.push_back(std::make_tuple(it-files.cbegin(), found.first, found.second));
        }
    }

    return ret;
}

void reportResults(std::istream &is, std::ostream &os, const std::vector<std::vector<SalesData>> &files) {
    std::string s;
    while (is >> s) {
        auto trans = find(files, s);
        if (trans.empty()) {
            os << s << " not found in any stores!" << std::endl;
            continue;
        }
        for (const auto &store:trans) {
            os << "store " << std::get<0>(store) << " sales:"
               << accumulate(std::get<1>(store), std::get<2>(store), SalesData(s)) << std::endl;
        }
    }
}