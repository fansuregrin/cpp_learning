#include "blob_ptr.h"
#include "blob.h"
#include <iostream>
#include <string>
#include <stdexcept>


int main() {
    Blob<int> nums = {1, 2, 2, 4, 5};
    BlobPtr<int> p1(nums);

    std::string sep;
    for (Blob<int>::size_type i=0; i<nums.size(); ++i) {
        std::cout << sep << *p1++;
        sep = ", ";
    }
    std::cout << std::endl;

    try {
        *p1;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    try {
        *p1++;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    
    {
        Blob<int> tmp = {0, 1, 0};
        p1 = tmp;
    }

    try {
        *p1;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}