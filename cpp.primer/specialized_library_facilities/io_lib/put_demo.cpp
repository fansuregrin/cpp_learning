// topic: unformated i/o operations (put)

#include <iostream>
#include <fstream>

int main() {
    // normal usage
    std::cout.put('a');
    std::cout.put('\n');

    std::ofstream s("/does/not/exist/");
    
    s.clear();  // pretended the stream is good
    std::cout << "Unformatted output: ";
    s.put('a');  // this will set badbit, but not failbit
    std::cout << "fail = " << bool(s.rdstate() & s.failbit)
              << ", bad = " << s.bad() << '\n';
    
    s.clear();
    std::cout << "Formatted output: ";
    s << 'a'; // this will set badbit and failbit
    std::cout << "fail = " << bool(s.rdstate() & s.failbit)
              << ", bad = " << s.bad() << '\n';
}