// topic: Bernoulli Distribution

#include <random>
#include <iostream>

using namespace std;

bool play(bool indicator) {
    if (indicator) {
        // the porgrame go first
    } else {
        // the user go first
    }
    // ...
}

int main() {
    string resp;
    default_random_engine e; // e has state, so it must be outside the loop!
    bernoulli_distribution b; // 50/50 odds by default
    do {
        bool first = b(e); // if true, the program will go first
        cout << (first ? "We go first" : "You get to go first") << endl;
        // play the game passing the indicator of who goes first
        cout << ((play(first)) ? "sorry, you lost" : "congrats, you won") << endl;
        cout << "play again? Enter 'yes' or 'no'" << endl;
    } while (cin >> resp && resp[0] == 'y');
}