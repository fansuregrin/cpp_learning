#include <random>
#include <iostream>
#include <ctime>

using namespace std;

int main(){
    random_device rdev;
    cout << "minimum: " << rdev.min() << endl;
    cout << "maxmum: " << rdev.max() << endl;
    cout << "entropy: " << rdev.entropy() << endl;
    cout << "some random numbers: ";
    int i = 3;
    while(i--)
        cout << rdev() << " ";
    cout << endl;

    default_random_engine eng, dre;
    cout << "minimum: " << eng.min() << endl;
    cout << "maxmum: " << eng.max() << endl;
    cout << " a random number: " << eng() << endl;

    uniform_int_distribution<int> distri_1(0, 100);

    clock_t start_t = clock();
    for(int i=0; i<1.0e6; ++i){
        distri_1(rdev);
    }
    cout << "generated 10^6 numbers through rdev" << endl;
    clock_t stop_t = clock();
    cout << "time consuming: " << (double)(stop_t - start_t)/CLOCKS_PER_SEC << "s" << endl;

    start_t = clock();
    for(int i=0; i<1.0e6; ++i){
        distri_1(eng);
    }
    cout << "generated 10^6 numbers through dre" << endl;
    stop_t = clock();
    cout << "time consuming: " << (double)(stop_t - start_t)/CLOCKS_PER_SEC << "s" << endl;

    return 0;
}   