#include "blob_ptr.h"
#include "blob.h"
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

int main() {
    Blob<int> nums = {1, 2, 2, 4, 5};
    BlobPtr<int> p1(nums);

    string sep;
    for (Blob<int>::size_type i=0; i<nums.size(); ++i) {
        cout << sep << *p1++;
        sep = ", ";
    }
    cout << endl;

    try {
        *p1;
    } catch (const exception& e) {
        cout << e.what() << endl;
    }

    try {
        *p1++;
    } catch (const exception& e) {
        cout << e.what() << endl;
    }
    
    {
        Blob<int> tmp = {0, 1, 0};
        p1 = tmp;
    }

    try {
        *p1;
    } catch (const exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}