#ifndef MESSAGE
#define MESSAGE

#include <string>
#include <set>
#include "folder.h"

using namespace std;

class Message {
public:
    // folders is initialized to the empty set automatically
    Message(const string& str = "") {};

    // copy control: we must manage pointers to this Message
    // from the Folders pointed to by folders

    Message(const Message&);

    Message& operator=(const Message&);

    ~Message();

    // Add this Message from specified Folder's set of messages
    void save(Folder&);

    // Remove this Message from specified Folder's set of messages
    void remove(Folder&);
private:
    string contents;  // Actual message text
    set<Folder*> folders;  // Folders that have this Message
    
    // Utility functions used by copy constructor, assignment, and destructor

    // Add this Message to the Folders that point to the parameter
    void put_msg_in_folders(const set<Folder>&);

    // Remove this Message from every Folder in folders
    void remove_msg_from_folders();
};

#endif