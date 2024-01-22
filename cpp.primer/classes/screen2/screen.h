#include <string>

class Screen {
public:
    typedef std::string::size_type pos;

    // alternative way to declare a type member using a type alias
    // using pos = std::string::size_type;

    Screen() = default;  // needed because Screen has another constructor

    // cursor initialized to 0 by its in-class initializer
    Screen(pos ht, pos wd, char c): height(ht), width(wd), contents(ht*wd, c) {}

    // get the character at the cursor
    char get() const { return contents[cursor]; }  // implicit inline

    inline char get(pos, pos) const;  // explicit inline

    Screen &move(pos, pos);  // can be made inline later

    void some_member() const;
private:
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;
    mutable size_t access_ctr;  // may change even in a const object
};

// we can specify inline on the definition
inline Screen &Screen::move(pos r, pos c) {
    cursor = r * width + c;
    return *this;
}

// declared as inline in the class
char Screen::get(pos r, pos c) const {
    return contents[r * width + c];
}

void Screen::some_member() const {
    ++access_ctr;  // keep a count of the calls to any member function
}