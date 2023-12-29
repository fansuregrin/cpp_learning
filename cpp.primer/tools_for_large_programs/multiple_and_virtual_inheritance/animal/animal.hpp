#ifndef ANIMAL
#define ANIMAL

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

class ZooAnimal {
public:
    ZooAnimal() {
        std::cout << "calling ZooAnimal() to construct a ZooAnimal..." << std::endl;
    }

    ZooAnimal(bool __onExhibit): onExhibit(__onExhibit) {
        std::cout << "calling ZooAnimal(" << std::boolalpha << __onExhibit
            << std::noboolalpha << ") to construct a ZooAnimal..." << std::endl;
    }

    ~ZooAnimal() {
        std::cout << "calling ~ZooAnimal() to destroy a ZooAnimal..." << std::endl;
    }

    virtual std::string str() const = 0;

    virtual std::string intro() const = 0;
protected:
    bool onExhibit;
};

class Bear: public ZooAnimal {
public: 
    Bear() {
        std::cout << "calling Bear() to construct a Bear..." << std::endl;
    }
    
    Bear(const std::string &__name, bool __onExhibit):
    name(__name), ZooAnimal(__onExhibit) {
        std::cout << "calling Bear(\"" << __name << "\", " << std::boolalpha 
            << __onExhibit << std::noboolalpha << ") to construct a Bear..." << std::endl;
    }

    ~Bear() {
        std::cout << "calling Bear() to destroy a Bear..." << std::endl;
    }

    std::string str() const {
        std::ostringstream s;
        s << "<Bear: \"" << name << "\", onExhibit=" << std::boolalpha 
          << onExhibit << std::noboolalpha << ">";
        return s.str();
    }

    std::string intro() const {
        std::ostringstream s;
        s << "Hi! I am " << name << "! I am " << (onExhibit?"":"not ")
          << "being exhibited.";
        return s.str();
    }
protected:
    std::string name;
};

enum endangered_level_type {
    __concerned,
    __vulnerable,
    __critical,
};

class Endangered {
public:
    typedef endangered_level_type elt;
    static const elt concerned = __concerned;
    static const elt vulnerable = __vulnerable;
    static const elt critical = __critical;

    Endangered() {
        std::cout << "calling Endangered() to construct an Endangered..." << std::endl;
    }

    Endangered(elt __level): level(__level) {
        std::cout << "calling Endangered(" << __level << ") to construct an Endangered..."
            << std::endl;
    }

    ~Endangered() {
        std::cout << "calling ~Endangered() to destroy an Endangered..." << std::endl;
    }

    virtual std::string str() const {
        std::string ret;
        switch (level) {
            case concerned: {
                ret = "concerned";
                break;
            }
            case vulnerable: {
                ret = "vulnerable";
                break;
            }
            case critical: {
                ret = "critical";
                break;
            }
        }
        return ret;
    }
protected:
    elt level;
};

class Panda: public Bear, public Endangered {
public:
    Panda() {
        std::cout << "calling Panda() to construct a Panda..." << std::endl;
    }

    Panda(const std::string &__name, bool __onExhibit):
    Bear(__name, __onExhibit), Endangered(Endangered::critical) {
        std::cout << "calling Pand(\"" << __name << "\", " << std::boolalpha
            << __onExhibit << std::noboolalpha << ") to construct a Panda..." << std::endl;
    }

    ~Panda() {
        std::cout << "calling ~Panda() to construct a Panda..." << std::endl;
    }

    std::string str() const {
        std::ostringstream s;
        s << "<Panda: \"" << name << "\", onExhibit=" << std::boolalpha 
          << onExhibit << std::noboolalpha << ", endangered_level=\""
          << Endangered::str() << "\">";
        return s.str();
    }

    std::string intro() const {
        std::ostringstream s;
        s << Bear::intro() << " I am a panda from China and I like eating bamboo!";
        return s.str();
    }

    virtual void cuddle() {

    }
};

#endif