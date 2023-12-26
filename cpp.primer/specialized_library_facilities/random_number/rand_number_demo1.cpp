// topic: random engine

#include <random>
#include <iostream>
#include <string>

using namespace std;

int main() {
    default_random_engine e;  // random-number engine
    
    // generates 10 random unsigned integers
    string sep;
    for (int i=0; i<10; ++i, sep=" ") {
        cout << sep << e();
    }
    cout << endl;

    e.seed(100UL);  // sets the seed
    cout << e() << endl;
    cout << "the range of random numbers: [" << e.min() << ", " << e.max() << "]" << endl;
    e.discard(5);  // advances the engine's state by a specified amount
    cout << e() << endl;
}