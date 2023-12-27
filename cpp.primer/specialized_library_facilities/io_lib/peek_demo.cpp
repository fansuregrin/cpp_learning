// topic: unformated i/o operations (peek)

#include <iostream>
#include <sstream>

int main() {
    std::istringstream s("Hello");
    char c1 = s.peek();
    char c2 = s.get();
    std::cout << "Peeked: " << c1 << ", got: " << c2 << '\n';
}