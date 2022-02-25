#include <vector>
#include <iostream>
#include <algorithm>
#include <random>

using namespace std;

int main(){
    vector<string> stu;
    default_random_engine dre;
    uniform_int_distribution<char> letter(97, 122);
    uniform_int_distribution<int> length(1, 10);

    int count;
    cout << "how many students do you want to create: ";
    cin >> count;
    while(count--){
        string name;
        for(int i=0; i<length(dre); ++i){
            name.push_back(letter(dre));
        }
        stu.push_back(name);
    }

    for(auto st: stu){
        cout << st << endl;
    }

    string name_;
    cout << "name you want to index: ";
    cin >> name_;
    auto p = find(stu.begin(), stu.end(), name_);
    if(p!=stu.end()){
        cout << "index: " << p-stu.begin() << endl;
    }
    
    return 0;
}