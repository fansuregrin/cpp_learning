// topic: unformated i/o operations (unget)

#include <iostream>
#include <sstream>

int main() {
    std::istringstream s("Hello");
    char c1 = s.get();
    if (s.unget()) {
        char c2 = s.get();
        std::cout << "Got: " << c1 << ", got again: " << c2 << '\n';
    }
}