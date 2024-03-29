#ifndef FOLDER
#define FOLDER

#include <set>
#include <string>

using namespace std;

class Message;

class Folder {
public:
    Folder();

    Folder(const string&);

    ~Folder();

    void add_msg(Message *);

    void rm_msg(Message *);

    ostream& display_msgs(ostream&);
private:
    string name;
    set<Message*> messages;
};

#endif