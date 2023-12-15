#ifndef COMPARE
#define COMPARE

template<typename T>
int compare(T a, T b) {
    if (a < b) return -1;
    if (b < a) return 1;
    return 0;
}

#endif