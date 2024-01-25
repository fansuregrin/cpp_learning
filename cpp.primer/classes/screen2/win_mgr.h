#include <vector>
#include "screen.h"

class WindowMgr {
public:
    // location ID for each screen on the window
    using ScreenIndex = std::vector<Screen>::size_type;

    // reset the Screen at the given position to all blanks
    void clear(ScreenIndex);

    // add a Screen to the window and returns its index
    ScreenIndex add_screen(const Screen&);
private:
    // Screens this WindowMgr is tracking
    // by default, a WindowMgr has one standard sized blank Screen
    std::vector<Screen> screens{Screen(24, 80, ' ')};
};

void WindowMgr::clear(ScreenIndex i) {
    Screen &s = screens[i];
    s.contents = std::string(s.height*s.width, ' ');
}

WindowMgr::ScreenIndex WindowMgr::add_screen(const Screen& s) {
    screens.push_back(s);
    return screens.size() - 1;
}