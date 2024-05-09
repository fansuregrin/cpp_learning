#include <memory>
#include <vector>
#include <string>
#include <iostream>


class Person: public std::enable_shared_from_this<Person> {
public:
    Person(const std::string &name_,
        std::shared_ptr<Person> m = nullptr,
        std::shared_ptr<Person> f = nullptr)
        : name(name_), mother(m), father(f) {}
    
    ~Person() {
        std::cout << "delete " << name << std::endl;
    }

    void set_parents_and_their_kids(std::shared_ptr<Person> m = nullptr,
    std::shared_ptr<Person> f = nullptr) {
        mother = m;
        father = f;
        if (mother != nullptr) {
            mother->kids.push_back(shared_from_this());
        }
        if (father != nullptr) {
            father->kids.push_back(shared_from_this());
        }
    }
public:
    std::string name;
    std::shared_ptr<Person> mother;
    std::shared_ptr<Person> father;
    std::vector<std::weak_ptr<Person>> kids;
};

std::shared_ptr<Person> init_family(const std::string &name) {
    std::shared_ptr<Person> mom = std::make_shared<Person>(name+"'s mom");
    std::shared_ptr<Person> dad = std::make_shared<Person>(name+"'s dad");
    std::shared_ptr<Person> kid = std::make_shared<Person>(name);
    kid->set_parents_and_their_kids(mom, dad);
    return kid;
}

int main() {
    std::shared_ptr<Person> p = init_family("Nico");

    std::cout << "Nico's family exists\n"
        << "  - Nico is shared " << p.use_count() << " times\n"
        << "  - name of 1st kid of Nico's mom: "
        << p->mother->kids[0].lock()->name
        << std::endl;

    p = init_family("Jim");
    std::cout << "Jim's family exists" << std::endl;
}