#include <iostream>
#include "message.h"
#include "folder.h"

Message::Message(const string& str):
contents(str) {
    
}

Message::Message(const Message& other):
contents(other.contents), folders(other.folders) {
    // add this Message to each Folder that points to `other`
    put_msg_in_folders(folders);
}

Message& Message::operator=(const Message& rhs) {
    remove_msg_from_folders();  // update existing Folders
    contents = rhs.contents;  // copy contents from `rhs`
    folders = rhs.folders; // copy Folder pointers from `rhs`
    // add this Message to each Folder in `rhs`
    put_msg_in_folders(rhs.folders);

    return *this;
}

void Message::put_msg_in_folders(const set<Folder*>& folders_) {
    for (set<Folder*>::const_iterator it=folders_.begin();
    it!=folders_.end(); ++it) {
        (*it)->add_msg(this);  // *it points to a Folder
    }
}

void Message::remove_msg_from_folders() {
    // remove this message from corresponding folders
    for (set<Folder*>::const_iterator it=folders.begin();
    it!=folders.end(); ++it) {
        (*it)->rm_msg(this);
    }
}

Message::~Message() {
    remove_msg_from_folders();
}

void Message::save(Folder& folder) {
    folder.add_msg(this);
    folders.insert(&folder);
}

void Message::remove(Folder& folder) {
    folder.rm_msg(this);
    folders.erase(&folder);
}

ostream& Message::display(ostream& out) {
    out << contents << "\n";
    return out;
}