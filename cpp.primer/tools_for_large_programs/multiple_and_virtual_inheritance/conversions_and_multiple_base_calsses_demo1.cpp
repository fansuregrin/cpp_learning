#include "animal/animal.hpp"
#include <iostream>


std::ostream &operator<<(std::ostream &os, const ZooAnimal &animal) {
    return os << animal.str();
}

void display(const Bear &bear) {
    std::cout << bear.str() << std::endl;
}

void hightlight(const Endangered &endangered) {
    std::cout << endangered.str() << std::endl;
}

void print(const Bear &bear) {
    std::cout << bear.str() << std::endl;
}

void print(const Endangered &endangered) {
    std::cout << endangered.str() << std::endl;
}

int main() {
    Panda yuanyuan("yuanyuan", true);

    display(yuanyuan);  // passes Panda to a reference to Bear
    hightlight(yuanyuan);  // passes Panda to a reference to Endangered
    std::cout << yuanyuan << std::endl;  // passes Panda to a reference to ZooAnimal


    // The compiler makes no attempt to distinguish between base classes in terms of a
    // derived-class conversion. Converting to each base class is equally good.
    // print(yuanyuan);  // error: call of overloaded ‘print(Panda&)’ is ambiguous

    Bear * pb = &yuanyuan;
    std::cout << pb->intro() << std::endl;  // ok! Panda::intro()
    // error: ‘class Bear’ has no member named ‘cuddle’
    // pb->cuddle();  // error: not part of the Bear interface

    Endangered &r = yuanyuan;
    // std::cout << r.intro() << std::endl;  // error: not part of the Endangered interface
}