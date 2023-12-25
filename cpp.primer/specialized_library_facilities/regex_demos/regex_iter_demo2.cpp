// topic: regex iterator

#include <regex>
#include <string>
#include <iostream>

using namespace std;

int main() {
    string pattern_text("[[:alpha:]]*[^c]ei[[:alpha:]]*");
    regex r(pattern_text, regex::icase);
    string file("receipt freind theif receive");
    
    const size_t limit_len = 40;
    for (sregex_iterator it(file.begin(), file.end(), r), end_it;
    it!=end_it; ++it) {
        auto pos = it->prefix().length();
        pos = pos > limit_len ? pos - limit_len : 0;
        cout << it->prefix().str().substr(pos)
             << "\n\t>>> " << it->str() << " <<<\n"
             << it->suffix().str().substr(0, limit_len) << endl;
    }
}