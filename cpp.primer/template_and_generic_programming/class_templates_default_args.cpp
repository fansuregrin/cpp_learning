// topic: Template Default Arguments and Class Templates

template <typename T = int>  // by default T is `int`
class Numbers {
public:
    Numbers(T v = 0): val(v) {}
private:
    T val;
};

int main() {
    Numbers<long double> lots_of_precision;
    Numbers<> average_precision;  // empty <> says we want the default type

    // In particular, if a class template provides default arguments for all of its
    // template parameters, and we want to use those defaults, we must put an empty
    // bracket pair following the template’s name.
}