#include <vector>
#include "screen.h"

class WindowMgr {
private:
    // Screens this WindowMgr is tracking
    // by default, a WindowMgr has one standard sized blank Screen
    std::vector<Screen> screens{Screen(24, 80, ' ')};
};