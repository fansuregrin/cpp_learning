#include <iostream>

namespace ns1 {
void show_v1();
void show_v2();

extern int d;

namespace x {
    extern int c;
}

namespace {
    extern int a;
    extern int b;
}
}