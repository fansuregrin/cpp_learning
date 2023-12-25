// topic: regex_replace

#include <iostream>
#include <string>
#include <regex>

using namespace std;

int main() {
    // match a potential phonenumber: (ddd) separator ddd separator dddd
    string phone("(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ]?)(\\d{4})");
    regex r(phone);

    string fmt = "$2.$5.$7";
    string number = "(908) 555-1800";
    cout << regex_replace(number, r, fmt) << endl;
}