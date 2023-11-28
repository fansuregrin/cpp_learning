#include "query.h"

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
    cout << "\n" << "[" << sought << "] occurs "
         << size << " " << make_plural(size, "time", "s") << ":" << endl;
    // print each line in which the word appeared
    for (line_nums::const_iterator iter=locs.begin();
    iter!=locs.end(); ++iter) {
        cout << "\t(line " << (*iter)+1 << ") "
             << tq.text_line(*iter) << endl;
    }
}

void print_results(const set<TextQuery::line_no>& locs, const TextQuery& tq) {
    typedef set<TextQuery::line_no> line_nums;
    line_nums::size_type size = locs.size();
    cout << "\n" << "match occurs "
         << size << " " << make_plural(size, "time", "s") << ":" << endl;
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
    // while (true) {
    //     cout << "enter word to look for, or q to quit: ";
    //     string s;
    //     cin >> s;
    //     // stop if hit eof on input or a 'q' is entered
    //     if (!cin || s=="q") break;
    //     // get the set of line numbers on which this word appears
    //     set<TextQuery::line_no> locs = tq.run_query(s);
    //     // print count and all occurrences, if any
    //     print_results(locs, s, tq);
    // }

    // Query q("Daddy");
    // Query q = ~Query("Alice");
    // Query q = Query("hair") | Query("Alice");
    // Query q = Query("hair") & Query("Alice");
    Query q = Query("fiery") & Query("bird") | Query("wind");
    
    set<TextQuery::line_no> locs = q.eval(tq);
    cout << "Executing Query for: " << q << endl;
    print_results(locs, tq);

    return 0;
}