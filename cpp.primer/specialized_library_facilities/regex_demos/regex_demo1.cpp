// topic: regular expression

#include <regex>
#include <string>
#include <iostream>

using namespace std;

int main() {
    // find the characters ei that follow a character other than c
    string pattern("[^c]ei");
    // we want the whole word in which our pattern appears
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
    regex r(pattern);  // construct a regex to find pattern
    smatch results;  // define an object to hold the results of a search
    // define a string that has text that does and doesn't match pattern
    string test_str = "receipt freind theif receive";
    // use r to find a match to pattern in test_str
    if (regex_search(test_str, results, r)) {  // if there is a match
        cout << results.str() << endl;  // print the matching word
    }
}