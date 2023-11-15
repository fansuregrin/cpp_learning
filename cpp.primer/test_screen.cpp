#include "screen.h"
#include <iostream>

using namespace std;

int main(void) {
    Screen a(5, 5);
    a.set('*');
    a.display(cout).move(0, 4).set('*').display(cout);
    return 0;
}