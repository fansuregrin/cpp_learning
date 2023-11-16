#include <iostream>
#include <vector>
#include "message.h"
#include "folder.h"

using namespace std;

int main() {
    Folder inbox("Inbox"), sent("Sent"), favorites("Favorites");
    Message msg1("Hello, world!");
    Message msg2("The spice must flow.");
    Message msg3("Wubba Lubba Dub-Dub");
    Message msg4("May the force be with you.");

    // start a new scope
    {
        Folder tmp("Temporary");
        Message msg5("With great power comes great responsibility!");
        msg5.save(tmp);
        msg5.save(favorites);
        msg2.save(tmp);
    }

    msg1.save(sent);
    msg2.save(inbox);
    msg3.save(inbox);
    msg4.save(inbox);
    msg3.save(favorites);

    return 0;
}