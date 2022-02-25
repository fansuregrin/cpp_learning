#include <iostream>
#include <vector>

// length
const int N = 40;

// compute the sum of n numbers
void sum(int & p, std::vector<int> & d){
    int i;
    p = 0;
    for(i=0; i<d.size(); ++i){
        p += d[i];
    }
}

int main(){
    int i;                      //counting [0, 40)
    int accum = 0;              //store the sum
    std::vector<int> data;
    for(i=0; i<N; ++i){
        data.push_back(i);      //push [0, 40) in data
    }
    sum(accum, data);
    std::cout << "sum is " << accum << std::endl;   //print sum
    
    return 0;
}   