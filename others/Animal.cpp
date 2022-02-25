#ifndef ANIMAL_CPP
#define ANIMAL_CPP
#include <string>
#include <iostream>
using namespace std;

class Animal{
    private:
        int age;
        string name;
        double weight;
        void say_priv();
    protected:
        string sex;
        void say_sex();
    public:
        string country;
        void say_country();
        void say_me();
        void set_age(int);
        void set_weight(int);
        void set_name(string);
        void set_sex(string);
        void set_country(string);
        void set_all(string, int, int, string, string);
        int get_age();
        int get_weight();
        string get_name();
        string get_sex();
        Animal(string _name="Bob", int _age=1, int _weight=5, string _sex="male", string _country="China");
};

Animal::Animal(string _name, int _age, int _weight, string _sex, string _country): 
        name(_name), age(_age), weight(_weight), sex(_sex), country(_country)
{
        cout << "a Animal was created!" << endl;
}

void Animal::set_age(int _age){
    age = _age;
}

void Animal::set_weight(int _weight){
    weight = _weight;
}

void Animal::set_name(string _name){
    name = _name;
}

void Animal::set_sex(string _sex){
    sex = _sex;
}

void Animal::set_country(string _country){
    country = _country;
}

void Animal::set_all(string _name, int _age, int _weight, string _sex, string _country){
    name = _name;
    age = _age;
    weight = _weight;
    sex = _sex;
    country = _country;
}

void Animal::say_priv(){
    cout << "I am " << name << ", " << age << " years old and weigh " << weight << " kg." << endl; 
}

void Animal::say_sex(){
    cout << "I am actually a " << sex << " animal." << endl;
}

void Animal::say_country(){
    cout << "I am from " << country << "." << endl;
}

void Animal::say_me(){
    cout << "=================== about me =====================" << endl;
    cout << "(1) "; say_priv();
    cout << "(2) "; say_sex();
    cout << "(3) "; say_country();
    cout << "==================================================" << endl;
}

int Animal::get_age(){
    return age;
}

string Animal::get_name(){
    return name;
}

int Animal::get_weight(){
    return weight;
}

string Animal::get_sex(){
    return sex;
}

#endif