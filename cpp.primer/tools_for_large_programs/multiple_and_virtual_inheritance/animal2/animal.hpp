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

    ZooAnimal(const std::string &__name, bool __onExhibit, const std::string &__family):
    name(__name), onExhibit(__onExhibit), family(__family) {
        std::cout << "calling ZooAnimal(\"" << __name << "\", "
            << std::boolalpha << __onExhibit << std::noboolalpha 
            << ", \"" << __family << "\") to construct a ZooAnimal..." << std::endl;
    }

    ~ZooAnimal() {
        std::cout << "calling ~ZooAnimal() to destroy a ZooAnimal..." << std::endl;
    }

    virtual std::string str() const {
        std::ostringstream s;
        s << "<Animal: \"" << name << "\", onExhibit=" << std::boolalpha 
            << onExhibit << std::noboolalpha << ", family=" << family << "\">";
        return s.str();
    }

    virtual std::string intro() const {
        std::ostringstream s;
        s << "Hi! I am " << name << "! I am " << (onExhibit?"":"not ")
          << "being exhibited.";
        return s.str();
    }
protected:
    std::string name;
    bool onExhibit;
    std::string family;
};

class Bear: public virtual ZooAnimal {
public: 
    Bear() {
        std::cout << "calling Bear() to construct a Bear..." << std::endl;
    }
    
    Bear(const std::string &__name, bool __onExhibit):
    ZooAnimal(__name, __onExhibit, "Bear") {
        std::cout << "calling Bear(\"" << __name << "\", " << std::boolalpha 
            << __onExhibit << std::noboolalpha << ") to construct a Bear..." << std::endl;
    }

    ~Bear() {
        std::cout << "calling ~Bear() to destroy a Bear..." << std::endl;
    }

    std::string str() const {
        std::ostringstream s;
        s << "<Bear: \"" << name << "\", onExhibit=" << std::boolalpha 
          << onExhibit << std::noboolalpha << ">";
        return s.str();
    }

    std::string intro() const {
        std::ostringstream s;
        s << ZooAnimal::intro() << " I am a Bear.";
        return s.str();
    }
};

class Raccoon: public virtual ZooAnimal {
public: 
    Raccoon() {
        std::cout << "calling Raccoon() to construct a Raccoon..." << std::endl;
    }
    
    Raccoon(const std::string &__name, bool __onExhibit):
    ZooAnimal(__name, __onExhibit, "Raccoon") {
        std::cout << "calling Raccoon(\"" << __name << "\", " << std::boolalpha 
            << __onExhibit << std::noboolalpha << ") to construct a Raccoon..." << std::endl;
    }

    ~Raccoon() {
        std::cout << "calling ~Raccoon() to destroy a Raccoon..." << std::endl;
    }

    std::string str() const {
        std::ostringstream s;
        s << "<Raccoon: \"" << name << "\", onExhibit=" << std::boolalpha 
          << onExhibit << std::noboolalpha << ">";
        return s.str();
    }

    std::string intro() const {
        std::ostringstream s;
        s << ZooAnimal::str() << " I am a Raccoon.";
        return s.str();
    }
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

class Panda: public Bear, public Raccoon, public Endangered {
public:
    Panda() {
        std::cout << "calling Panda() to construct a Panda..." << std::endl;
    }

    Panda(const std::string &__name, bool __onExhibit):
        /// How a Virtually Inherited Object Is Constructed?
        // he virtual base subparts of the object are initialized first, using
        // initializers provided in the constructor for the most derived class. Once the virtual base
        // subparts of the object are constructed, the direct base subparts are constructed in the
        // order in which they appear in the derivation list.
        ZooAnimal(__name, __onExhibit, "Panda"),
        Bear(__name, __onExhibit),
        Raccoon(__name, __onExhibit),
        Endangered(Endangered::critical) {
        std::cout << "calling Pand(\"" << __name << "\", " << std::boolalpha
            << __onExhibit << std::noboolalpha << ") to construct a Panda..." << std::endl;
    }

    ~Panda() {
        std::cout << "calling ~Panda() to construct a Panda..." << std::endl;
    }

    std::string str() const {
        std::ostringstream s;
        s << "<Panda: \"" << name << "\", onExhibit=" << std::boolalpha 
          << onExhibit << std::noboolalpha << ", family=\"" << family << "\", endangered_level=\""
          << Endangered::str() << "\">";
        return s.str();
    }

    std::string intro() const {
        std::ostringstream s;
        s << ZooAnimal::intro() << " I am a Panda from China and I like eating bamboo!";
        return s.str();
    }
};

#endif