// topic: Specifying Options for a regex Object

#include <regex>
#include <string>
#include <iostream>

using namespace std;

int main() {
    // one or more alphanumeric characters followed by a '.' followed by "cpp" or "cxx" or "cc"
    regex r("[[:alnum:]]+\\.(cpp|cxx|cc)$", regex::icase);
    smatch results;
    string filename;
    while (cin >> filename) {
        if (filename == ":q") break;
        if (regex_search(filename, results, r)) {
            cout << results.str() << endl;
        }
    }
}