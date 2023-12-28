// topic: Overloading and `using` Declarations

namespace A {
    void print(int) { }
    void display(int) {}
    void display(double) {}
}

void print(double) {

}

void display(int) {

}

// using A::print(int);  // error: cannot specify a parameter list
using A::print;  // ok: using declarations specify names only

// error: ‘void A::display(int)’ conflicts with a previous declaration
// using A::display;

int main() {

}