// topic: function template

#include <iostream>

using namespace std;

class Square {
public:
    Square(): len(0.0) {}
    Square(double __len): len(__len) {}

    double area() const {
        return len*len;
    }

    double get_len() const {
        return len;
    }

    bool operator<(const Square& rhs) const {
        return len < rhs.len;
    }

    bool operator==(const Square& rhs) const {
        return len == rhs.len;
    }

    bool operator>(const Square& rhs) const {
        return !(*this<rhs) && !(*this==rhs);
    }
private:
    double len;
};

ostream& operator<<(ostream& os, const Square& sq) {
    return os << "Square(" << sq.get_len() << ")";
}

// a function template that return the minima of two arguments with type `T`
// require there is an implementation of operator< on two `T`s
template <typename T>
T get_min(T a, T b) {
    return a < b ? a : b;
}

// a function template that return the maxima of two arguments with type `T`
// `class` is an interchange of `typename`
// the `inline` reserved word must follow the template parameter list
template <class T>
inline T get_max(T a, T b) {
    return a > b ? a : b;
}

template <typename InputIt, typename T>
InputIt find(InputIt first, InputIt last, const T& val) {
    for (; first!=last; ++first) {
        if (*first == val) return first;
    }
    return last;
}

int main() {
    // call `int get_min<int>(int a, int b)`
    cout << "minima of " << 3 << " and " << 4 << ": " << get_min(3, 4) << endl;
    // call `double get_min<double>(double a, double b)`
    cout << "minima of " << 1.2 << " and " << 3.8 << ": " << get_min(1.2, 3.8) << endl;

    Square sq1(1.2), sq2(1.5);
    // call `Square get_min<Square>(Square a, Square b)`
    cout << "minima of " << sq1 << " and " << sq2 << ": " << get_min(sq1, sq2) << endl;

    cout << "minima of " << sq1 << " and " << sq2 << ": " << get_max(sq1, sq2) << endl;

    int arr[5] = {1, 2, 3, 4, 5};
    int * it = find(arr, arr+5, 3);
    if (it != arr+5) cout << "found \"" << *it << "\"!" << endl;

    return 0;
}