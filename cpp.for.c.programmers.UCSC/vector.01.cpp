#include <iostream>
#include <vector>

using namespace std;

int main(){
    vector<int> nums;
    cout << "size of nums: " << nums.size() << endl;
    cout << "max size of nums: " << nums.max_size() << endl;

    //push 10 numbers
    for(int i=0; i<10; ++i){
        nums.push_back(i*i);
    }

    //print nums
    for(auto p = nums.begin(); p!=nums.end(); ++p){
        cout << *p << " ";
    }
    cout << endl;

    //another print nums
    for(auto p: nums){
        cout << p << " ";
    }
    cout << endl;
    
    return 0;
}