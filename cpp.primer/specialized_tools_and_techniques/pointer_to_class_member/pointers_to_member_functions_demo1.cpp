// topic: pointers to member functions

#include <string>


class Screen {
public:
    typedef std::string::size_type pos;
    
    Screen(): cursor(0), height(1), width(1) {}

    char get_cursor() const { return contents[cursor]; }

    char get() const { return contents[cursor]; }
    char get(pos ht, pos wd) const {
        return contents[ht*width+wd];
    }
private:
    std::string contents;
    pos cursor;
    pos height, width;
};


/// Using Type Aliases for Member Pointers

// Action is a type that can point to a member function of Screen
// that returns a char and takes two pos arguments
using Action = char (Screen::*)(Screen::pos, Screen::pos) const;
Action get = &Screen::get;  // get points to the get member of Screen

// action takes a reference to a Screen and a pointer to a Screen member function
Screen& action(Screen &s, Action act = &Screen::get) {
    (s.*act)(0, 0);
    return s;
}

int main() {
    // pmf is a pointer that can point to a Screen member function that is const
    // that returns a char and takes no arguments.
    auto pmf = &Screen::get_cursor;

    // If the member function is a const member or a reference member, 
    // we must include the const or reference qualifier as well.
    // As with normal function pointers, if the member is overloaded, we must distinguish
    // which function we want by declaring the type explicitly.

    char (Screen::*pmf2)(Screen::pos ht, Screen::pos wd) const;
    pmf2 = &Screen::get;

    // pmf points to a Screen member that takes no arguments and returns char
    pmf = &Screen::get;

    // pmf = Screen::get;  // error: no conversion to pointer for member functions

    /// Using a Pointer to Member Function
    Screen my_screen, *p_screen = &my_screen;
    char c1 = (p_screen->*pmf)();
    // passes the arguments 0, 0 to the two-parameter version of get on the object my_screen
    char c2 = (my_screen.*pmf2)(0, 0);

    /// Using Type Aliases for Member Pointers
    // equivalent calls:
    action(my_screen);  // uses the default argument
    action(my_screen, get);  // uses the variable get that we previously defined
    action(my_screen, &Screen::get);  // passes the address explicitly
}