// topic: regex_replace

#include <iostream>
#include <string>
#include <sstream>
#include <regex>

using namespace std;

int main() {
    using std::regex_constants::format_no_copy;

    // match a potential phonenumber: (ddd) separator ddd separator dddd
    string phone("(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ]?)(\\d{4})");
    regex r(phone);

    string fmt = "$2.$5.$7";
    istringstream is("morgan (201) 555-2368 862-555-0123\ndrew (973)555.0130\nlee (609) 555-0132 2015550175 800.555-0000");
    string s;
    while (getline(is, s)) {
        cout << regex_replace(s, r, fmt, format_no_copy) << endl;
    }
}