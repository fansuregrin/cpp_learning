#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

int main(){
    ifstream word_file("wordd.txt");
    while(!word_file.good()){
        cout << "Error! Please input the correct filepath: ";
        string temp;
        cin >> temp;
        word_file = ifstream(temp);
    }
    istream_iterator<string> start(word_file), end;
    vector<string> words(start, end);
    cout << "word(s) count: " << words.size() << endl;
    cout << "\nwords as read" << endl;
    for(auto str: words){
        cout << str << " ";
    }
    cout << endl;
    sort(words.begin(), words.end());
    cout << "\nwords as sorted" << endl;
    for(auto str: words){
        cout << str << " ";
    }
    cout << endl;
    return 0;
}