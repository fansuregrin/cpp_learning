// topic: Member Templates of Ordianary (Nontemplate) Classes

#include <iostream>
#include <memory>
#include <string>


// function-object class that calls delete on a given pointer
class DebugDelete {
public:
    DebugDelete(std::ostream &s = std::cerr): os(s) {}

    // as with any function template, the type of T is deduced by the compiler
    template <typename T>
    void operator()(T * p) const {
        os << "deleting pointer: " << p << std::endl;
        delete p;
    }
private:
    std::ostream & os;
};

int main() {
    double * dp = new double;
    DebugDelete d;  // an object that can act like a delete expression

    d(dp);  // calls `DebugDelete::operator()(double*)`, which deletes `p`

    int * ip = new int(2);
    DebugDelete()(ip);  // calls `operator()(int*)` on a temporary `DebugDelete` object

    // destroying the the object to which p points
    // instantiates DebugDelete::operator()<int>(int *)
    std::unique_ptr<int, DebugDelete> p(new int, DebugDelete());
    // destroying the the object to which sp points
    // instantiates DebugDelete::operator()<string>(string*)
    std::unique_ptr<std::string, DebugDelete> sp(new std::string, DebugDelete());

    return 0;
}