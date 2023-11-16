#include "message.h"
#include "folder.h"

Message::Message(const string& str = ""):
contents(str) {
    
}

Message::Message(const Message& other):
contents(other.contents), folders(other.folders) {
    // add this Message to each Folder that points to `other`
    put_msg_in_folders(folders);
}

void Message::put_msg_in_folders(const set<Folder*>& folders_) {
    for (set<Folder*>::const_iterator it=folders_.begin();
    it!=folders_.end(); ++it) {
        (*it)->add_msg(this);  // *it points to a Folder
    }
}