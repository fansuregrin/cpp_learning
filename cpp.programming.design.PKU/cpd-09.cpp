// coursera C++程序设计
// 第 4 周 编程作业—运算符重载 第四题
#include <iostream>
using namespace std;

class BigInt{
    private:
        string data;
    public:
        BigInt(){data="0";};
        BigInt(const string &);
        BigInt(const char *);
        friend ostream& operator<<(ostream &, const BigInt &);
        BigInt & operator=(const string &);
        BigInt & operator=(const char *);
        BigInt operator+(const BigInt &);
        BigInt operator-(const BigInt &);
        BigInt operator*(const BigInt &);
        BigInt operator/(const BigInt &);
        bool operator>(const BigInt &);
        bool operator==(const BigInt &);
        bool operator<(const BigInt &);
        bool operator>=(const BigInt &);
        bool is_positive();
};

BigInt::BigInt(const string & s): data(s){}
BigInt::BigInt(const char * s): data(s){}

BigInt & BigInt::operator=(const string & s){
    data = s;
    return *this;
}

BigInt & BigInt::operator=(const char * s){
    data = s;
    return *this;
}

ostream & operator<<(ostream & out, const BigInt & b){
    out << b.data;
    return out;
}

BigInt BigInt::operator+(const BigInt & b){
    int len, i;
    char * carry;
    string x, y, re_str;
    x = data;
    y = b.data;
    int len_x = x.length();
    int len_y = y.length();
    if(len_x > len_y){
        len = len_x;
        y.insert(0, len_x - len_y, '0');
    }
    else{
        len = len_y;
        x.insert(0, len_y - len_x, '0');
    }
    carry = new char[len+1];
    for(i=0; i<=len; i++){
        carry[i] = 0;
    }
    for(i=len-1; i>=0; i--){
        re_str.insert(0, 1, (x[i] -48 + y[i] - 48 + carry[len-i-1]) % 10 + '0');
        carry[len-i] = (x[i] - 48 + y[i] - 48 + carry[len-i-1])/10;
    } 
    if(carry[len]){
       re_str.insert(0, 1, carry[len]+'0');
    }
    delete carry;
    BigInt re(re_str);
    return re;
}

BigInt BigInt::operator-(const BigInt & b){
    int len, i;
    string x, y, re_str;
    x = data;
    y = b.data;
    if(*this == b){
        re_str = "0";
    }
    else if(*this > b){
        len = x.length();
        y.insert(0, x.length()-y.length(), '0');
        for(i=len-1; i>=0; i--){
            if(x[i] - y[i] >= 0){
                re_str.insert(0, 1, x[i] - y[i] + '0');
            }
            else{
                re_str.insert(0, 1, x[i] + 10 - y[i] + '0');
                x[i-1] -= 1;
            }
        }
        while(re_str.length()>1 && re_str[0]=='0'){
            re_str.erase(0, 1);
        }
    }
    else{
        len = y.length();
        x.insert(0, y.length()-x.length(), '0');
        for(i=len-1; i>=0; i--){
            if(y[i] - x[i] >= 0){
                re_str.insert(0, 1, y[i] - x[i] + '0'); 
            }
            else{
                re_str.insert(0, 1, y[i] + 10 - x[i] + '0');
                y[i-1] -= 1;
            }
        }
        re_str.insert(0, 1, '-'); 
        while(re_str.length()>2 && re_str[1]=='0'){
            re_str.erase(1, 1);
        }
    }
    BigInt re(re_str);
    return re;
}

BigInt BigInt::operator*(const BigInt & b){
    int i, j, len;
    BigInt re("0"), part("0");
    len = b.data.length();
    for(i=len-1; i>=0; i--){
        int count = b.data[i]-'0';
        part = "0";
        for(j=0; j<count; j++){
            part = part + *this; 
        }
        part.data.append(len-i-1, '0');
        re = re + part;
    }
    return re;
}

BigInt BigInt::operator/(const BigInt & b){
    
    BigInt re("0");
    if(b.data == "0"){
        re = "error!";
    }    
    if(*this < b){
        ;
    }
    else{
        int i;
        char j;
        int len = data.length() - b.data.length();
        string re_str;
        BigInt remain = *this, tes_remain;
        for(i=len; i>=0; i--){
            string temp = b.data;
            temp.append(i, '0');
            BigInt divisor = temp;
            for(j='9'; j>='0'; j--){
                BigInt quo = string(1, j);
                tes_remain = remain - divisor*quo;
                if(tes_remain.is_positive()){
                    re_str.append(1, j);
                    remain = tes_remain;
                    break;  
                }
            }
        }
        re.data = re_str;
    }
    return re;
}

bool BigInt::operator>(const BigInt & b){
    int len_a = data.length();
    int len_b = b.data.length();
    if(len_a > len_b){
        return true;
    }
    else if(len_a < len_b){
        return false;
    }
    else{
        for(int i=0; i<len_a; i++){
            if(data[i] > b.data[i])
                return true;
            else if(data[i] < b.data[i])
                return false;
            else ;
        }
        return false;
    }
}

bool BigInt::operator==(const BigInt & b){
    int len_a = data.length();
    int len_b = b.data.length();
    if(len_a != len_b){
        return false;
    }
    else{
        for(int i=0; i<len_a; i++){
            if(data[i] != b.data[i]){
                return false;
            }
            else ;
        }
        return true;
    }
}

bool BigInt::operator<(const BigInt & b){
    int len_a = data.length();
    int len_b = b.data.length();
    if(len_a < len_b){
        return true;
    }
    else if(len_a > len_b){
        return false;
    }
    else{
        for(int i=0; i<len_a; i++){
            if(data[i] < b.data[i])
                return true;
            else if(data[i] > b.data[i])
                return false;
            else ;
        }
        return false;
    }
}

bool BigInt::operator>=(const BigInt & b){
    if(*this > b)
        return true;
    else if(*this == b)
        return true;
    else
        return false;
}

bool BigInt::is_positive(){
    if(data[0] == '-'){
        return false;
    }
    else
        return true;
}

int main(){
    BigInt a, b;
    string op1, op2;
    char ope;
    cin >> op1 >> ope >> op2;
    a = op1;
    b = op2;
    switch(ope){
        case '+': cout << a+b << endl; break;
        case '-': cout << a-b << endl; break;
        case '*': cout << a*b << endl; break;
        case '/': cout << a/b << endl; break;
    }
    return 0;
}