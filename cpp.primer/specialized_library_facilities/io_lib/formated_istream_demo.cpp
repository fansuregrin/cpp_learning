// topic: format istream

#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

int main() {
    char ch;

    istringstream is1("a b c\nd");
    while (is1 >> ch) {
        cout << ch;
    }
    cout << endl;

    istringstream is2("a b c\nd");
    is2 >> noskipws;
    while (is2 >> ch) {
        cout << ch;
    }
    cout << endl << skipws;
}