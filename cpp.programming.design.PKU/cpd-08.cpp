// coursera C++程序设计
// 第 4 周 编程作业—运算符重载 第三题
#include <iostream>
#include <cstring>
using namespace std;

// 在此处补充你的代码
class Array2{
    private:
        int row, column;
        int ** p;
    public:
        Array2(int, int);
        ~Array2();
        Array2 & operator=(const Array2 &);
        int * operator[](int);
        int & operator()(int, int);
};

//constructor 
Array2::Array2(int r=0, int c=0){
    row = r;
    column = c;
    if(row>0 && column>0){
        p = new int*[row];
        for(int i=0; i<row; i++){
            p[i] = new int[column];
        }
    }
    else{
        p = NULL;
    }
}

//destructor
Array2::~Array2(){
    if(p){
        for(int i=0; i<row; i++){
            delete [] p[i];
        }
        delete [] p;
    }
}

Array2 & Array2::operator=(const Array2 & arr){
    row = arr.row;
    column = arr.column;
    p = new int*[row];
    for(int i=0; i<row; i++){
        p[i] = new int[column];
        for(int j=0; j<column; j++){
            p[i][j] = arr.p[i][j];
        }
    }
    return *this;
}

int * Array2::operator[](int r){
    return p[r];
}

int & Array2::operator()(int r, int c){
    return p[r][c];
}

int main() {
    Array2 a(3,4);
    int i,j;
    for( i = 0;i < 3; ++i )
        for( j = 0; j < 4; j ++ )
            a[i][j] = i * 4 + j;
    for( i = 0;i < 3; ++i ) {
        for( j = 0; j < 4; j ++ ) {
            cout << a(i,j) << ",";
        }
        cout << endl;
    }
    cout << "next" << endl;
    Array2 b; b = a;
    for( i = 0;i < 3; ++i ) {
        for( j = 0; j < 4; j ++ ) {
            cout << b[i][j] << ",";
        }
        cout << endl;
    }
    return 0;
}