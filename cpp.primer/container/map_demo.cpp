#include <map>
#include <string>
#include <iostream>
#include <functional>

using namespace std;

int main() {
    map<char, int> letter_cnt;
    
    string pangram = "The quick brown fox jumps over the lazy dog";
    for (auto ch:pangram) {
        if (isalpha(ch)) ++letter_cnt[tolower(ch)];
    }

    // print the map use `iterator`
    for (map<char,int>::const_iterator iter=letter_cnt.begin();
    iter!=letter_cnt.end(); ++iter) {
        // the type of `*iter` is a `pair<char, int>`
        cout << iter->first << " " << iter->second << "\n";
    }

    // print the map use `range-based for-loop`
    for (const auto& p:letter_cnt) {
        cout << p.first << " " << p.second << "\n";
    }

    map<string,size_t> inventory;

    function<void ()> print_inventory = [&inventory]() {
        string comma;
        for (const auto& p:inventory) {
            cout << comma << p.first << ": " << p.second;
            comma = ", ";
        }
        cout << endl;
    };

    inventory.insert(make_pair("apple", 2));
    inventory.insert({"strawberry", 3});
    inventory.insert(map<string,size_t>::value_type("banana", 1));
    inventory["pear"] = 5;
    print_inventory();

    // the number of boxes of "apple" in the inventory won't change because the `insert`
    // function does not modify the value if the key already exists in the map
    inventory.insert(make_pair("apple", 4));
    print_inventory();

    // check how many boxes of "sunsettias" are in the inventory

    // This approach makes sense logically, but it has side effects.
    // It will insert a new key: "sunsettia" into the map, and initialize it with '0'.
    //
    // cout << "sunsettia: " << inventory["sunsettia"] << "\n";
    // print_inventory();
    //
    // Instead, we can use this appoach:
    if (inventory.count("sunsettia")) {
        cout << "sunsettia: " << inventory["sunsettia"] << "\n";
    }
    // or this:
    if (inventory.find("sunsettia") != inventory.end()) {
        cout << "sunsettia: " << inventory["sunsettia"] << "\n";
    }

    inventory["lavender mellon"] = 6;
    inventory["wolfhock"] = 3;
    print_inventory();
    inventory.erase("sunsettia");
    inventory.erase("lavender mellon");
    print_inventory();
}