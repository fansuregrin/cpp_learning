// topic: Regular Expression Classes and the Input Sequence Type

#include <regex>
#include <string>
#include <iostream>

using namespace std;

int main() {
    // the type of the match argument and the type of the input sequence need be matched

    // one or more alphanumeric characters followed by a '.' followed by "cpp" or "cxx" or "cc"
    regex r1("[[:alnum:]]+\\.(cpp|cxx|cc)$", regex::icase);
    smatch results1;
    string filename1 = "test.cc";
    if (regex_search(filename1, results1, r1)) {
        cout << results1.str() << endl;
    }

    cmatch results2;  // to search a character array
    if (regex_search("a.cPp", results2, r1)) {
        cout << results2.str() << endl;
    }

    wregex r2(L"[[:alnum:]]+\\.(cpp|cxx|cc)$", regex::icase);
    wsmatch results3;
    wstring filename2 = L"hello.cC";
    if (regex_search(filename2, results3, r2)) {
        wcout << results3.str() << endl;
    }

    return 0;
}