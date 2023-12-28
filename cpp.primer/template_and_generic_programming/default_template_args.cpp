// topic: default template arguments

#include <functional>


// compare has a default template argument, less<T>
// and a default function argument, F()
template <typename T, typename F = std::less<T>>
int compare(const T & v1, const T & v2, F f = F()) {
    if (f(v1, v2)) return -1;
    if (f(v2, v1)) return 1;
    return 0;
}

int main() {
    int i = compare(0, 42);
    int j = compare(1.1, 2.2, std::greater<double>());

    return 0;
}