#include "folder.h"

Folder::Folder(const string& name_ = "Default"):
name(name_) {

}

void Folder::add_msg(Message * msg) {
    messages.insert(msg);
}

void Folder::rm_msg(Message * msg) {
    messages.erase(msg);
}