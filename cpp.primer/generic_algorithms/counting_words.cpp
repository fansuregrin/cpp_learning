#include <string>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

// comparison function to be used to sort by word length
bool is_shorter(const string& s1, const string& s2) {
    return s1.size() < s2.size();
}

// determine whether a length of a given word is 6 or more
bool ge_6(const string& s) {
    return s.size() >= 6;
}

// return plural version of word if ctr isn't 1
string make_plural(size_t ctr, const string &word, const string &ending)
{
    return (ctr == 1) ? word : word + ending;
}

int main() {
    vector<string> words{
        "the", "quick", "red", "fox", "jumps",
        "over", "the", "slow", "red", "turtle"};

    // sort words alphabetically so we can find the duplicates
    sort(words.begin(), words.end());

    /* eliminate duplicate words:
    * unique reorders words so that each word appears once in the
    * front portion of words and returns an iterator one past the unique range;
    * erase uses a vector operation to remove the nonunique elements
    */
    vector<string>::iterator end_unique = unique(words.begin(), words.end());
    words.erase(end_unique, words.end());

    // sort words by size, but maintain alphabetic order for words
    // of the same size
    stable_sort(words.begin(), words.end(), is_shorter);

    vector<string>::size_type wc = count_if(words.begin(), words.end(), ge_6);

    cout << wc << " " << make_plural(wc, "word", "s")
         << " 6 characters or longer" << endl;

    return 0;
}