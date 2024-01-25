#include <string>
#include <iostream>

class Screen {
    // Window_mgr members can access the private parts of class Screen
    friend class WindowMgr;
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

    Screen &set(char);
    Screen &set(pos, pos, char);

    const Screen &display(std::ostream &os) const {
        do_display(os);
        return *this;
    }

    Screen &display(std::ostream &os) {
        do_display(os);
        return *this;
    }

    void some_member() const;
private:
    pos cursor = 0;
    pos height = 1, width = 1;
    std::string contents;
    mutable size_t access_ctr;  // may change even in a const object

    void do_display(std::ostream &os) const {
        os << contents;
    }
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

inline Screen &Screen::set(char c) {
    contents[cursor] = c;  // set the new value at the current cursor location
    return *this;  // return this object as an lvalue
}

inline Screen &Screen::set(pos row, pos col, char c) {
    contents[row*width+col] = c;  // set specified location to given value
    return *this;  // return this object as an lvalue
}

void Screen::some_member() const {
    ++access_ctr;  // keep a count of the calls to any member function
}