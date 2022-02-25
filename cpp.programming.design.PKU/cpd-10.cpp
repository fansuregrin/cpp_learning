// coursera C++程序设计
// 第 5 周 编程作业—继承与派生 第一题
#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

// 在此处补充你的代码
class MyString{
    private:
        int len;
        char *data;
    public:
        MyString();
        MyString(const char *);
        ~MyString(){ delete [] data; };
        MyString(const MyString &);
        friend MyString operator+(const MyString &, const MyString &);
        friend MyString operator+(const MyString &, const char *);
        friend MyString operator+(const char *, const MyString &);
        friend ostream & operator<<(ostream &, const MyString &);
        MyString & operator=(const MyString &);
        MyString & operator=(const char *);
        char & operator[](int);
        MyString & operator+=(const MyString &);
        MyString & operator+=(const char *);
        MyString operator()(int, int);
        friend bool operator<(const MyString &, const MyString &);
        friend bool operator==(const MyString &, const MyString &);
        friend bool operator>(const MyString &, const MyString &);
};

MyString::MyString(){
    len = 0;
    data = NULL;
}

MyString::MyString(const char * s){
    len = strlen(s);
    data = new char[len];
    strncpy(data, s, len);
}

MyString::MyString(const MyString & str){
    len = str.len;
    data = new char[len];
    strncpy(data, str.data, len);
}

MyString & MyString::operator=(const MyString & str){
    len = str.len;
    data = new char[len];
    strncpy(data, str.data, len);
    return *this;
}

MyString & MyString::operator=(const char * s){
    len = strlen(s);
    data = new char[len];
    strncpy(data, s, len);
    return *this;
}

MyString operator+(const MyString & lhs, const MyString & rhs){
    MyString re;
    re.len = lhs.len + rhs.len;
    re.data = new char[re.len];
    strncpy(re.data, lhs.data, lhs.len);
    strncpy(re.data+lhs.len, rhs.data, rhs.len);
    return re;
}

MyString operator+(const MyString & lhs, const char * rhs){
    MyString re;
    re.len = lhs.len + strlen(rhs);
    re.data = new char[re.len];
    strncpy(re.data, lhs.data, lhs.len);
    strncpy(re.data+lhs.len, rhs, strlen(rhs));
    return re;
}

MyString operator+(const char *lhs, const MyString & rhs){
    MyString re;
    re.len = strlen(lhs) + rhs.len;
    re.data = new char[re.len];
    strncpy(re.data, lhs, strlen(lhs));
    strncpy(re.data+strlen(lhs), rhs.data, rhs.len);
    return re;
}

MyString & MyString::operator+=(const MyString & str){
    int oldlen = len;
    len += str.len;
    char * temp = new char[len];
    strncpy(temp, data, len);
    strncpy(temp+oldlen, str.data, str.len);
    data = temp;
    return *this;
}

MyString & MyString::operator+=(const char * s){
    int oldlen = len;
    len += strlen(s);
    char * temp = new char[len];
    strncpy(temp, data, len);
    strncpy(temp+oldlen, s, strlen(s));
    data = temp;
    return *this;
}

ostream & operator<<(ostream & out, const MyString & str){
    for(int i=0; i<str.len; i++){
        cout << str.data[i];
    }
    return out;
}

char & MyString::operator[](int pos){
    return data[pos];
}

bool operator<(const MyString & lhs, const MyString & rhs){
    int i;
    int len = lhs.len>rhs.len?rhs.len:lhs.len;
    for(i=0; i<len; i++){
        if(lhs.data[i] < rhs.data[i]){
           return true;
        }
        else if(lhs.data[i] > rhs.data[i]){
            return false;
        }
    }
    return lhs.len>rhs.len?false:true;
}

bool operator>(const MyString & lhs, const MyString & rhs){
    int i;
    int len = lhs.len>rhs.len?rhs.len:lhs.len;
    for(i=0; i<len; i++){
        if(lhs.data[i] > rhs.data[i]){
           return true;
        }
        else if(lhs.data[i] < rhs.data[i]){
            return false;
        }
    }
    return lhs.len>rhs.len?true:false;
}

bool operator==(const MyString & lhs, const MyString & rhs){
    int i;
    if (lhs.len != rhs.len){
        return false;
    }
    for(i=0; i<lhs.len; i++){
        if(lhs.data[i] != rhs.data[i]){
           return false;
        }
    }
    return true;
}

MyString MyString::operator()(int pos, int npos){
    MyString re;
    re.len = npos;
    re.data = new char[npos];
    strncpy(re.data, data+pos, npos);
    return re;
}

int CompareString( const void * e1, const void * e2) {
    MyString * s1 = (MyString * ) e1;
    MyString * s2 = (MyString * ) e2;
    if( *s1 < *s2 ) return -1;
    else if( *s1 == *s2 ) return 0;
    else return 1;
}

int main() {
    MyString s1("abcd-"),s2,s3("efgh-"),s4(s1);
    MyString SArray[4] = {"big","me","about","take"};
    cout << "1. " << s1 << s2 << s3<< s4<< endl;
    s4 = s3; 
    s3 = s1 + s3;
    cout << "2. " << s1 << endl;
    cout << "3. " << s2 << endl;
    cout << "4. " << s3 << endl;
    cout << "5. " << s4 << endl;
    cout << "6. " << s1[2] << endl;
    s2 = s1; s1 = "ijkl-";
    s1[2] = 'A' ;
    cout << "7. " << s2 << endl;
    cout << "8. " << s1 << endl;
    s1 += "mnop";
    cout << "9. " << s1 << endl;
    s4 = "qrst-" + s2;
    cout << "10. " << s4 << endl;
    s1 = s2 + s4 + " uvw " + "xyz";
    cout << "11. " << s1 << endl;
    qsort(SArray,4,sizeof(MyString), CompareString);
    for( int i = 0;i < 4;++i )
        cout << SArray[i] << endl;
    //输出s1从下标0开始长度为4的子串
    cout << s1(0,4) << endl;
    //输出s1从下标为5开始长度为10的子串
    cout << s1(5,10) << endl;

    return 0;
}