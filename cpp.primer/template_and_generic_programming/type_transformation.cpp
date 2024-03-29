// topic: type transformation

#include <vector>

// use The Type Transformation Library Template Classes
#include <type_traits>


template<typename It>
auto fcn(It beg, It end)
-> typename std::remove_reference<decltype(*beg)>::type {
    for (It i=beg; i!=end; ++i) {
        ++*i;
    }
    return *beg;  // return a copy of an element from the range
}

int main() {
    std::vector<int> vec{1, 2, 3};
    // fcn(vector<int>::iterator beg, vector<int>::iterator end)->int
    fcn(vec.begin(), vec.end());
}