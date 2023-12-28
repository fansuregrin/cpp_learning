// topic: trailing return types (尾置返回类型)

#include <vector>


// a trailing return lets us declare the return type after the parameter list is seen

template<typename It>
auto fcn(It beg, It end) -> decltype(*beg) {
    for (It i=beg; i!=end; ++i) {
        ++*i;
    }
    return *beg;  // return a reference to an element from the range
}

int main() {
    std::vector<int> vec{1, 2, 3};
    fcn(vec.begin(), vec.end());
}