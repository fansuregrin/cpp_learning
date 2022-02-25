// coursera C++程序设计
// 第 6 周 编程作业—多态与虚函数 第四题
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

class Settings;
class Headquarter;
class Warrior;
class Weapon;

class Settings{
    public:
        string name[5];
        int strength[5]; 
        string weapon[3];
        Settings();
        void set_warrior_strength();
        friend class Headquarter;
        friend class Warrior;
};

Settings::Settings(){
    name[0] = "dragon";
    name[1] = "ninja";
    name[2] = "iceman";
    name[3] = "lion";
    name[4] = "wolf";
    weapon[0] = "sword";
    weapon[1] = "bomb";
    weapon[2] = "arrow";
}

void Settings::set_warrior_strength(){
    for(int i=0; i<5; i++){
        cin >> strength[i];
    }
}

Settings setting;

class Weapon{
    private:
        int id;
        Warrior * wr;
    public:
        Weapon(int _id, Warrior * _wr):id(_id), wr(_wr){}
        // ~Weapon(){ cout << "a " << setting.weapon[id] << " disappeared..." << endl; }
};

class Warrior{
    private:
        int id;
        int strength;
        Headquarter * hq;
    public:
        Warrior(int _id, int _strength, Headquarter * _hq): id(_id), strength(_strength), hq(_hq){}
        int get_id(){ return id; }
        Headquarter * get_hq(){ return hq; }
};

class Dragon: public Warrior{
    private:
        string name;
        double morale;
        Weapon * weapon;
    public:
        Dragon(int, int, double, int, Headquarter *);
        ~Dragon();
};

Dragon::Dragon(int _id, int _strength, double _morale, int _weapon_id, Headquarter * _hq): Warrior(_id, _strength, _hq){
    name = "dragon";
    morale = _morale;
    weapon = new Weapon(_weapon_id, this);
    cout.flags(ios::fixed);
    cout.precision(2);
    cout << "It has a " << setting.weapon[_weapon_id] << ",and it's morale is " << morale << endl;
}

Dragon::~Dragon(){
    delete weapon;
    // cout << "dragon " << get_id() << " death from hq-" << get_hq() << "..." << endl;
} 

class Ninja: public Warrior{
    private:
        string name;
        Weapon * weapons[2];
    public:
        Ninja(int, int, Headquarter *, int, int);
        ~Ninja();
};

Ninja::Ninja(int _id, int _strength, Headquarter * _hq, int _weapon_id_1, int _weapon_id_2): Warrior(_id, _strength, _hq){
    name = "ninja";
    weapons[0] = new Weapon(_weapon_id_1, this);
    weapons[1] = new Weapon(_weapon_id_2, this);
    cout << "It has a " << setting.weapon[_weapon_id_1] << " and a " << setting.weapon[_weapon_id_2] << endl;
}

Ninja::~Ninja(){
    delete weapons[0];
    delete weapons[1];
    // cout << "ninja " << get_id() << " death from hq-" << get_hq() << "..." << endl;
}

class Iceman: public Warrior{
    private:
        string name;
        Weapon * weapon;
    public:
        Iceman(int, int, int, Headquarter *);
        ~Iceman();
};

Iceman::Iceman(int _id, int _strength, int _weapon_id, Headquarter * _hq): Warrior(_id, _strength, _hq){
    name = "iceman";
    weapon = new Weapon(_weapon_id, this);
    cout << "It has a " << setting.weapon[_weapon_id] << endl;
}

Iceman::~Iceman(){
    delete weapon;
    // cout << "Iceman " << get_id() << " deathfrom hq-" << get_hq() << "..." << endl;
}

class Lion: public Warrior{
    private:
        string name;
        int loyalty;
    public:
        Lion(int, int, int, Headquarter *);
        ~Lion();
};

Lion::Lion(int _id, int _strength, int _loyalty, Headquarter * _hq): Warrior(_id, _strength, _hq){
    name = "lion";
    loyalty = _loyalty;
    cout.flags(ios::fixed);
    cout.precision(2);
    cout << "It's loyalty is " << loyalty << endl;
}

Lion::~Lion(){
    // cout << "lion " << get_id() << " deathfrom hq-" << get_hq() << "..." << endl;
}

class Wolf: public Warrior{
    private:
        string name;
    public:
        Wolf(int, int, Headquarter *);
        ~Wolf();
};

Wolf::Wolf(int _id, int _strength, Headquarter * _hq): Warrior(_id, _strength, _hq){
    name = "wolf";
}

Wolf::~Wolf(){
    // cout << "wolf " << get_id() << " deathfrom hq-" << get_hq() << "..." << endl;
}

class Headquarter{
    private:
        // long hq_id;
        int time;
        int turn;
        int strength;
        int type;       //red or blue
        int id;
        int gen_seq[5];
        int num[5];
        bool stop;
        vector<Dragon *> dragon_list;
        vector<Ninja *> ninja_list;
        vector<Iceman *> iceman_list;
        vector<Lion *> lion_list;
        vector<Wolf *> wolf_list;
    public:
        Headquarter(int, int);
        ~Headquarter();
        void gen_warrior();
        bool can_gen();
        bool is_stop();
        // int get_hq_id();
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

Headquarter::~Headquarter(){
    int i;
    for(i=0; i<dragon_list.size(); ++i){
        delete dragon_list[i];
    }
    for(i=0; i<ninja_list.size(); ++i){
        delete ninja_list[i];
    }
    for(i=0; i<iceman_list.size(); ++i){
        delete iceman_list[i];
    }
    for(i=0; i<lion_list.size(); ++i){
        delete lion_list[i];
    }
    for(i=0; i<wolf_list.size(); ++i){
        delete wolf_list[i];
    }
}

void Headquarter::gen_warrior(){
    string type_s;
    if(type == 0){
        type_s = "red";
    }
    else if(type == 1){
        type_s = "blue";
    }
    if(!can_gen() && !stop){
        printf("%03d ", time);
        cout << type_s << " headquarter stops making warriors" << endl;
        stop = true;
    }
    while(can_gen()){
        int i = turn % 5; 
        turn++;
        int w_strength = setting.strength[gen_seq[i]];
        string w_name = setting.name[gen_seq[i]];
        if(strength - setting.strength[gen_seq[i]] >= 0){
            printf("%03d ", time++);
            cout << type_s << " " << w_name << " " << ++id << " born with strength " << w_strength << "," 
                 << ++num[gen_seq[i]] << " " << w_name << " in " << type_s << " headquarter" << endl;
            strength -= w_strength;
            switch(gen_seq[i]){
                case 0:{
                    Dragon * _dragon = new Dragon(id, w_strength, (double)strength/w_strength, id%3, this);
                    dragon_list.push_back(_dragon);
                    break;
                }
                case 1:{
                    Ninja * _ninja = new Ninja(id, w_strength, this, id%3, (id+1)%3);
                    ninja_list.push_back(_ninja);
                    break;
                }
                case 2:{
                    Iceman * _iceman = new Iceman(id, w_strength, id%3, this);
                    iceman_list.push_back(_iceman);
                    break;
                }
                case 3:{
                    Lion * _lion = new Lion(id, w_strength, strength, this);
                    lion_list.push_back(_lion);
                    break;
                }
                case 4:{
                    Wolf * _wolf = new Wolf(id, w_strength, this);
                    wolf_list.push_back(_wolf);
                    break;
                }
            }
            break;
        }   
    }
}

bool Headquarter::can_gen(){
    for(int i=0; i<5; i++){
        if(strength - setting.strength[gen_seq[i]] >= 0)
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
        setting.set_warrior_strength();
        cout << "Case:" << i+1 << endl;
        while(!red.is_stop() || !blue.is_stop()){
            red.gen_warrior();
            blue.gen_warrior();
        }
    }

    return 0;
}