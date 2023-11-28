#ifndef TEXT_QUERY_H
#define TEXT_QUERY_H

#include <vector>
#include <set>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

class TextQuery {
public:
    // typedef: line number
    typedef vector<string>::size_type line_no;

    /* interface:
     * `read_file` builds internal data structures for the given file
     * `run_query` finds the given word and returns set of lines on which it appears
     * `text_line` returns a requested line from the input file
     */

    void read_file(ifstream& is) {
        store_file(is);
        build_map();
    }

    set<line_no> run_query(const string&) const;

    const string& text_line(line_no) const;
private:
    // remember the whole input file
    vector<string> lines_of_text; 

    // map word to set of the lines on which it occurs
    map<string, set<line_no>> word_map;

    // store input file
    void store_file(ifstream& is);

    // associated each word with a set of line numbers
    void build_map();
public:
    line_no size() const { return lines_of_text.size(); }
};

// read input file: store each line as element in lines_of_text
void TextQuery::store_file(ifstream& is) {
    string text_line;
    while (getline(is, text_line)) {
        lines_of_text.push_back(text_line);
    }
}

// finds whitespace-separated words in the input vector
// and puts the word in word_map along with the line number
void TextQuery::build_map() {
    // process each line from the input vector
    for (line_no line_num=0; line_num<lines_of_text.size(); ++line_num) {
        // we'll use line to read the text a word at a time
        istringstream line(lines_of_text[line_num]);
        string word;
        while (line >> word) {
            // add this line number to the set;
            // subscript will add word to the map if it's not already there
            while (!word.empty() && !isalpha(word.front())) {
                word.erase(word.begin());
            }
            while (!word.empty() && !isalpha(word.back())) {
                word.pop_back();
            }
            word_map[word].insert(line_num);
        }
    }
}

set<TextQuery::line_no>
TextQuery::run_query(const string& query_word) const {
    // Note: must use find and not subscript the map directly
    // to avoid adding words to word_map!
    auto loc = word_map.find(query_word);
    if (loc != word_map.end()) {
        return loc->second;
    } else {
        return set<line_no>();
    }
}

const string& TextQuery::text_line(line_no line_num) const {
    if (line_num < lines_of_text.size()) {
        return lines_of_text[line_num];
    }
    throw out_of_range("line number out of range");
}

#endif