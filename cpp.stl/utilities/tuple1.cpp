#include <tuple>
#include <complex>
#include <string>
#include <iostream>

using std::tuple;
using std::string;
using std::complex;

int main() {
    tuple<string,int,int,complex<double>> t;
    tuple<int,float,string> t1(1, 3.14, "hi");
    auto t2 = std::make_tuple(24, 44, "hello");

    std::cout << std::get<0>(t1) << ", "
        << std::get<1>(t1) << ", "
        << std::get<2>(t1) << std::endl;

    // 获取 `t1` 中元素的个数
    std::cout << "number of elements of t1: " 
        << std::tuple_size<decltype(t1)>::value << std::endl;

    std::get<1>(t1) = std::get<1>(t2);

    // 拥有相同元素个数的tuple可以进行关系比较
    // 但要确保对应元素能进行关系比较，否则程序是 ill-formed
    if (t1 < t2) {
        t1 = t2;
    }
}