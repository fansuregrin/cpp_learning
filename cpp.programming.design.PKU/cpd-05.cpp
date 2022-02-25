// coursera C++程序设计
// 第 3 周 编程作业—类和对象 第四题
#include <iostream>
#include <cstdio>
using namespace std;

class Kind{
    public:
        string name[5];
        int strength[5]; 
        Kind();
        friend class Headquarter;
};

Kind::Kind(){
    name[0] = "dragon";
    name[1] = "ninja";
    name[2] = "iceman";
    name[3] = "lion";
    name[4] = "wolf";
    for(int i=0; i<5; i++){
        cin >> strength[i];
    }
}

class Headquarter{
    private:
        int time;
        int turn;
        int strength;
        int type;       //red or blue
        int id;
        int gen_seq[5];
        int num[5];
        bool stop;
    public:
        Headquarter(int, int);
        void gen_warrior(const Kind &);
        bool can_gen(const Kind &);
        bool is_stop();
};

Headquarter::Headquarter(int _strength, int _type): strength(_strength), type(_type){
    time = 0;
    id = 0;
    turn = 0;
    stop = false;
    for(int i=0; i<5; i++) num[i] = 0;
    if(type == 0){          //red
        gen_seq[0] = 2;
        gen_seq[1] = 3;
        gen_seq[2] = 4;
        gen_seq[3] = 1;
        gen_seq[4] = 0;
    }
    else if(type == 1){     //blue
        gen_seq[0] = 3;
        gen_seq[1] = 0;
        gen_seq[2] = 1;
        gen_seq[3] = 2;
        gen_seq[4] = 4;
    } 
}
void Headquarter::gen_warrior(const Kind & kind){
    string type_s;
    if(type == 0){
        type_s = "red";
    }
    else if(type == 1){
        type_s = "blue";
    }
    if(!can_gen(kind) && !stop){
        printf("%03d ", time);
        cout << type_s << " headquarter stops making warriors" << endl;
        stop = true;
    }
    while(can_gen(kind)){
        int i = turn % 5; 
        turn++;
        if(strength - kind.strength[gen_seq[i]] >= 0){
            printf("%03d ", time++);
            cout << type_s << " " << kind.name[gen_seq[i]] << " " << ++id << " born with strength " << kind.strength[gen_seq[i]] << "," 
                 << ++num[gen_seq[i]] << " " << kind.name[gen_seq[i]] << " in " << type_s << " headquarter" << endl;
            strength -= kind.strength[gen_seq[i]];
            break;
        }
        
    }
}

bool Headquarter::can_gen(const Kind & kind){
    for(int i=0; i<5; i++){
        if(strength - kind.strength[gen_seq[i]] >= 0)
            return true;
    }
    return false;
}

bool Headquarter::is_stop(){
    return stop;
}

int main(){
    int n;      //测试数据组数
    int i;   
    int total_strength;
    int time;   
    cin >> n;
    for(i=0; i<n; i++){
        cin >> total_strength;
        Headquarter red(total_strength, 0);     //red
        Headquarter blue(total_strength, 1);    //blue
        Kind _kind;
        cout << "Case:" << i+1 << endl;
        while(!red.is_stop() || !blue.is_stop()){
            red.gen_warrior(_kind);
            blue.gen_warrior(_kind);
        }
    }

    return 0;
}