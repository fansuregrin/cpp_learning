// topic: Errors in Specifying or Using a Regular Expression

#include <regex>
#include <string>
#include <iostream>

using namespace std;

int main() {
    // one or more alphanumeric characters followed by a '.' followed by "cpp" or "cxx" or "cc"
    try {
        regex r("[[:alnum:]+\\.(cpp|cxx|cc)$", regex::icase);  // code: 4
        // regex r("((.)(.)");  // code: 5
        // regex r("a{3");  // code: 6
        // regex r("[.]{}");  // code: 7
        // regex r("[1-0]");  // code: 8
    } catch (regex_error &e) {
        cout << e.what() << "\ncode: " << e.code() << endl;
    }
}