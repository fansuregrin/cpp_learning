#include "folder.h"
#include "message.h"

Folder::Folder(const string& name_ = "Default"):
name(name_) {

}

Folder::~Folder() {
    for (set<Message*>::const_iterator it=messages.begin();
    it!=messages.end(); ++it) {
        (*it)->remove(*this);
    }
}

void Folder::add_msg(Message * msg) {
    messages.insert(msg);
}

void Folder::rm_msg(Message * msg) {
    messages.erase(msg);
}