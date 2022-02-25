// coursera C++程序设计
// 第 2 周 编程作业—C++初探 第一题
#include <iostream>
#include <cstdio>
using namespace std;

class Stu{
    private:
        char name[20]={0}, id[20]={0};
        unsigned int age, grades[4];
    public:
        void get_info();
        void print_info();
};

void Stu::get_info(){
    char temp;
    int i = 0;
    temp = getchar();
    while(temp!=','){
        name[i++] = temp;
        temp = getchar();
    }
    scanf("%d,", &age);
    i = 0;
    temp = getchar();
    while(temp!=','){
        id[i++] = temp;
        temp = getchar();
    }
    for(i=0; i<4; i++){
       scanf("%d", &grades[i]);
       getchar();
    }
}

void Stu::print_info(){
    int avrg_grade, sum_grade = 0;
    for(int i=0; i<4; i++){
        sum_grade += grades[i];
    }
    avrg_grade = sum_grade / 4;
    cout << name << "," << age << "," << id << "," << avrg_grade << endl;
}

int main(){
    Stu stu;
    stu.get_info();
    stu.print_info();
    return 0;
}