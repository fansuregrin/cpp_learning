#include <memory>
#include <string>
#include <iostream>
#include <vector>

using std::shared_ptr;
using std::string;
using std::make_shared;
using std::vector;

int main() {
    shared_ptr<string> pNico = make_shared<string>("nico");
    shared_ptr<string> pJutta = make_shared<string>("jutta");

    (*pNico)[0] = 'N';
    pJutta->replace(0, 1, "J");

    vector<shared_ptr<string>> who_make_coffee;
    who_make_coffee.push_back(pJutta);
    who_make_coffee.push_back(pJutta);
    who_make_coffee.push_back(pNico);
    who_make_coffee.push_back(pJutta);
    who_make_coffee.push_back(pNico);

    string sep;
    for (auto ptr:who_make_coffee) {
        std::cout << *ptr << (sep = " ");
    }
    std::cout << std::endl;
    // Jutta Jutta Nico Jutta Nico

    *pNico = "Nicolai";

    for (auto ptr:who_make_coffee) {
        std::cout << *ptr << (sep = " ");
    }
    std::cout << std::endl;
    // Jutta Jutta Nicolai Jutta Nicolai

    // use_count of pJutta: 4
    std::cout << "use_count of pJutta: " << pJutta.use_count() << std::endl;
    // use_count of pNico: 3
    std::cout << "use_count of pNico: " << pNico.use_count() << std::endl;

    // 创建 shared_ptr 时可以指定一个 deleter
    shared_ptr<string> p1(new string("abc"), [](string * ptr) {
        std::cout << "delete <" << *ptr << ">" << std::endl;
        delete ptr;
    });
}