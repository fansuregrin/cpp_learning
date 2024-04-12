#include <string>
#include "print_tuple.hpp"

using std::string;
using std::tuple;

int main() {
    tuple<int,float,string> t1(77, 1.25, "hello");
    tuple<int,double,char,int,string> t2(9, 0.01, 'X', 88, "big");
    std::cout << "t1: " << t1 << std::endl;
    std::cout << "t2: " << t2 << std::endl;
}