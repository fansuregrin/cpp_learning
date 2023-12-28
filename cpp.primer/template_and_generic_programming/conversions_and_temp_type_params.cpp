// topic: conversions and template type parameters

// const conversions and array or function to pointer are the only automatic
// conversions for arguments to parameters with template types.
// 1) `const` conversions
// 2) array/function-to-pointer conversions

// Normal conversions are applied to arguments whose type is not a template
// parameter.

#include <string>


template<typename T> void f_obj(T a, T b) { }
template<typename T> void f_ref(const T& a, const T& b) { }

template<typename T>
int compare(const T& a, const T& b) {
    if (a < b) return -1;
    if (b < a) return 1;
    return 0;
}

template<typename U, typename V>
int flexible_compare(const U& a, const V& b) {
    if (a < b) return -1;
    if (b < a) return 1;
    return 0;
}

template<typename T> T add(const T& a, const int& b) {
    return a + b;
}

int main() {
    std::string s1("a value");
    const std::string s2("another value");

    f_obj(s1, s2);  // calls f_obj(string, string); const is ignored
    f_ref(s1, s2);  // calls f_ref(const string&, const string&)
                    // uses permissible conversion to const on `s1`

    int a[10], b[42];
    f_obj(a, b);  // calls f(int*, int*)
    
    // error: no matching function for call to ‘f_ref(int [10], int [42])’
    // f_ref(a, b);

    // error: no matching function for call to ‘compare(long int, int)’
    // compare(1L, 1);
    // If we want to allow normal conversions on the arguments, we can define the
    // function with two type parameters:
    flexible_compare(1L, 1);  // ok; calls flexible_compare(const long&, const int&)
    
    // ok; calls `add(const double &, const int &)`; converts long to int
    add(3.1, 100L);

    return 0;
}