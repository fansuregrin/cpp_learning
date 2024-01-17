// topic: pointers to data members

#include <string>


class Screen {
public:
    typedef std::string::size_type pos;

    static const std::string Screen::*data() {
        return &Screen::contents;
    }

    std::string pub_str;
private:
    std::string contents;
    pos cursor;
    pos height, width;
};

int main() {
    using std::string;

    // pdata can point to a string member of a const (or non const) Screen object
    const string Screen::*pdata;

    pdata = &Screen::pub_str;

    /// Using a Pointer to Data Member
    //
    // It is essential to understand that when we initialize or assign a pointer to member,
    // that pointer does not yet point to any data. It identifies a specific member but not the
    // object that contains that member. We supply the object when we dereference the
    // pointer to member.
    //
    Screen my_screen, *p_screen = &my_screen;
    // .* dereferences pdata to fetch the contents member from the object my_screen
    auto s = my_screen.*pdata;
    // ->* dereferences pdata to fetch contents from the object to which p_screen points
    s = p_screen->*pdata;

    /// A Function Returning a Pointer to Data Member
    // data() returns a pointer to the contents member of class Screen
    pdata = Screen::data();
    // fetch the contents of the object named myScreen
    s = my_screen.*pdata;
}