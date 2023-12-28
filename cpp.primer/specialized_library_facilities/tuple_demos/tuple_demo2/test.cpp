#include "sales_data.hpp"
#include "find_book.hpp"
#include <algorithm>


int main() {
    std::vector<std::vector<SalesData>> files = {
        {SalesData("0-3584-1212-9", 2, 21.5), SalesData("0-4787-7003-0", 5, 45.0), SalesData("0-6116-5694-9", 10, 15.5)},
        {SalesData("0-3584-1212-9", 3, 20.0), SalesData("0-8137-7492-6", 4, 38.0)},
        {SalesData("0-6116-5694-9", 10, 14.5), SalesData("0-3584-1212-9", 6, 21.0), SalesData("0-9195-4997-7", 1, 90.0)},
    };
    for (auto &store:files) {
        std::sort(store.begin(), store.end(), compareIsbn);
    }

    reportResults(std::cin, std::cout, files);

    return 0;
}