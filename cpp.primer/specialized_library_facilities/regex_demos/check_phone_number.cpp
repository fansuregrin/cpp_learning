// topic: Subexpressions for Data Validation

#include <iostream>
#include <regex>
#include <string>

using namespace std;

bool valid(const smatch &m) {
    // if there is an open parenthesis before the area code
    if (m[1].matched) {
        // the area code must be followed by a close parenthesis
        // and followed immediately by the rest of the number or a space
        return m[3].matched && (!m[4].matched || m[4].str() == " ");
    } else {
        // then there can't be a close after the area code
        // the delimiters between the other two components must match
        return !m[3].matched && m[4].str() == m[6].str();
    }
}

int main() {
    // match a potential phonenumber: (ddd) separator ddd separator dddd
    string phone("(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ]?)(\\d{4})");
    regex r(phone);  // a regex to find our pattern
    smatch m;
    string s;
    // read each record from the input file
    cout << "PLEASE ENTER: ";
    while (getline(cin, s)) {
        if (s == "q") break;
        // for each matching phone number
        for (sregex_iterator it(s.begin(), s.end(), r), end_it;
        it != end_it; ++it) {
            // check whether the number's formatting is valid
            if (valid(*it)) {
                cout << "valid: " << it->str() << endl;
            } else {
                cout << "invalid:" << it->str() << endl;
            }
        }
        cout << "PLEASE ENTER: ";
    }
}