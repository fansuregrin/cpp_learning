#include "show.h"

namespace ns1 {

void show_v2() {
    std::cout << "=================" << std::endl;
    // undefined reference to `ns1::(anonymous namespace)::a'
    // std::cout << "a = " << a << std::endl;
    
    // undefined reference to `ns1::(anonymous namespace)::b'
    // std::cout << "b = " << b << std::endl;
    
    std::cout << "c = " << x::c << std::endl;
    std::cout << "d = " << d << std::endl;
    std::cout << "=================" << std::endl;
}

}