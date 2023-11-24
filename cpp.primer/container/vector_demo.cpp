#include <vector>
#include <iostream>

using namespace std;

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& v) {
    out << "[";
    for (typename vector<T>::const_iterator iter=v.begin();
    iter!=v.end(); ++iter) {
        if (iter != v.end()-1)
            out << *iter << ", ";
        else
            out << *iter;
    }
    return out << "]";
}

int main() {
    int nums[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = 5;

    // initialization/construction
    vector<int> v1;
    vector<int> v2(n);
    vector<int> v3(n, 3);
    vector<int> v4(nums+2, nums+8);
    vector<int> v5(v4.begin(), v4.end()-2);
    vector<int> v6{5, 4, 1, 1, -1};
    vector<int> v7(v6);

    vector<vector<int>> nest_v1(3, vector<int>(2));

    cout << "after initialization:" << endl;
    cout << "v1: " << v1 << endl;
    cout << "v2: " << v2 << endl;
    cout << "v3: " << v3 << endl;
    cout << "v4: " << v4 << endl;
    cout << "v5: " << v5 << endl;
    cout << "v6: " << v6 << endl;
    cout << "v7: " << v7 << endl;
    
    // assignment
    v1 = {1, 2};
    v2 = v7;

    cout << "after assignment:" << endl;
    cout << "v1: " << v1 << endl;
    cout << "v2: " << v2 << endl;

    // insertion
    v1.insert(v1.begin(), 0);
    v2.insert(v2.begin()+1, 3, 1);
    v3.insert(v3.begin()+v3.size()/2, v5.begin(), v5.end());
    v4.insert(v4.end(), {-1, -2, -3});

    cout << "after insertion:" << endl;
    cout << "v1: " << v1 << endl;
    cout << "v2: " << v2 << endl;
    cout << "v3: " << v3 << endl;
    cout << "v4: " << v4 << endl;

    return 0;
}