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
            char last_c = *word.rbegin();
            if (last_c==',' || last_c=='.' || last_c=='!' || last_c=='?') {
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

// opens in binding it to the given file
ifstream& open_file(ifstream& in, const string filename) {
    in.close();  // close in case it was already open
    in.clear();  // clear any existing errors
    // if the open fails, the stream will be in an invalid state
    in.open(filename.c_str());  // open the file we were given
    return in;
}

// return plural version of word if ctr isn't 1
string make_plural(size_t ctr, const string &word, const string &ending)
{
    return (ctr == 1) ? word : word + ending;
}

void print_results(const set<TextQuery::line_no>& locs, const string& sought,
const TextQuery& tq) {
    // if the word was found, then print count and all occurrences
    typedef set<TextQuery::line_no> line_nums;
    line_nums::size_type size = locs.size();
    cout << "\n" << sought << " occurs "
         << size << " " << make_plural(size, "time", "s") << endl;
    // print each line in which the word appeared
    for (line_nums::const_iterator iter=locs.begin();
    iter!=locs.end(); ++iter) {
        cout << "\t(line " << (*iter)+1 << ") "
             << tq.text_line(*iter) << endl;
    }
}

// program takes single argument specifying the file to query
int main(int argc, char ** argv) {
    // open the file from which user will query words
    ifstream infile;
    if (argc<2 || !open_file(infile, argv[1])) {
        cerr << "No input file!" << endl;
        return EXIT_FAILURE;
    }

    TextQuery tq;

    tq.read_file(infile); // builds query map

    // iterate with the user: prompt for a word to find and print results
    // loop indefinitely; the loop exit is inside the while
    while (true) {
        cout << "enter word to look for, or q to quit: ";
        string s;
        cin >> s;
        // stop if hit eof on input or a 'q' is entered
        if (!cin || s=="q") break;
        // get the set of line numbers on which this word appears
        set<TextQuery::line_no> locs = tq.run_query(s);
        // print count and all occurrences, if any
        print_results(locs, s, tq);
    }
}