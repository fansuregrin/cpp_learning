#include <iostream>
using namespace std;

class Warrior{
    private:
        int id;
        int strength;
    public:
        Warrior(int _id, int _strength): id(_id), strength(_strength){}
};

class Dragon: public Warrior{
    private:
        string name;
    public:
        Dragon(int, int, string);
};

Dragon::Dragon(int _id, int _strength, string _name): Warrior(_id, _strength){
    name = "dragon";
}

class Ninja: public Warrior{
    private:
        string name;
    public:
        Ninja(int, int, string);
};

Ninja::Ninja(int _id, int _strength, string _name): Warrior(_id, _strength){
    name = "ninja";
}

class Iceman: public Warrior{
    private:
        string name;
    public:
        Iceman(int, int, string);
};

Iceman::Iceman(int _id, int _strength, string _name): Warrior(_id, _strength){
    name = "iceman";
}

class Lion: public Warrior{
    private:
        string name;
    public:
        Lion(int, int, string);
};

Lion::Lion(int _id, int _strength, string _name): Warrior(_id, _strength){
    name = "lion";
}

class Wolf: public Warrior{
    private:
        string name;
    public:
        Wolf(int, int, string);
};

Wolf::Wolf(int _id, int _strength, string _name): Warrior(_id, _strength){
    name = "wolf";
}

