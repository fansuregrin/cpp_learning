// topic: regex iterator

#include <regex>
#include <string>
#include <iostream>

using namespace std;

int main() {
    string pattern_text("[[:alpha:]]*[^c]ei[[:alpha:]]*");
    regex r(pattern_text, regex::icase);
    string file("receipt freind theif receive");
    for (sregex_iterator it(file.begin(), file.end(), r), end_it;
    it!=end_it; ++it) {
        cout << it->str() << endl;
    }
}