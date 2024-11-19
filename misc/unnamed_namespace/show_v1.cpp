#include "show.h"

namespace ns1 {

// 匿名命名空间可以让里面的内容局部于当前所在的编译单元（文件）
namespace {
int a = 1;
int b = 2;
} // unamed namespace

namespace x {
int c = 3;
} // namespace x

int d = 4;

void show_v1() {
    std::cout << "=================" << std::endl;
    // can access `ns1::<unnamed>::a` and `ns1::<unnamed>::b`
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    
    std::cout << "c = " << x::c << std::endl;
    std::cout << "d = " << d << std::endl;
    std::cout << "=================" << std::endl;
}

} // namespace ns1