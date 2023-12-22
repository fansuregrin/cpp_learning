// Function Template Specialization

#include <cstring>

using namespace std;

template <size_t N, size_t M>
int compare(const char (&a)[N], const char (&b)[M]) {
    return strcmp(a, b);
}

template <typename T>
int compare(const T &a, const T &b) {
    if (a < b) return -1;
    if (b < a) return 1;
    return 0;
}

// special version of compare to handle pointers to character arrays
template <>
int compare(const char * const &a, const char * const &b) {
    return strcmp(a, b);
}

int main() {
    const char *p1 = "dog", *p2 = "cat";

    // calls `compare<const char *>(const char *const &a, const char *const &b)`,
    // which is the special version.
    compare(p1, p2);

    // calls `compare<4UL, 5UL>(const char (&a)[4], const char (&b)[5])`.
    compare("dog", "cats");

    return 0;
}