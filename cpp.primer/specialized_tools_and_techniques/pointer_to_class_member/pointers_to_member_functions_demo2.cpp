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

    // cursor movement functions:

    Screen& home() {
        cursor = 0;
        return *this;
    }

    Screen& forward() {
        if (cursor < width*height-1) {
            ++cursor;
        }
        return *this; 
    }

    Screen& back() {
        if (cursor > 0) {
            --cursor;
        }
        return *this;
    }

    Screen& up() {
        if (cursor/width > 0) {
            cursor -= width;
        }
        return *this;
    }

    Screen& down() {
        if (cursor/width < width-1) {
            cursor += width;
        }
        return *this;
    }

    // Action is a pointer that can be assigned any of the cursor movement members
    using Action = Screen& (Screen::*)();

    enum Derictions { HOME, FORWARD, BACK, UP, DOWN};

    Screen& move(Derictions);
private:
    std::string contents;
    pos cursor;
    pos height, width;
    
    static Action Menu[];  // function table
};

Screen::Action Screen::Menu[] = {
    &Screen::home,
    &Screen::forward,
    &Screen::back,
    &Screen::up,
    &Screen::down,
};

Screen& Screen::move(Derictions cm) {
    // run the element indexed by cm on this object
    return (this->*Menu[cm])();  // Menu[cm] points to a member function
}

int main() {
    Screen my_screen;
    my_screen.move(Screen::HOME);
    my_screen.move(Screen::DOWN);
}