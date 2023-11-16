#ifndef FOLDER
#define FOLDER

#include <set>
#include <string>

using namespace std;

class Message;

class Folder {
public:
    Folder(const string&);

    void add_msg(Message *);

    void rm_msg(Message *);
private:
    string name;
    set<Message*> messages;
};

#endif