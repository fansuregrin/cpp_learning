// topic: Instantiation and Member Templates

#include "blob.h"
#include <iterator>
#include <list>
#include <vector>


int main() {
    int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<long> vi = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::list<const char *> w = {"now", "is", "the", "time"};

    // instantiates the `Blob<int>` class
    // and the `Blob<int>` constructor that has two `int*` parameters
    Blob<int> b1(std::begin(ia), std::end(ia));

    // instantiates the `Blob<int>` constructor that has two `vector<long>::iterator` parameters
    Blob<int> b2(vi.begin(), vi.end());

    // instantiates the `Blob<string>` class and the `Blob<string>`
    // constructor that has two `list<const char*>::iterator` parameters
    Blob<std::string> b3(w.begin(), w.end());

    return 0;
}