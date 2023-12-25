// topic: sub-expressions

#include <regex>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    regex r("([[:alnum:]]+)\\.(cpp|cxx|cc)$", regex::icase);
    smatch results;
    string filename;
    while (cin >> filename) {
        if (filename == ":q") break;
        if (regex_search(filename, results, r)) {
            cout << std::setw(20) << results.str() << " "
                 << std::setw(16) << results.str(1) << " "
                 << std::setw(4)  << results.str(2) << endl;
        }
    }
}