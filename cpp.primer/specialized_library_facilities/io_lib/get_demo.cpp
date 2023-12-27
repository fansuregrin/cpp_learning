// topic: unformated i/o operations (get)

#include <iostream>
#include <sstream>

int main() {
    std::istringstream s1("Hello, world.");
    char c1 = s1.get();  // reads 'H'
    std::cout << "after reading: [" << c1 << "], gcount() is " << s1.gcount() << '\n';

    char c2;
    s1.get(c2);  // reads 'e'
    std::cout << "after reading: [" << c2 << "], gcount() is " << s1.gcount() << '\n';
    
    char str[5];
    // `get( char_type* s, std::streamsize count)` reads at most std::max(0, count - 1) characters
    // and stores them into character string pointed to by s until '\n' is found.
    s1.get(str, 5);  // reads 'llo,', `str` is {'l', 'l', 'o', ',', '\0'}
    std::cout << "after reading: [" << str << "], gcount() is " << s1.gcount() << '\n';

    std::cout << "after reading: [";
    s1.get(*std::cout.rdbuf());  // reads the rest, not including '\n'
    std::cout << "], gcount() is " << s1.gcount() << '\n';
}