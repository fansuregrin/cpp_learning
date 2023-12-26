// topic: seeding a generator

#include <random>
#include <iostream>
#include <ctime>

using namespace std;

int main() {
    default_random_engine e1;  // uses the default seed
    default_random_engine e2(114514);  // uses the given seed

    default_random_engine e3;
    e3.seed(114514);
    default_random_engine e4(114514);

    // e1 and e2 will generate different sequences
    // e3 and e4 will generate the same sequence
    for (int i=0; i<10; ++i) {
        if (e1() == e2()) {
            cout << "unseeded match at iteration: " << i << endl;
        }
        if (e3() != e4()) {
            cout << "seeded differs at iteration: " << i << endl;
        }
    }

    default_random_engine e5(time(0));
    cout << e5() << endl;
}