// topic: function-template explicit arguments


// T1 cannot be deduced: it doesn't appear in the function parameter list

template<typename T1, typename T2, typename T3>
T1 sum(T2 a, T3 b) {
    return a + b;
}

// Explicit template argument(s) are matched to corresponding template parameter(s)
// from left to right

// poor design: users must explicitly specify all three template parameters

template<typename T1, typename T2, typename T3>
T3 bad_sum(T1 a, T2 b) {
    return a + b;
}

template<typename T>
int compare(const T& a, const T& b) {
    if (a < b) return -1;
    if (b < a) return 1;
    return 0;
}

int main() {
    // error: no matching function for call to ‘sum(int, long int)’
    // long re = sum(2, 2L);

    // T1 is explicitly specified; T2 and T3 are inferred from the argument types
    long re = sum<long>(2, 2L);

    // error!
    // long re2 = bad_sum<long>(2, 2L);
    long re2 = bad_sum<int, long, long>(2, 2L);  // ok!

    // normal conversions also apply for arguments whose
    // template type parameter is explicitly specified
    // compare(2, 2L);  // error!
    compare<long>(2, 2L);  // ok; calls `compare(const long &, const long &)`
    compare<int>(2, 2L); // ok; calls `compare(const int &, const int &)`

    return 0;
}